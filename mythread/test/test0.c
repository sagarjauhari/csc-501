#include <stdio.h>
#include "../mythread.h"
#include "../threadq.h"

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
