all: assign1
tests: test1 test2 test3 test4 test5 test6

assign1: assign1.c pslibrary.c
	gcc -o assign1 assign1.c pslibrary.c

test1:
	assign1 3 8 7 3 6 3 2 > Test-1.txt

test2:
	assign1 3 8 7 3 6 7 2 > Test-2.txt

test3:
	assign1 4 8 7 3 6 1 2 > Test-3.txt

test4:
	assign1 3 3 3 4 2 1 2 > Test-4.txt

test5:
	assign1 3 3 2 3 2 1 2 > Test-5.txt

test6:
	assign1 3 5 2 5 4 1 1 > Test-6.txt
