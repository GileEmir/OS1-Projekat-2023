.global _ZN5Riscv14supervisorTrapEv
.align 4

.extern _ZN5Riscv15handleInterruptEv
.extern _ZN5Riscv11handleTimerEv
.extern _ZN5Riscv13handleConsoleEv



_ZN5Riscv14supervisorTrapEv:
    j handleInterruptT
    j handleTimerT
    ld x0,0*0(sp)
    ld x0,0*0(sp)
    ld x0,0*0(sp)
    ld x0,0*0(sp)
    ld x0,0*0(sp)
    ld x0,0*0(sp)
    ld x0,0*0(sp)
    j handleConsoleT


handleInterruptT:
    # push all registers to stack
    addi sp, sp, -256
    .irp index, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    sd x\index, \index * 8(sp)
    .endr

    call _ZN5Riscv15handleInterruptEv

    # pop all registers from stack
    .irp index, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    ld x\index, \index * 8(sp)
    .endr
    addi sp, sp, 256

    sret

handleTimerT:
    # push all registers to stack
    addi sp, sp, -256
    .irp index, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    sd x\index, \index * 8(sp)
    .endr

    call _ZN5Riscv11handleTimerEv

    # pop all registers from stack
    .irp index, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    ld x\index, \index * 8(sp)
    .endr
    addi sp, sp, 256

    sret

handleConsoleT:
    # push all registers to stack
    addi sp, sp, -256
    .irp index, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    sd x\index, \index * 8(sp)
    .endr

    call _ZN5Riscv13handleConsoleEv

    # pop all registers from stack
    .irp index, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    ld x\index, \index * 8(sp)
    .endr
    addi sp, sp, 256

    sret
