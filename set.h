// コクウキョウ - Kokūkyō
//            - Wys
// This code is free, and open source.

#ifndef SET_H
#define SET_H

#define     nop         0x00

#define     mov         0x01
#define     add         0x02
#define     sub         0x03
#define     mul         0x04
#define     div         0x05

#define     jmp         0x06
#define     je          0x07
#define     jne         0x06
#define     jl          0x08
#define     jg          0x09
#define     jle         0x0A
#define     jge         0x0B

#define     cmp         0x0C
#define     lea         0x0D

#define     push        0x0E
#define     pop         0x0F

#define     byte        0x10
#define     word        0x11
#define     dword       0x12
#define     qword       0x13
#define     dqword      0x14

#define     syscall     0x15
#define     call        0x16
#define     ret         0x17

#define     mod         0x18

#define     halt        0xFF

#define     STACK_MIN   (1024)
#define     STACK_MAX   (1024 * 16)

#define     SEG_MAX     (8 * 1024 * 1024 * 1024)

#define     INS_COUNT   27

#endif // SET_H