#include <stdio.h>
#include "interface.h"
#include "athread.h"

#define my_atomic_add(_new_,_addr_) \
{          asm volatile("ldw_inc   %0,0(%1)\n\t"  \
               :"=r"(_new_):"r"(_addr_):"memory");        \
                _new_++;\
}
inline unsigned long rpcc()
{
    unsigned long time;
    asm("rtc %0" : "=&r"(time) ::"memory");
    return time;
}

#define master_count 1000000

extern void slave_func();
int my_num=5;
unsigned long local_my_num[64]={5};
unsigned long aver_latency[64]={5};
int flag=0;

int main(int argc, char** argv)
{
  int thread_num;
  int t;
  int j;
  int check = my_num;
  
  thread_num = 4;
  
  if(argc > 1)
    thread_num = atoi(argv[1]);
  athread_init();
  printf("init:%d\n",my_num);

#ifdef _SPAWN
  printf("spawn\n");
  athread_spawn(func,0);
  athread_join();
  athread_halt();
#else
  for (t=0; t<thread_num; t++)
    athread_create(t, func, 0);
  unsigned long st=rpcc();
  for (t=0;t<master_count;t++)
  {
     // printf("%d,",flag);
//     my_mutex_lock(&flag);
////      printf("1flag:%d\t",flag);
  //    my_num--;
    //  my_mutex_unlock(&flag);
 // my_atomic_add(flag,&my_num);
//    
  }
  unsigned long et= rpcc();
  for(t=0; t<thread_num; t++)
  {
    athread_wait(t);
    athread_end(t);
  }
  printf("result:%d,%d\n",my_num,flag);
  printf("faaw latency : \n");
  unsigned long sum=0;
  for(t=0; t<thread_num; t++)
  {
    printf("%lu, ", aver_latency[t]);
    if(t==15) printf("\n");
    sum+=aver_latency[t];
  }
  printf("\n");
  printf("master aver latency= %lu\n", (et-st)/master_count);
  printf("slave aver latency= %lu\n", sum/t);
#endif
  check =check-master_count+64*1000;
  if (check -my_num<0.000001)
      printf("right\n");
  else
      printf("error\n");
  return 0;
}
