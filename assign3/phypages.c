#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "phypages.h"

int **frameTable;
int tableSize = 0;
int LClock = 0;

/****************************************************************
int **createFrameTable(int size)

Purpose: 
	Creates a 2D array of the frame table. At each Index (frame)
	we have a [0]page association and [1] LC Value.

Parameters:
    int size	Number of frames.

Returns:
	frameTable	Pointer to the newly created frame table
	NULL		On Error
****************************************************************/
int **createFrameTable(int size){
	tableSize = size;
    frameTable = malloc(sizeof(int *) * size);
	if(frameTable == NULL){
		printf("Failed to allocate frame table\n");
		return NULL;
	}
	int i;
	for(i = 0; i < size; i++){
		frameTable[i] = malloc(2 * sizeof(int));
		if(frameTable[i] == NULL){
			printf("Failed to allocate frame table\n");
			for(i; i >= 0; i--){
				free(frameTable[i]);
			}
			free(frameTable);
			return NULL;
		}
		frameTable[i][0] = -1; //Page allocated to this frame
		frameTable[i][1] = 0;  //Value used to find LC
	}

    return frameTable;
}

/****************************************************************
int map(int **pageTable,int page)

Purpose:
    When a page access comes in and the associated frame combo
	is invalid we find an empty frame to put it in.
	
	If all frames are full we kick out the one with the lowest LC
	Value.

Parameters:
    int **pageTable		Pointer to the page table to reset valid bit
	int page			# of Page accessed

Returns
	i			First empty frame number that was allocated
	LRU_Frame	Frame number now associated to param page.
****************************************************************/
int map(int **pageTable,int page){
	int i;
	int LRU_Frame = 1;
	for(i = 1; i < tableSize; i++){
		if(frameTable[i][1] < frameTable[LRU_Frame][1]){
        	LRU_Frame = i;
        }

		if(frameTable[i][0] == -1){
			frameTable[i][0] = page;
			frameTable[i][1] = LClock++;
			return i;
		}
	}
	pageTable[frameTable[LRU_Frame][0]][1] = 0;//Frames page is now invalid
	frameTable[LRU_Frame][0] = page; //Set frame to its new page.
	frameTable[LRU_Frame][1] = LClock++;
	return LRU_Frame;//No Empty Frames!
}

/****************************************************************
int accessedFrame(int frame)

Purpose:
    If in our main program, the page was valid we reset the LC
	value to the current global LC (Least clock) value.

Parameters:
    int frame	Frame that was accessed

Returns
	frame	Number of frame updated
****************************************************************/
int accessedFrame(int frame){
	frameTable[frame][1] = LClock++;
	return frame;
}

/****************************************************************
int freeFrameTable()

Purpose:
    Handy function to free our frame table.
****************************************************************/
int freeFrameTable(){
	int i;
	for(i = 0; i < tableSize; i++){
		free(frameTable[i]);
	}
	free(frameTable);
}
