#ifndef PROJECT_BASE_MEMALLOCATOR_HPP
#define PROJECT_BASE_MEMALLOCATOR_HPP

#include "../lib/hw.h"

class MemAllocator{
public:
    struct FreeMem{
        FreeMem* next;
        FreeMem* prev;
        size_t size;
        //FreeMem(size_t freeMemSize):next(nullptr), prev(nullptr), size(freeMemSize){}
    };
    MemAllocator(MemAllocator &) = delete;
    void operator=(const MemAllocator&) = delete;

    static MemAllocator *getInstance();

    static void* mem_alloc(size_t size);

    static int mem_free(void* addr);

    static void printFreeMem();
private:
    static MemAllocator* myMemAllocator;
    MemAllocator(){}
    static FreeMem* freemem_head;



};

#endif //PROJECT_BASE_MEMALLOCATOR_HPP
