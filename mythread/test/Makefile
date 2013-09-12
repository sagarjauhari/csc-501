# Test Cases
all: one passing ping tree test0 test1 test2

fib: fib.c
	gcc fib.c ../mythread.a -lpthread -o fib.out

one: one.c
	gcc one.c ../mythread.a -lpthread -o one.out

passing: passing.c
	gcc  passing.c ../mythread.a -lpthread -o passing.out

ping: ping.c
	gcc ping.c ../mythread.a -lpthread -o ping.out

tree: tree.c
	gcc tree.c ../mythread.a -lpthread -o tree.out

test0: test0.c
	gcc test0.c ../mythread.a -lpthread -o test0.out

test1: test1.c
	gcc test1.c ../mythread.a -lpthread -o test1.out

test2: test2.c
	gcc test2.c ../mythread.a -lpthread -o test2.out

clean:
	rm *.out
