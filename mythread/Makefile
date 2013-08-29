all: archive

archive: mythread.o
	ar rcs mythread.a *.o; rm *.o

mythread.o: mythread.c mythread.h
	gcc -c *.c

clean:
	rm mythread.a
