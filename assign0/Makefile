all: driver1 driver2

driver1: driver1.c myio.c
	gcc -o driver1 driver1.c myio.c -I.

driver2: driver2.c myio.c
	gcc -o driver2 driver2.c myio.c -I.

clean: 
	rm myio.o
