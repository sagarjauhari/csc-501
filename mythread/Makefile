all: archive tests

archive: mythread.o
	ar rcs mythread.a *.o; rm *.o

mythread.o: mythread.c mythread.h
	gcc -c *.c

clean:
	rm mythread.a; cd test; make clean;

tests:
	cd test;make
