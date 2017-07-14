/**********************************************************************
assign3part3.c
July 14, 2017
Author: Joseph A. Rocha

Purpose: This program simulated page/frame management implemented with
LRU policy

Sample Invocation:
	part3 128 4096 1024 part2sequence
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include "pagetable.h"
#include "phypages.h"

int main(int argc, char* argv[]){
    
	if(argc != 5){
		printf("Error! Usage: <progname> <BytesofPage> <SizeofVirtualMemory> <SizeOfPhysicalMemory> <inputFile>\n");
		exit(-1);
	}
    int inFile;
    if((inFile = open(argv[4], O_RDONLY)) == -1){
		perror("Unable to open file");
		exit(-1);
    }
	int outFile;
    if((outFile = open("output-part3test", O_WRONLY | O_CREAT | O_TRUNC, 0600)) == -1){
		perror("Unable to write to file");
		exit(-1);
    }

	int pageNum = atoi(argv[2]) / atoi(argv[1]);
	int frameNum = atoi(argv[3]) / atoi(argv[1]);
	int offsetBits = floor(log(atoi(argv[1]))/log(2));

	if(frameNum < 2){
		printf("Error: There CANNOT be less than 2 frames, OS needs 1!\n");
		exit(-1);
	}

	int **pageTable = createPageTable(pageNum);
	int **frameTable = createFrameTable(frameNum);

    unsigned long virtualAddress;
 	unsigned long offset;
    unsigned long page;
	unsigned long  frame;
	unsigned long physicalAddress;
	unsigned long pageFaults = 0;

    while(read(inFile, &virtualAddress, sizeof(unsigned long)) == sizeof(unsigned long)){
		page = virtualAddress >> offsetBits;
		if(pageTable[page][1] == 0){
			pageFaults++;
			frame = map(pageTable, page);
			pageTable[page][0] = frame;
			pageTable[page][1] = 1;
		}else{
			frame = accessedFrame(pageTable[page][0]);			 
		}
		offset = virtualAddress & ((1 << offsetBits)-1);
		physicalAddress = (frame << offsetBits) + offset;
		printf("Virtual Address = 0x%lx\nPage = %d\nFrame = %d\nOffset = %lx\nPhysical Address = 0x%lx\n\n", virtualAddress, (int)page, (int)frame, offset, physicalAddress);
    	write(outFile, &physicalAddress, sizeof(unsigned long));
	}
	printf("Page Faults: %lu\n", pageFaults);
	freeFrameTable(frameTable);
	freePageTable(pageTable, pageNum);
}
