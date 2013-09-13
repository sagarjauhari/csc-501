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
  printf("t1 start\n");
  printf("t1 going to yield\n");
  MyThreadYield();
  printf("t1 again\n");
  printf("t1 exiting\n");
  MyThreadExit();
  printf("t1 did not exit\n");
}

void t0(void * dummy)
{
  printf("t0 start\n");
  MyThread* th1 = MyThreadCreate(t1, (void *)1);
  printf("t0 going to join\n");
  MyThreadJoin(th1);
  printf("t0 again\n");
  MyThreadExit();
}
int main()
{
  MyThreadInit(t0, NULL);
}
