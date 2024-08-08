#include <stdio.h>
//#include "task.h"
#include <slave.h>


#define my_atomic_add(_new_,_addr_) \
{          asm volatile("faaw   %0,0(%1)\n\t"  \
               :"=r"(_new_):"r"(_addr_):"memory");        \
                 _new_++;\
}
#define atomic_add_1(_addr_) \
{         unsigned long _new_;\
          asm volatile("faaw   %0,0(%1)\n\t"  \
               :"=r"(_new_):"r"(_addr_):"memory");        \
}

#define TMAX 1000000

inline unsigned long rtc()
{
  unsigned long rpcc = 0;
  asm volatile ("rcsr %0, 4":"=&r"(rpcc)::"memory");
  return rpcc;
}


unsigned int test_count=101;
unsigned int add()
{
  //test_count=test_count+1;

  unsigned int tmp;
  //asm volatile("addl %0,1,%0":"+&r"(test_count)::"memory");
  asm volatile("addl %0,67,%0":"+&r"(test_count)::"memory");
  //" ldw %[test_count],%[tmp]\n"
  //" addw %[test_count],101,%[test_count]\n" 
  //__asm__ __volatile__ (           \
  ////" ldw %[tmp],%[test_count]\n"
  ////" ldw %[test_count],%[tmp]\n"
  ////" addw %[tmp],101,%[tmp]\n" 
  //" addw %[tmp],101,%[test_count]\n" 
  //: [tmp] "+r" (tmp)
  //: [test_count] "r" (test_count)
  //: "memory");
  printf("test_count=%u\n",test_count);          
  return tmp;
}

extern unsigned long my_num,flag;
extern unsigned long local_my_num[64];
extern unsigned long aver_latency[64];

void func()
{
    int i,j;
    unsigned long temp=0;
//    volatile int flag=0;
    char c;
 // printf("my_id,%d",_MYID);
 // printf("\n");
    i=athread_get_id(-1);
    j=athread_get_core(-1);
//    printf("%d,",my_num);
    //unsigned int ret=add();
//    printf("return value=%u\n",ret);
//    ret=add();
//    ret=add();
//    printf("return value=%u\n",ret);
    unsigned long *addr=&(local_my_num[_MYID]); //local
    //unsigned long *addr=&(my_num); //share
    unsigned long st = rtc();
   for (i=0;i<TMAX;i++)    
    {
      // slave_my_mutex_lock(&flag);
       // my_num++;
       //slave_my_mutex_unlock(&flag);
     //atomic_add_1(&my_num);                
     atomic_add_1(addr);     
     //  atomic_add_1(&(local_my_num[_MYID]));                 
    //my_atomic_add(temp,&my_num);                
    }
    unsigned long et = rtc();
    if(_MYID==0) printf("total_count=%lu,each= %lu\n",et-st,(et-st)/TMAX);
    aver_latency[_MYID]= (et-st)/TMAX;
   // printf("each aver latency= %lu\n", aver_latency[_MYID]);
}
