// コクウキョウ - Kokūkyō
//            - Wys
// This code is free, and open source.

#ifndef     KOKUYO_VM_H
#define     KOKUYO_VM_H

#define     MEMORY_MAX  (1024 * 1024 * 1024 * 1024 * 4)
#define     MEMORY_MIN  (512)
#define     MEMORY_STD  (4 * 1024 * 1024 * 1024)

#define     THREAD_MAX  (128)
#define     THREAD_MIN  (1)
#define     THREAD_STD  (16)

#define     STACK_MIN   (1024)
#define     STACK_MAX   (1024 * 16)
#define     SEG_MAX     (8 * 1024 * 1024 * 1024)

#endif // KOKUYO_VM_H