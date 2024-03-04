#include "../h/scheduler.hpp"

//List<TCB> Scheduler::readyThreadQueue; DODATO
ListaTCB Scheduler::readyThreadQueue;

TCB *Scheduler::get()
{
    return readyThreadQueue.removeFirst();
}

void Scheduler::put(TCB *ccb)
{
   readyThreadQueue.addLast(ccb);
}

