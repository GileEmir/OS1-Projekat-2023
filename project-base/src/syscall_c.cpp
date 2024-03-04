#include "../h/riscv.hpp"
#include "../h/syscall_c.h"
#include "../h/opcodes.hpp"


void* mem_alloc(size_t size){
    if (!size) { return nullptr; }
    size_t blocks = (size % MEM_BLOCK_SIZE == 0) ?
                    size / MEM_BLOCK_SIZE :
                    1 + size / MEM_BLOCK_SIZE;
    __asm__ volatile ("mv a1, %0" : : "r" (blocks));    //size je u blokovima
    __asm__ volatile ("mv a0, %0": : "r"(MEM_ALLOC));
    __asm__ volatile ("ecall");

                                                        //vracanje vrednosti
    volatile uint64 returnaddr;
    __asm__ volatile("mv %0, a0": "=r"(returnaddr));
    return (void*) returnaddr;
}

int mem_free(void* addr){
    if(!addr) return -1;

    __asm__ volatile ("mv a1, %0": : "r"(addr));
    __asm__ volatile ("mv a0, %0": : "r"(MEM_FREE));
    __asm__ volatile ("ecall");

                                                        //vracanje vrednosti
    volatile uint64 returnval;
    __asm__ volatile("mv %0, a0": "=r"(returnval));
    return (int) returnval;
}


int thread_create (thread_t* handle,void(*start_routine)(void*),void* arg){



    void* stack_space = mem_alloc(DEFAULT_STACK_SIZE);
    if (stack_space == nullptr)
    {
        return -1;
    }
    asm volatile("mv a4, %[stek]" ::[stek] "r" ((uint64)stack_space + DEFAULT_STACK_SIZE));
    __asm__ volatile("mv a3, %[arg]": : [arg] "r" (arg));
    __asm__ volatile("mv a2, %[arg]": : [arg] "r" (start_routine));
    __asm__ volatile("mv a1, %[arg]" : : [arg] "r" (handle));
    __asm__ volatile("mv a0, %[code]" : : [code] "r" (THREAD_CREATE));
    __asm__ volatile("ecall");

    volatile uint64 returnval;
    __asm__ volatile("mv %0, a0": "=r"(returnval));
    return (int) returnval;


}

int thread_exit (){
    __asm__ volatile("mv a0, %[code]" : : [code] "r" (THREAD_EXIT));
    __asm__ volatile("ecall");


    volatile uint64 returnval;
    __asm__ volatile("mv %0, a0": "=r"(returnval));
    return (int) returnval;

}


void thread_dispatch (){
    __asm__ volatile("mv a0, %[code]" : : [code] "r" (THREAD_DISPATCH));
    __asm__ volatile("ecall");

}
void thread_join (thread_t handle){                                     //U TELU NEKE FUNCIKE KOJU RADI PROCES A ZOVEMO join(b)  DA BI A SACEKAO B DA SE ZAVRSI  pozivom

    __asm__ volatile("mv a1, %[arg]" : : [arg] "r" (handle));
    __asm__ volatile("mv a0, %[code]" : : [code] "r" (THREAD_JOIN));
    __asm__ volatile("ecall");

}



int thread_getID(){
    __asm__ volatile("mv a0, %[code]": :[code] "r"(THREAD_ID) );
    __asm__ volatile ("ecall");

    volatile uint64 returnval;
    __asm__ volatile("mv %0, a0": "=r"(returnval));
    return (int) returnval;
}


int sem_open (sem_t* handle,unsigned init){



    __asm__ volatile("mv a2, %0" : : "r" (init));
    __asm__ volatile("mv a1, %0" : : "r" (handle));
    __asm__ volatile("mv a0, %0" : : "r" (SEM_OPEN));
    __asm__ volatile ("ecall");

    volatile uint64 returnval;
    __asm__ volatile("mv %0, a0": "=r"(returnval));
    return (int) returnval;

}

int sem_close (sem_t handle){
    if (handle == nullptr) {
        return -1;
    }

    __asm__ volatile("mv a1, %0" : : "r" (handle));
    __asm__ volatile("mv a0, %0" : : "r" (SEM_CLOSE));
    __asm__ volatile ("ecall");

    volatile uint64 returnval;
    __asm__ volatile("mv %0, a0": "=r"(returnval));
    return (int) returnval;
}

int sem_wait (sem_t id){
    if (id == nullptr) {
        return -1;
    }

    __asm__ volatile("mv a1, %0" : : "r" (id));
    __asm__ volatile("mv a0, %0" : : "r" (SEM_WAIT));
    __asm__ volatile ("ecall");

    volatile uint64 returnval;
    __asm__ volatile("mv %0, a0": "=r"(returnval));
    return (int) returnval;
}

int sem_signal (sem_t id){
    if (id == nullptr) {
        return -1;
    }


    __asm__ volatile("mv a1, %0" : : "r" (id));
    __asm__ volatile("mv a0, %0" : : "r" (SEM_SIGNAL));
    __asm__ volatile ("ecall");
    volatile uint64 returnval;
    __asm__ volatile("mv %0, a0": "=r"(returnval));
    return (int) returnval;
}


int time_sleep (time_t){
    //nisam radio
    return 0;
}

char getc(){

    __asm__ volatile("mv a0, %[code]" : : [code] "r" (GETC));
    __asm__ volatile("ecall");

    volatile uint64 returnval;
    __asm__ volatile("mv %0, a0": "=r"(returnval));
    return (int) returnval;


}

void putc(char c){

    asm volatile("mv a1,%0"::"r"(c));
    asm volatile("mv a0,%0"::"r"(PUTC));
    asm volatile("ecall");
}


void goToUserMode(){
    __asm__ volatile("mv a0, %[code]" : : [code] "r" (GOTO_USER));
    __asm__ volatile("ecall");
}
void goToSystemMode(){
    __asm__ volatile("mv a0, %[code]" : : [code] "r" (GOTO_SYSTEM));
    __asm__ volatile("ecall");
}