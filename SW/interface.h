#ifndef INTERFACE_H
#define INTERFACE_H
void my_mutex_lock(volatile int* my_lock);
int my_mutex_unlock(volatile int* my_lock);

void slave_my_mutex_lock(volatile int* my_lock);
int slave_my_mutex_unlock(volatile int* my_lock);
#endif
