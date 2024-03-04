#include "../lib/console.h"
#include "../h/riscv.hpp"
#include "../h/syscall_c.h"
#include "../h/print.hpp"
#include "../h/MemAllocator.hpp"
#include "../h/worker.hpp"
#include "../h/_sem.hpp"

extern void userMain();


void userMainWrapper(){
    userMain();

}



void main(){
/*
    uint64 base= (uint64) &Riscv::supervisorTrap;
    Riscv::w_stvec((base|1));

    Riscv::ms_sstatus(Riscv::SSTATUS_SIE);



    static TCB* threads[10];

    TCB::createThread(& threads[0],nullptr, nullptr);
    TCB::running = threads[0];

    Riscv::ms_sstatus(Riscv::SSTATUS_SIE);
    goToUserMode();
    TCB::SetMaximumUserThreads(2);

    thread_create(& threads[1],workerBodyA, nullptr);
    MyprintString("ThreadA created\n");
    thread_create(& threads[2],workerBodyB, threads[1]);
    MyprintString("ThreadB created\n");
    thread_create(& threads[3],workerBodyC, threads[2]);
    MyprintString("ThreadC created\n");
    thread_create(& threads[4],workerBodyD, nullptr);
    MyprintString("ThreadD created\n");
    thread_create(& threads[5],workerBodyE, threads[1]);
    MyprintString("ThreadE created\n");
    thread_create(& threads[6],workerBodyF, threads[2]);
    MyprintString("ThreadF created\n");
    thread_create(& threads[7],workerBodyG, nullptr);
    MyprintString("ThreadG created\n");

    thread_create(& threads[8],workerBodyH, threads[1]);
    MyprintString("ThreadH created\n");
    thread_create(& threads[9],workerBodyI, threads[2]);
    MyprintString("ThreadI created\n");






    //thread_join(threads[1]);
    //thread_join(threads[2]);



    while(!(threads[1]->isFinished()) || !(threads[2]->isFinished()) || !(threads[3]->isFinished()) || !(threads[4]->isFinished()) || !(threads[5]->isFinished())|| !(threads[6]->isFinished())|| !(threads[7]->isFinished())|| !(threads[8]->isFinished())|| !(threads[9]->isFinished()))
       thread_dispatch();

    MyprintString("Finnished waiting for threads 1 and 2 and 3  \n");

    for(auto &thread : threads){
        delete thread;
    }
    MyprintString("Finished\n");


*/


   // Riscv::mc_sstatus(Riscv::SSTATUS_SIE);


    uint64 base=(uint64) &Riscv::supervisorTrap;
    Riscv::w_stvec(base | 1);

    TCB *main;

    //TCB::createThread(&main,nullptr,nullptr,nullptr);
    thread_create(&main, nullptr, nullptr);
    TCB::running = main;
    //naprvi se kernel nit pa
    Riscv::ms_sstatus(Riscv::SSTATUS_SIE);

    goToUserMode();

    thread_t userMainThread;
    thread_create(&userMainThread, reinterpret_cast<void (*)(void *)>(&userMainWrapper), nullptr);

    while (!userMainThread->isFinished())
        thread_dispatch();

    delete userMainThread;

    //Riscv::mc_sstatus(Riscv::SSTATUS_SIE);

}