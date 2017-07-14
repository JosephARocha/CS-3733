/**************************************************
myio.c (LIBRARY)
Date: May 1, 2017
Author: Joseph A. Rocha

Purpose: 
	This library provides simple C IO functions.
**************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "myio.h"

/****************************************************************
int ReadInteger(void)

Purpose: 
	Reads a line using ReadLine() and parses using sscanf.
	If theres an error the user is given a chance to try again.

Returns:
	int val		Value that was read using sscanf
****************************************************************/
int ReadInteger(void){
    int val;
    char *line;
	char throwaway;

	while(sscanf((line = ReadLine()), " %d %c", &val, &throwaway) != 1){
		fprintf(stderr, "Error: Invalid Input, Try Again...\n");
		free(line);
	}
	free(line);
	return val;
}

/****************************************************************
double ReadDouble(void)

Purpose:
    Reads a line using ReadLine() and parses using sscanf.
    If theres an error the user is given a chance to try again.

Returns:
    doublr val     Value that was read using sscanf
****************************************************************/
double ReadDouble(void){
    double val;
    char *line;
    char throwaway;
    while(sscanf((line = ReadLine()), " %lf %c", &val, &throwaway) != 1){
        fprintf(stderr, "Error: Invalid Input, Try Again...\n");
        free(line);
    }
    free(line);
    return val;
}

/****************************************************************
char *ReadLine(void)

Purpose:
    Reads a line from STDIN using ReadLineFile().

Implemented By:
	ReadInteger()
	ReadDouble()

Returns:
    A char * (String) containing the line read from STDIN
****************************************************************/
char *ReadLine(void){
	return(ReadLineFile(stdin));
}

/****************************************************************
char *ReadLineFile(FILE *infile)

Purpose:
    Reads a line from FILE infile one character at a time and 
	adds it into a string dynamically allocated. The newline
	character is NOT added.

Implemented By:
    ReadLine()

Returns:
	char *string	String containing the line read
    NULL			On EOF

Notes:
	Allocates on char by char basis, potentially resulting in 
	inneficient time cost. Might be better to sacrifice space for
	speed by allocating more than one char at a time.
****************************************************************/
char *ReadLineFile(FILE *infile){
	char *string = NULL;
	char c = 0;
	int size = 0;//Really describes the size of the string without null terminator char

	while((c = fgetc(infile)) != '\n'){
    	if(c == EOF){
			free(string);
			return NULL;
		}
    	string = realloc(string, (size+2)*sizeof(char));
		if(string == NULL){
			perror("Memory Error");
			exit(-1);
		}
    	string[size++] = c;
	}
	string[size] = '\0';
	return string;
}
