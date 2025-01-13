// コクウキョウ - Kokūkyō
//            - Wys
// This code is free, and open source.

#ifndef SET_H
#define SET_H

#define     nop         0x00

#define     movb        0X01
#define     addb        0x02
#define     subb        0x03
#define     mulb        0x04
#define     modb        0x05

#define     movw        0x06
#define     addw        0x07
#define     subw        0x08
#define     mulw        0x09
#define     divw        0x0A
#define     modw        0x0B

#define     movd        0x0C
#define     addd        0x0D
#define     subd        0x0E
#define     muld        0x0F
#define     divd        0x11
#define     modd        0x12

#define     movq        0x13
#define     addq        0x14
#define     subq        0x15
#define     mulq        0x16
#define     divq        0x17
#define     modq        0x18

#define     jmp         0x19
#define     je          0x1A
#define     jne         0x1B
#define     jl          0x1C
#define     jg          0x1D
#define     jle         0x1E
#define     jlg         0x1F

#define     call        0x20
#define     ret         0x21

#define     pushb       0x22
#define     pushw       0x23
#define     pushd       0x24
#define     pushq       0x25

#define     popb        0x26
#define     popw        0x27
#define     popd        0x28
#define     popq        0x29

#define     syscall     0x2A

#define     movs        0x2B
#define     adds        0x2C
#define     subs        0x2D
#define     muls        0x2E
#define     divs        0x2F
#define     mods        0x30

#define     cmpb        0x31
#define     cmpw        0x32
#define     cmpd        0x33
#define     cmpq        0x34

#define     xorb        0x35
#define     xorw        0x36
#define     xord        0x37
#define     xorq        0x38

#define     andb        0x39
#define     andw        0x3A
#define     andd        0x3B
#define     andq        0x3C

#define     orb         0x3D
#define     orw         0x3E
#define     ord         0x3F
#define     orq         0x40

#define     lea         0x41

#define     halt        0xFF

#endif // SET_H