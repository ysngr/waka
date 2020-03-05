waka : waka.h waka.o setup.o loop.o view.o
	gcc -o waka waka.o setup.o loop.o view.o -Wall -lncursesw

waka.o : waka.c
	gcc -c waka.c -Wall

setup.o : setup.c
	gcc -c setup.c -Wall

loop.o : loop.c
	gcc -c loop.c -Wall

view.o : view.c
	gcc -c view.c -Wall -Wno-format-security

clean :
	rm *.o waka
