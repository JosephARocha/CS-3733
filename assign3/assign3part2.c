/**********************************************************************
assign3part2.c
July 14, 2017
Author: Joseph A. Rocha

Purpose: This program simulated page/frame management implemented with
LRU policy

Sample Invocation:
	<progname> <input_file>
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "pagetable.h"
#include "phypages.h"

int main(int argc, char* argv[]){
    
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
    if((outFile = open("output-part2test", O_WRONLY | O_CREAT | O_TRUNC, 0600)) == -1){
		perror("Unable to write to file");
		exit(-1);
    }

	int **pageTable = createPageTable(32);
	int **frameTable = createFrameTable(8);

    unsigned long virtualAddress;
 	unsigned long offset;
    unsigned long page;
	unsigned long  frame;
	unsigned long physicalAddress;
	unsigned long pageFaults = 0;
    while(read(inFile, &virtualAddress, sizeof(unsigned long)) == sizeof(unsigned long)){
		page = virtualAddress >> 7;
		if(pageTable[page][1] == 0){
			pageFaults++;
			frame = map(pageTable, page);
			pageTable[page][0] = frame;
			pageTable[page][1] = 1;
		}else{
			frame = accessedFrame(pageTable[page][0]);			 
		}
		offset = virtualAddress & ((1 << 7)-1);//2^offset -1 
		physicalAddress = (frame << 7) + offset;
		printf("Virtual Address = 0x%lx\nPage = %d\nFrame = %d\nOffset = %lx\nPhysical Address = 0x%lx\n\n", virtualAddress, (int)page, (int)frame, offset, physicalAddress);
    	write(outFile, &physicalAddress, sizeof(unsigned long));
	}
	printf("Page Faults: %lu\n", pageFaults);
	freeFrameTable(frameTable);
	freePageTable(pageTable, 32);
}
