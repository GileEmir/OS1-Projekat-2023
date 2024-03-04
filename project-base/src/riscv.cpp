
#include "../h/riscv.hpp"
#include "../h/syscall_c.h"

//#include "../h/tcb.hpp"
//#include "../lib/console.h"
//#include "../test/printing.hpp"
#include "../h/opcodes.hpp"
#include "../h/_sem.hpp"
#include "../h/tcb.hpp"

#include "../h/MemAllocator.hpp"
#include "../h/print.hpp"
#include "../test/printing.hpp"



/*
void Riscv::init()
{
    bufin = new _buffer;
    bufout = new _buffer;
}
*/
// Kada se nova nit napravi, i dalje smo u prekidnoj rutini. Pozivamo ovu funkciju da bi izašli iz pr. rutine.

uint64  Riscv::timer=0;

// Različiti tipovi prekida
enum Interrupts: uint64 {
    SOFTWARE    = 0x8000000000000001UL,
    ECALL_SUPER = 0x0000000000000009UL,
    ECALL_USER  = 0x0000000000000008UL,
    HARDWARE    = 0x8000000000000009UL
};

/*
 * Ako je sistemska nit bila RUNNING pre prekidne rutine, vraćamo se u privilegovani režim po izlasku iz pr. rutine,
 * a ako je korisnička nit bila RUNNING pre prekidne rutine, vraćamo se u neprivilegovani režim.
 */





void Riscv::popSppSpie()
{

    //
    __asm__ volatile ("csrw sepc, ra");
    __asm__ volatile("sret");
}

void Riscv::handleConsole()
{
    console_handler();
}


void Riscv::handleTimer()
{
/*
    timer++;
    if(timer>=50){
    __putc('t');
    __putc('\n');
    timer=0;
    }
    //console_handler();

*/
    Riscv::mc_sip(SIP_SSIP);
}


void Riscv::handleInterrupt()
{
    uint64 scause=r_scause();
    if (scause == ECALL_SUPER || scause == ECALL_USER) //(ecall)
    {

        uint64 volatile sstatus=r_sstatus();
        uint64 volatile sepc = r_sepc() + 4;


        uint64 a0;
        __asm__ volatile("ld %0, 10*8(fp)" : "=r"(a0));


        if(a0 == MEM_ALLOC) { // mem_alloc
            uint64 a;
            __asm__ volatile ("ld %0,11*8(fp)":"=r"(a));
            uint64  size= a ;

            void* retval=MemAllocator::getInstance()->mem_alloc(size);
            __asm__ volatile ("sd %0, 10*8(fp)"::"r"(retval));  // 10*8(fp)=a0, 11*8(fp)=a1,12*8(fp)=a2...


        }
        else if(a0 == MEM_FREE) { // mem_free
            uint64 a;
            __asm__ volatile ("ld %0,11*8(fp)":"=r"(a));
            void* volatile addr=(void*) a ;

            int retval= MemAllocator::mem_free(addr);
            __asm__ volatile ("sd %0, 10*8(fp)"::"r"(retval));  // 10*8(fp)=a0, 11*8(fp)=a1,12*8(fp)=a2...
        }
        else if(a0 == THREAD_CREATE) { //thread_create
            // 10*8(fp)=a0, 11*8(fp)=a1,12*8(fp)=a2...
            uint64 thandle;
            __asm__ volatile ("ld %[handle], 11*8(fp)" : [handle]"=r"(thandle));
            uint64 startR;
            __asm__ volatile ("ld %[rs], 12*8(fp)" : [rs]"=r"(startR));
            TCB::Body funct=(TCB::Body)startR;
            void* arg;
            __asm__ volatile("ld %[arg], 13*8(fp)": [arg] "=r"(arg));
            TCB** threadHandle=(TCB**) thandle;
            uint64* stek;
            __asm__ volatile("ld %[stek], 14*8(fp)": [stek] "=r"(stek));

            *threadHandle=TCB::createThread(threadHandle,funct,arg,stek);
            uint64 retVal=0;
            if(threadHandle== nullptr)retVal=-1;
            __asm__ volatile ("sd %0, 10*8(fp)"::"r"(retVal));
        }
        else if(a0 == THREAD_EXIT) { // thread_exit
            TCB::running->setFinished(true);
            TCB::dispatch();
        }
        else if(a0 == THREAD_DISPATCH) { // thread_dispatch
            TCB::dispatch();
        }
        else if(a0==THREAD_JOIN){
            // 10*8(fp)=a0, 11*8(fp)=a1,12*8(fp)=a2...
            uint64 thandle;
            __asm__ volatile ("ld %[handle], 11*8(fp)" : [handle]"=r"(thandle));
            TCB::join((TCB *)thandle);

        }else if(a0==THREAD_ID){
            uint64 a=TCB::running->getThreadID();
            TCB::dispatch();
            uint64 retVal=a;
            __asm__ volatile ("sd %0, 10*8(fp)"::"r"(retVal));
        }else if(a0 == SEM_OPEN){
            sem_t* handle;
            int init;
            uint64 ret;

            __asm__ volatile("ld %[arg], 11*8(fp)": [arg] "=r"(handle));

            __asm__ volatile("ld %[arg], 12*8(fp)": [arg] "=r"(init));

            *handle = _sem::createSemaphore(init);

            if (*handle == nullptr){
                ret = -1;
            }
            else {
                ret = 0;
            }
            __asm__ volatile("sd %0,10*8(fp)"::"r"(ret));

        }else if(a0 == SEM_CLOSE){
            sem_t handle;
            uint64 ret;

            __asm__ volatile("ld %[arg], 11*8(fp)": [arg] "=r"(handle));
            ret = (handle)->close();

            __asm__ volatile("sd %0,10*8(fp)"::"r"(ret));

        }else if(a0==SEM_WAIT) {
            sem_t id;
            uint64 ret;

            __asm__ volatile("ld %[arg], 11*8(fp)": [arg] "=r"(id));
            ret = (id)->wait();

            __asm__ volatile("sd %0,10*8(fp)"::"r"(ret));
        }else if(a0==SEM_SIGNAL) {
            sem_t id;
            uint64 ret;

            __asm__ volatile("ld %[arg], 11*8(fp)": [arg] "=r"(id));
            ret = (id)->signal();

            __asm__ volatile("sd %0,10*8(fp)"::"r"(ret));
        }
        else if(a0 == TIME_SLEEP) { //time_sleep
                //nisam radio
        }
        else if(a0 == GOTO_USER){
            w_sstatus(sstatus);
            mc_sstatus(SSTATUS_SPP);
            w_sepc(sepc);
            //__asm__ volatile("csrw sepc, %0"::"r"(sepc));
            return;
        }
        else if(a0 == GOTO_SYSTEM){
            w_sstatus(sstatus);
            ms_sstatus(SSTATUS_SPP);
            __asm__ volatile("csrw sepc, %0"::"r"(sepc));
            return;
        }

        else if(a0 == GETC) { // getc
            char c=__getc();
            __asm__ volatile("sd %0,10*8(fp)"::"r"(c));
        }
        else if(a0 == PUTC) { // putc
            uint64 ch;
            __asm__ volatile("ld t2, 8*11(fp)");
            __asm__ volatile("mv %0, t2" : "=r" (ch));
            __putc((char)ch);
        }

        w_sstatus(sstatus); // restauracija statusnog registra
        w_sepc(sepc); // restauracija pc registra


    } else{
        uint64 sepc = r_sepc();
        // unexpected trap cause
        printString("scause: ");
        printInt(scause);
        printString("\n");

        printString("sepc: ");
        printHexa(sepc);
        printString("\n");

        while(true);
    }

}





void Riscv::handleSupervisorTrap()
{

}
