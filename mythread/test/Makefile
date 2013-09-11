# Test Cases
all: one passing ping tree test1

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

test1: test1.c
	gcc test1.c ../mythread.a -lpthread -o test1.out

clean:
	rm *.out
