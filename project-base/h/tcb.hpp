
#ifndef OS1_VEZBE07_RISCV_CONTEXT_SWITCH_1_SYNCHRONOUS_CCB_HPP
#define OS1_VEZBE07_RISCV_CONTEXT_SWITCH_1_SYNCHRONOUS_CCB_HPP
#include "../lib/hw.h"
#include "scheduler.hpp"
#include "../h/syscall_cpp.hpp"
#include "../h/riscv.hpp"
typedef TCB *thread_t;

class TCB
{
    public:
        ~TCB(){delete[] stack;}
        bool isFinished () const { return finished; }
        void setFinished (bool value) { TCB::finished = value; }
        using Body = void (*)(void* );
        static TCB* createThread(TCB** handle,TCB::Body body,void* arg,uint64* stek);
        static TCB *running;
        static void join(TCB* handle);
        static void dispatch();
        static int numOfTCB;


        int ID ;
        int getThreadID();
        bool isBlocked() const { return blocked; }
        void setBlocked(bool value) { blocked = value; }




private:
    TCB (Body body,void* arg,uint64* stek) :
                body (body),args(arg),
                stack((uint64*)((uint64)stek - DEFAULT_STACK_SIZE)),
                context({ (uint64)&threadWrapper,
                          (uint64)stek
                        }),
                        finished(false) ,blocked(false){
            ID=numOfTCB;
            numOfTCB++;


            if (body != nullptr ) {
                Scheduler::put(this);
            }

        }

    struct Context
    {
        uint64 ra;
        uint64 sp;
    };
    Body body;
    void* args;
    uint64 *stack;
    Context context;
    bool finished;
    bool blocked;


    static void contextSwitch (Context *oldContext, Context *runningContext);

    static void threadWrapper();

    static ListaTCB blockedThreads;

};

#endif //OS1_VEZBE07_RISCV_CONTEXT_SWITCH_1_SYNCHRONOUS_CCB_HPP