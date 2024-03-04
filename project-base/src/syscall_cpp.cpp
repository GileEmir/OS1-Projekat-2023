#include "../h/riscv.hpp"
#include "../h/syscall_cpp.hpp"
#include "../h/tcb.hpp"


void* operator new (size_t size) {
    return mem_alloc(size);
}

void operator delete (void* adrress)noexcept{
     mem_free(adrress);
}

void* operator new[] (size_t size) {
    return mem_alloc(size);
}

void operator delete[] (void* adrress)noexcept{
    mem_free(adrress);
}


Thread::Thread()
{
    myHandle=nullptr;
    body = threadWrapper;
    arg = this;
}

Thread::Thread(void (*body)(void *), void *arg) {
    myHandle= nullptr;
    this->body=body;
    this->arg=arg;
}

Thread::~Thread() {
    thread_join(myHandle);
}

int Thread::start() {
    if(myHandle == nullptr){ thread_create(&myHandle,body,arg);return 0;}
    else return -1;

}

void Thread:: join(){
    thread_join(myHandle);            //U TELU NEKE FUNCIKE KOJU RADI PROCES A ZOVEMO b.join() DA BI A SACEKAO B DA SE ZAVRSI
}

void Thread:: dispatch (){
    thread_dispatch();
}

int Thread::sleep (time_t t){
    //return time_sleep(t);
    return 0;
}

void Thread::threadWrapper(void* thread) {
    ((Thread*)thread)->run();
}

int Thread::getThreadID() {
    return thread_getID();
}



int Semaphore::wait (){
    return sem_wait(myHandle);

}

int Semaphore::signal (){
    return sem_signal(myHandle);
}

Semaphore::Semaphore(unsigned int init) {
    myHandle= nullptr;
    sem_open(&myHandle,init);
}

Semaphore::~Semaphore() {
    sem_close(myHandle);
}

char Console::getc() {
    return ::getc();
}

void Console::putc(char a) {
    ::putc(a);
}


PeriodicThread::PeriodicThread(time_t period) {

}
