/**********************************************************************
assign3part1.c
July 14, 2017
Author: Joseph A. Rocha

Purpose: This program simulated page/frame managment in C with already
defined bindings.

Sample Invocation:
	<progname> <input_file>
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

unsigned long pow2(unsigned long to);

int main(int argc, char* argv[]){
	int table[32] = {2, 4 ,1, 7, 3 ,5 ,6};
	if(argc != 2){
		printf("Error! Usage: <progname> <inputFile>\n");
		exit(-1);
	}
    int inFile;
    if((inFile = open(argv[1], O_RDONLY)) == -1){
		perror("Unable to open file");
		exit(-1);
    }
	int outFile;
    if((outFile = open("output-part1test", O_WRONLY | O_CREAT | O_TRUNC, 0600)) == -1){
		perror("Unable to write to file");
		exit(-1);
    }

    unsigned long virtualAddress;
 	unsigned long offset;
    unsigned long page;
	unsigned long  frame;
	unsigned long physicalAddress;
    while(read(inFile, &virtualAddress, sizeof(unsigned long)) == sizeof(unsigned long)){
		page = virtualAddress >> 7;
		frame = table[page];
		offset = virtualAddress & ((1 << 7)-1);//2^offset -1 
		physicalAddress = (frame << 7) + offset;
		printf("Virtual Address = 0x%lx\nPage = %lx\nFrame = %lx\nOffset = %lx\nPhysical Address = 0x%lx\n\n", virtualAddress, page, frame, offset, physicalAddress);
    	write(outFile, &physicalAddress, sizeof(unsigned long));
	}
}
