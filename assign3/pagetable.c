#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "pagetable.h"

/****************************************************************
int **createPageTable(int size)

Purpose: 
	Creates a 2D page table. Each page number corresponds to a
	[0]Frame number that it was allocated to (init -1) and
	[1]Valid or invalid for determining if another page 
	took the frame away.

Parameters:
    size	Number of entries in the array

Returns
	pageTable	Pointer to the page table.
****************************************************************/
int **createPageTable(int size){
	int **pageTable;
	pageTable = malloc(sizeof(int *) * size);
	if(pageTable == NULL){
		printf("Failed to allocate page table\n");
		return NULL;
	}
    int i;
	for(i = 0; i < size; i++){
		pageTable[i] = malloc(sizeof(int) * 2);
		if(pageTable[i] == NULL){
			printf("Failed to allocate page table\n");
			for(i; i >= 0; i--){
				free(pageTable[i]);
			}
			free(pageTable);
		}
		pageTable[i][0] = -1;
		pageTable[i][1] = 0;
	}
    return pageTable;
}

/****************************************************************
int freePageTable(int **pageTable, int size){

Purpose:
    Handy function for freeing the page table.

Parameters:
	int **pageTable		Pointer to the structure
    size    			Number of entries in the array
****************************************************************/

int freePageTable(int **pageTable, int size){
	int i;
	for(i = 0; i < size; i++){
		free(pageTable[i]);
	}
	free(pageTable);
}
