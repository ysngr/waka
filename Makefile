waka : waka.o setup.o loop.o
	gcc -o waka waka.o setup.o loop.o -Wall -lncursesw

waka.o : waka.c
	gcc -c waka.c -Wall

setup.o : setup.c
	gcc -c setup.c -Wall

loop.o : loop.c
	gcc -c loop.c -Wall

clean :
	rm *.o waka
