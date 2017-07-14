all: part2 part3

part2: assign3part2.c pagetable.c phypages.c
	gcc -o part2 assign3part2.c pagetable.c phypages.c -I.

part3: assign3part3.c pagetable.c phypages.c
	gcc -o part3 assign3part3.c pagetable.c phypages.c -lm -I.

clean: 
	rm pagetable.o
	rm phypages.o
