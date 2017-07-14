#include <stdio.h>
#include <stdlib.h>
#include "pslibrary.h"

int main(int argc, char *argv[]){
	int inputs[7] = {0};
	 int i;
	int strSize = 0;
	//Checks to see if there is a correct number of args
	if(argc != 8){
		printf("Error: Incorrect Number of Arguments...\n");
		printf("Sample Invocation: <prog name> 1 2 3 4 5 6 7\n");
		exit(-1);
	}

	//Prints project main header and puts args into array of ints
	printf("Assignment 2 program was written by Joseph Rocha\n");
	printf("input: ");
	for(i = 1; i < argc; i++){
		inputs[i-1] = atoi(argv[i]);
		printf("%d ", inputs[i-1]);
	}
	printf("\n");

	//Calculates the sum of the last 6 integers
	for(i = 1; i < argc-1; i++){
		strSize += inputs[i];
	}

	//Creates two strings with size of the last 6 integers
	char *proc1 = malloc((strSize + 1));
	char *proc2 = malloc((strSize + 1));
	
	fcfs(proc1, proc2, inputs[1], inputs[2], inputs[3], inputs[4], inputs[5], inputs[6]);
	display("Part 1\n", proc1, proc2);

	sjf(proc1, proc2, inputs[1], inputs[2], inputs[3], inputs[4], inputs[5], inputs[6]);
	display("Part 2\n", proc1, proc2);

	psjf(proc1, proc2, inputs[1], inputs[2], inputs[3], inputs[4], inputs[5], inputs[6]);
	display("Part 3\n", proc1, proc2);


	rr(proc1, proc2, inputs[0], inputs[1], inputs[2], inputs[3], inputs[4], inputs[5], inputs[6]);
	display("Part 4\n", proc1, proc2);
	
	free(proc1);
	free(proc2);
}
