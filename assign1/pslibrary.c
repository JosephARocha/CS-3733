#include <stdio.h>
#include <string.h>
#include "pslibrary.h"

void part0(char *s1, char *s2){
	strcpy(s1, "RRwwwwwRRRRRRRRR");
	strcpy(s2, "rrRRRRwwwwwwwwrrRRRRRRR");
}

float max(int a, int b) {
    if (a > b)
        return a;
    return b;
}

void display(char *heading, char *s1, char *s2){
	printf("\n%s", heading);
	printf("%s\n", s1);
	printf("%s\n\n", s2);
	int readyQProc1 = 0;
	int readyQProc2 = 0;
	int runningQProc1 = 0;
	int runningQProc2 = 0;
    int i = 0;

	for(i = 0; i < strlen(s1); i++){
		if(s1[i] == 'r')
   			readyQProc1 += 1;
        if(s1[i] == 'R')
            runningQProc1 += 1;
    }

 	for(i = 0; i < strlen(s2); i++){
        if(s2[i] == 'r')
            readyQProc2 += 1;
        if(s2[i] == 'R')
            runningQProc2 += 1;
    }

    float averageReadyQ = (readyQProc1 + readyQProc2)/2;
	float runTime = (float)(runningQProc1 + runningQProc2)/max(strlen(s1), strlen(s2));	 
	printf("%d %d %.1f %.5f\n", readyQProc1, readyQProc2, averageReadyQ, runTime);
}

void fcfsa(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2){	
   int i = 0;
   int place1 = 0;
   int place2 = 0; 
   
   for(i = x1; i > 0; i--){
   	s1[place1++] = 'R';
   	s2[place2++] = 'r';
   }

   for(i = x2; i > 0; i--){
    s2[place2++] = 'R';
   }

   for(i = y1; i > 0; i--){
   	s1[place1++] = 'w';
   }

   if(y1 < x2){
       for(i = 0; i < (x2-y1); i++)
           s1[place1++] = 'r';
   }

   for(i = 0; i < z1; i++){
       s1[place1++] = 'R';
   }


   for(i = y2; i > 0; i--){
   	s2[place2++] = 'w';
   }

   if(y2 < z1){
       for(i = 0; i < (z1-y2); i++)
	       s2[place2++] = 'r';

   }

   while(s1[place2] == 'R'){
       s2[place2++] = 'r';
   }

   for(i = 0; i < z2; i++){
       s2[place2++] = 'R';
   }
   s1[place1] = '\0';
   s2[place2] = '\0';
}
