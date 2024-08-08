#include <stdio.h>
#include "interface.h"

#define my_atomic_add(_new_,_addr_) \
{          asm volatile("faaw   %0,0(%1)\n\t"  \
               :"=r"(_new_):"r"(_addr_):"memory");        \
               _new_++;\
}

void my_mutex_lock(volatile int* my_lock)
{
    unsigned int __addr,__tmpi;
    __asm__ __volatile__(
        "        memb\n"
        "        ldi      %1,%2\n"
        "1:      faaw     %0,0(%1)\n"
        "        bne      %0,1b\n"
        "        memb\n"
      : "=&r"  (__tmpi),
        "=&r"  (__addr)
      :  "m" (*my_lock)
      : "memory");
    return;
}
int my_mutex_unlock(volatile int* my_lock)
{ 
    unsigned int __addr ;
    __asm__ __volatile__(
        "        memb\n"
        "        ldi      %0,%1\n"
        "        stw      $31,0(%0)\n"
        "        memb\n"
      : "=&r"  (__addr)
      : "m" (*my_lock)
      : "memory");
    return;
}



