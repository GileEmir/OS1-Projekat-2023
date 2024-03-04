#include "../h/MemAllocator.hpp"
#include "../h/print.hpp"
#include "../h/syscall_c.h"

const size_t freeMemSize = (size_t) (HEAP_END_ADDR) -(size_t )HEAP_START_ADDR;

MemAllocator::FreeMem* MemAllocator::freemem_head = (MemAllocator::FreeMem*)HEAP_START_ADDR; // JER STATICKI PODATAK NE MOZE U HEDERU DA SE ZADAJE VREDNOST
MemAllocator* MemAllocator::myMemAllocator = nullptr;
void* MemAllocator::mem_alloc(size_t size) { // ALGORITAM PRVOG NALASKA
    if (size <= 0) return nullptr;



    // Izračunavanje broja memorijskih blokova potrebnih za podatke
    size_t brojBlokovaZaPodatke = size;

    // Izračunavanje ukupne potrebne veličine za alocirani memorijski blok (uključujući zaglavlje)
    size_t ukupnaVelicina = brojBlokovaZaPodatke * MEM_BLOCK_SIZE+MEM_BLOCK_SIZE;

    bool r=false;
    FreeMem* trenutni = freemem_head;
    for (; trenutni != nullptr; trenutni = trenutni->next) {
        if (trenutni->size >= ukupnaVelicina) {
            // Provera da li u bloku ima dovoljno mesta za zaglavlje
            if (trenutni->size-ukupnaVelicina >2*MEM_BLOCK_SIZE) {
                if(trenutni==freemem_head) r=true;
                FreeMem* tr=trenutni;
                uint64 siz=trenutni->size;
                FreeMem* nex=trenutni->next;
                FreeMem* pre=trenutni->prev;

                // Podela bloka na alocirani segment i novi slobodni segment
                trenutni=(FreeMem*)((char*)trenutni+ukupnaVelicina);
                trenutni->size=siz-ukupnaVelicina;
                trenutni->prev=pre;
                if(pre!= nullptr){
                    pre->next=trenutni;
                }
                trenutni->next=nex;
                if(nex!=0){
                    nex->prev=trenutni;
                }
                if(r) freemem_head=trenutni;

                //Popravljanje informacija o tek zauzetom  bloku
                tr->next= nullptr;
                tr->prev= nullptr;
                tr->size=ukupnaVelicina;

                return (void*)((char*) tr+MEM_BLOCK_SIZE);
            } else {
                // Koristi ceo slobodan blok za alocirani segment
                if(trenutni==freemem_head) r=true;
                if(r) freemem_head=trenutni->next;
                if(trenutni->prev!=0){
                    trenutni->prev->next=trenutni->next;
                }
                if(trenutni->next!=0){
                    trenutni->next->prev=trenutni->prev;
                }
                trenutni->prev= nullptr;
                trenutni->next= nullptr;
                //printFreeMem();
                // Ceo blok je alociran kao alocirani segment
                return (void*)((char*)trenutni + MEM_BLOCK_SIZE);
            }
        }
    }

    // Ako nije pronađen odgovarajući slobodan memorijski blok, vraća se nullptr
    return nullptr;
}

void MemAllocator::printFreeMem(){
    FreeMem* trenutni = freemem_head;
    for (; trenutni != nullptr; trenutni = trenutni->next) {
        printHexa((uint64)trenutni);
        putc('\n');
        printHexa(trenutni->size);
        putc('\n');
    }

}


int MemAllocator::mem_free(void *addr) {
    if (addr == nullptr) return -2;

    // Calculate the header size
    size_t headSize = MEM_BLOCK_SIZE;

    // Adjust the address to get the starting address of the allocated segment
    addr = (void*)((char*)addr - headSize);

    // Find the appropriate position to insert the freed block in the FreeMem list
    FreeMem* cur = nullptr;
    if (!freemem_head || (char*)addr < (char*)freemem_head) cur = nullptr;
    else {
        for (cur = freemem_head; cur->next != nullptr && (char*)addr > (char*)(cur->next); cur = cur->next);
    }

    FreeMem* tmp = (FreeMem*)addr;
    tmp->prev = cur;
    if (cur!=0) tmp->next = cur->next;
    else tmp->next = freemem_head;
    if (tmp->next!=0) tmp->next->prev = tmp;
    if (cur!=0) cur->next = tmp;
    else freemem_head = tmp;

    // Attempt to merge with neighboring free segments
    if (tmp->next!=0 && (char*)((char*)tmp + tmp->size) == (char*)tmp->next) {
        tmp->size += tmp->next->size;
        tmp->next = tmp->next->next;
        if (tmp->next) tmp->next->prev = tmp;
    }

    if (tmp->prev!=0 && (char*)((char*)tmp->prev + tmp->prev->size) == (char*)tmp) {
        tmp->prev->size += tmp->size;
        tmp->prev->next = tmp->next;
        if (tmp->next) tmp->next->prev = tmp->prev;
    }
    //printFreeMem();
    return 0;
}



MemAllocator *MemAllocator::getInstance() {

    if (myMemAllocator == nullptr) {
        freemem_head = (FreeMem*)HEAP_START_ADDR;
        freemem_head->next = nullptr;
        freemem_head->prev = nullptr;
        freemem_head->size = (size_t)HEAP_END_ADDR -(size_t )HEAP_START_ADDR;
        myMemAllocator = (MemAllocator*)MemAllocator::mem_alloc((sizeof(MemAllocator)+MEM_BLOCK_SIZE-1)/MEM_BLOCK_SIZE);
    }
    return myMemAllocator;
}