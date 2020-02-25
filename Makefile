waka : waka.o setup.o loop.o ku.o word.o
	gcc -o waka waka.o setup.o loop.o ku.o word.o -Wall

waka.o : waka.c
	gcc -c waka.c -Wall

setup.o : setup.c
	gcc -c setup.c -Wall

loop.o : loop.c
	gcc -c loop.c -Wall

ku.o : ku.c
	gcc -c ku.c -Wall

word.o : word.c
	gcc -c word.c -Wall

clean :
	rm *.o waka
