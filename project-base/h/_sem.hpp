//
#ifndef PROJECT_BASE__SEM_HPP
#define PROJECT_BASE__SEM_HPP
#include "list.hpp"

class TCB;

class _sem
{
public:

    ~_sem();
    int wait ();
    int signal ();
    int close ();
    int getValue () const { return value; };
    static _sem *createSemaphore( int init);

    _sem (int initialValue=0) : closed(false), value(initialValue) {}

protected:
    void block ();
    void deblock ();
    bool closed=false;
    int value;
    int NumOfBlockedThreads = 0;
private:
    List<TCB> blocked;
};

#endif //PROJECT_BASE__SEM_HPP