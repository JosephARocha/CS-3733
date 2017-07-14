/*********************************************************************************
driver2.c
Date: June 6, 2017
Author: Joseph A. Rocha
Purpose:
	This C program demonstrates the myio library by opening and output file and
	making sure the output file contains lines from the input file but single spaced.

Example Invocation:
	<file_name> <input_file> <output_file> 
*********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "myio.h"

int main(int argc, char *argv[]){
	if(argc != 3){
		fprintf(stderr, "Error: Incorrect Invocation...\n");
		fprintf(stderr, "Example Invocation: <program_name> <input_file> <output_file>\n");
		exit(-1);
	}
	
	FILE *inputFD;
	FILE *outputFD;
	char *data;

	inputFD = fopen(argv[1], "r");
	if(inputFD == NULL){
		perror("Could Not Open File");
	}

	outputFD = fopen(argv[2], "w");
    if(outputFD == NULL){
		close(inputFD);
        perror("Could Not Open and/or Create File");
    }

	char lastChar = 0;
	while((data = ReadLineFile(inputFD)) != NULL){
		char *freeThis = data;
		while(*data != '\0'){
			if(lastChar == ' ' && *data == ' '){
				lastChar = *data;
				data++;
				continue;
			}
			fputc(*data, outputFD);
			lastChar = *data;
			data++;
		}
		free(freeThis);
		fputc('\n', outputFD);
	}

	fclose(inputFD);
	fclose(outputFD);
}
