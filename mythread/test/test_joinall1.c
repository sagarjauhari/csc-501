#include <stdio.h>
#include "../mythread.h"
#include "../threadq.h"

/*
Output:
	t0 start
	t0 going to join
	t1 start
	t1 going to yield
	t1 again
	t1 exiting
	t0 again
*/
void t1(void * dummy)
{
  printf("t1\n");
  MyThreadYield();
  printf("t1 again\n");
  MyThreadExit();
}

void t2(void * dummy)
{
  printf("t2\n");
  MyThreadYield();
  printf("t2 again\n");
  MyThreadExit();
}

void t0(void * dummy)
{
  printf("t0\n");
  MyThread* th1 = MyThreadCreate(t1, (void *)1);
  MyThread* th2 = MyThreadCreate(t2, (void *)2);
  
  MyThreadJoinAll();
  
  printf("t0 bye\n");
  MyThreadExit();
}
int main()
{
  MyThreadInit(t0, NULL);
}
