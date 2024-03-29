#ifndef _opcodes_hpp
#define _opcodes_hpp

enum Opcodes: uint64 {
    MEM_ALLOC       = 0x01,
    MEM_FREE        = 0x02,
    THREAD_CREATE   = 0x11,
    THREAD_EXIT     = 0x12,
    THREAD_DISPATCH = 0x13,
    THREAD_JOIN     = 0X14,
    THREAD_ID       = 0x15,
    SEM_OPEN        = 0x21,
    SEM_CLOSE       = 0x22,
    SEM_WAIT        = 0x23,
    SEM_SIGNAL      = 0x24,
    TIME_SLEEP      = 0x31,
    GETC            = 0x41,
    PUTC            = 0x42,
    GOTO_USER       = 0x50,
    GOTO_SYSTEM     = 0x51,
};

#endif //_opcodes_hpp