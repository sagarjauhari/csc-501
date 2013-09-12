#include <stdio.h>
#include "../mythread.h"
#include "../threadq.h"

/*
Output:
	t0 start
	t1 start
	t2 start
	t0 again
	t1 again
	t2 again
	t0 bye
*/

void t0(void * dummy)
{
  printf("t0 start\n");
  MyThreadYield();
  printf("t0 again 1\n");
  MyThreadYield();
  printf("t0 again 2\n");
  printf("t0 bye\n");
  MyThreadExit();
}



int main()
{
  MyThreadInit(t0, NULL);
}
