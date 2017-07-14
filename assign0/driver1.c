/***********************************************************************
driver1.c
Date: June 1, 2017
Author: Joseph A. Rocha
Purpose:
	This C program demonstrates the myio library By 
	asking the user to enter in x ints, y doubles, and 
	z strings. It keeps track of the maximum integer, double
	and longest string.

Example Invocation:
	<filename> 1 2 2
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myio.h"

int main(int argc, char *argv[]){
	if(argc != 4){
		fprintf(stderr, "Error: Invalid Number of Args\n");
		fprintf(stderr, "Example Invocation: <program_name> 1 2 2\n");
		exit(-1);
	}
	int x = atoi(argv[1]);
	int y = atoi(argv[2]);
	int z = atoi(argv[3]);
	double dVal;
	double maxdVal;
	int iVal;
	int maxiVal;
	char * string;
	char * maxString;

	if(x > 0){
	printf("Enter %d integers:", x);
	iVal = ReadInteger();
	maxiVal = iVal;
	printf("%d\n", iVal);
	x--;
	for(x; x > 0; x--){
		iVal = ReadInteger();
		if(iVal > maxiVal)
			maxiVal = iVal;
		printf("%d\n", iVal);
	}
	}
	
	if(y > 0){
	printf("Enter %d doubles:", y);
    dVal = ReadDouble();
    maxdVal = dVal;
    printf("%lf\n", dVal);
    y--;
    for(y; y > 0; y--){
        dVal = ReadDouble();
        if(dVal > maxdVal)
            maxdVal = dVal;
        printf("%lf\n", dVal);
    }
	}

	if(z > 0){
	printf("Enter %d strings:", z);
	string = ReadLine();
	maxString = string;
	printf("%s\n", string);
	z--;
	for(z; z > 0; z--){
        string = ReadLine();
		printf("%s\n", string);
        if(strlen(string) > strlen(maxString)){
			free(maxString);
			maxString = string;
		}else{
			free(string);
		}
    }
	}

	if(atoi(argv[1]) > 0) 
		printf("Max Integer was %d\n", maxiVal);
	if(atoi(argv[2]) > 0) 
		printf("Max Double was %lf\n", maxdVal);
	if(atoi(argv[3]) > 0) 
		printf("Max String was %s\n", maxString);
	free(maxString);
}
