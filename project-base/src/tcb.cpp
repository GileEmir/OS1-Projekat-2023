#include "../h/tcb.hpp"
#include "../h/riscv.hpp"
#include "../h/syscall_c.h"
#include "../h/MemAllocator.hpp"
#include "../h/print.hpp"

TCB* TCB::running=nullptr;

int TCB::numOfTCB=1;

//List<TCB> TCB::blockedThreads;
ListaTCB TCB::blockedThreads;


TCB* TCB::createThread(TCB** handle,TCB::Body body,void* arg,uint64* stek) {
    *handle = new TCB(body,arg,stek);
    return *handle;
}

void TCB::dispatch()
{
    TCB *old = running;
    if (!old->isFinished() && !old->isBlocked()) { Scheduler::put(old); }
    running = Scheduler::get();


    if (old != running) {
        TCB::contextSwitch(&old->context, &running->context);
    }
}
void TCB::threadWrapper()
{
    Riscv::popSppSpie();
    running->body(running->args);
    thread_exit();
}

void TCB::join(TCB *handle) {                   // ON CEKA DA SE ZAVRSI HANDLE
    while(!handle->isFinished()){
        dispatch();
    }

}

int TCB::getThreadID() {

    return ID;
}




