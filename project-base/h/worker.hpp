
#ifndef PROJECT_BASE_WORKER_HPP
#define PROJECT_BASE_WORKER_HPP
#include "../h/worker.hpp"
#include "../h/riscv.hpp"
#include "../h/tcb.hpp"
#include "../lib/hw.h"
#include "../h/print.hpp"

static volatile bool finishedA = false;
static volatile bool finishedB = false;
static volatile bool finishedC = false;



static uint64 fibonacci(uint64 n) {
    if (n == 0 || n == 1) { return n; }
    if (n % 10 == 0) { TCB::dispatch(); }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

void workerBodyA(void* arg) {
    uint16 i, j;
    MyprintString("telo A");
    putc('\n');
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 500; j++);
        printInteger(Thread::getThreadID());
        __putc('\n');
    }
    MyprintString("Kraj tela A");
    putc('\n');
    finishedA = true;

    /*uint8 i ;
    for ( i = 0; i < 3; i++) {
        MyprintString("A: i=");
        printInteger(i);
        MyprintString("\n");

    }
    MyprintString("A yield!\n");
    __asm__ ("li t1,7");
    TCB::yield();



    uint64 t1 = 0;
    __asm__ ("mv %0, t1" : "=r"(t1));
    MyprintString("\n");

    uint64 result = fibonacci(20);
    MyprintString("A: fibonaci=");
    printInteger(result);
    MyprintString("\n");

    for ( ; i < 6; i++) {
        MyprintString("A: i=");
        printInteger(i);
        MyprintString("\n");

    }
    MyprintString("A finished!\n");

    TCB::yield();*/

}

void workerBodyB(void* arg) {
    uint16 i, j;
    MyprintString("telo B");
    putc('\n');
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 500; j++);
        printInteger(Thread::getThreadID());
        __putc('\n');
    }
    MyprintString("Kraj tela B");
    putc('\n');
    finishedA = true;

    /*uint8 i ;

    if(arg!=0){
        TCB* argg=(TCB*) arg;
        thread_join(argg);
    }
    for ( i = 10; i < 13; i++) {
        MyprintString("B: i=");
        printInteger(i);
        MyprintString("\n");

    }
    MyprintString("B yield!\n");
    __asm__ ("li t1,5");
    TCB::yield();

    uint64 t1 = 0;
    __asm__ ("mv %0, t1" : "=r"(t1));
    MyprintString("\n");

    uint64 result = fibonacci(23);
    MyprintString("B: fibonaci=");
    printInteger(result);
    MyprintString("\n");

    for ( ; i < 16; i++) {
        MyprintString("B: i=");
        printInteger(i);
        MyprintString("\n");

    }
    MyprintString("B finished!\n");

    TCB::yield();*/


}

void workerBodyC(void* arg){
    uint16 i, j;
    MyprintString("telo C");
    putc('\n');
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 500; j++);
        printInteger(Thread::getThreadID());
        __putc('\n');
    }
    MyprintString("Kraj tela C");
    putc('\n');
    finishedA = true;
}
void workerBodyD(void* arg) {
    uint16 i, j;
    MyprintString("telo D");
    putc('\n');
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 500; j++);
        printInteger(Thread::getThreadID());
        __putc('\n');
    }
    MyprintString("Kraj tela D");
    putc('\n');
    finishedA = true;

}
void workerBodyE(void* arg) {
    uint16 i, j;
    MyprintString("telo E");
    putc('\n');
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 500; j++);
        printInteger(Thread::getThreadID());
        __putc('\n');
    }
    MyprintString("Kraj tela E");
    putc('\n');
    finishedA = true;
}
void workerBodyF(void* arg) {
    uint16 i, j;
    MyprintString("telo F");
    putc('\n');
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 500; j++);
        printInteger(Thread::getThreadID());
        __putc('\n');
    }
    MyprintString("Kraj tela F");
    putc('\n');
    finishedA = true;
}

void workerBodyG(void* arg) {
    uint16 i, j;
    MyprintString("telo G");
    putc('\n');
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 500; j++);
        printInteger(Thread::getThreadID());
        __putc('\n');
    }
    MyprintString("Kraj tela G");
    putc('\n');
    finishedA = true;
}

void workerBodyH(void* arg) {
    uint16 i, j;
    MyprintString("telo H");
    putc('\n');
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 500; j++);
        printInteger(Thread::getThreadID());
        __putc('\n');
    }
    MyprintString("Kraj tela H");
    putc('\n');
    finishedA = true;
}

void workerBodyI(void* arg) {
    uint16 i, j;
    MyprintString("telo I");
    putc('\n');
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 500; j++);
        printInteger(Thread::getThreadID());
        __putc('\n');
    }
    MyprintString("Kraj tela I");
    putc('\n');
    finishedA = true;
}


#endif //PROJECT_BASE_WORKER_HPP
