# Test Cases
all: one passing ping tree

fib: fib.c
	gcc fib.c ../mythread.a -o fib.out

one: one.c
	gcc one.c ../mythread.a -o one.out

passing: passing.c
	gcc passing.c ../mythread.a -o passing.out

ping: ping.c
	gcc ping.c ../mythread.a -o ping.out

tree: tree.c
	gcc tree.c ../mythread.a -o tree.out

clean:
	rm *.out
