#include <stdio.h>
#include <string.h>
#include "pslibrary.h"
#define READY  0
#define RUNNING  1
#define WAITING  2
#define DONE  3

static char stateChars[] = {'r','R','w',0};

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
	printf("%s\n", s2);
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

    float averageReadyQ = (float)(readyQProc1 + readyQProc2)/2;
	float runTime = (float)(runningQProc1 + runningQProc2)/max(strlen(s1), strlen(s2));	 
	printf("%d %d %.1f %.5f\n", readyQProc1, readyQProc2, averageReadyQ, runTime);
}

void fcfs(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2){	
  int i;                                   /* next string position (time) */
   int state1 = READY;                            /* start with both ready */
   int state2 = READY;
   int cpuLeft1 = x1;                       /* P1 next CPU burst remaining */
   int cpuLeft2 = x2;                       /* P2 next CPU burst remaining */
   int ioLeft1 = y1;        /* P1 next IO burst remaining, 0 if no more IO */
   int ioLeft2 = y2;        /* P2 next IO burst remaining, 0 if no more IO */
   
   for (i=0; (state1 != DONE) || (state2 != DONE); i++) {
                                /* running process completes its CPU burst */
      if ((state1 == RUNNING) && (cpuLeft1== 0)) {
         if (ioLeft1 == 0) {
            state1 = DONE;
            s1[i] = stateChars[state1];            /* terminate the string */
         }
         else
            state1 = WAITING;
      }  
      else if ((state2 == RUNNING) && (cpuLeft2 == 0) ) {
         if (ioLeft2 == 0) {
            state2 = DONE;
            s2[i] = stateChars[state2];
         }
         else
            state2 = WAITING;
      }  
                                                     /* handle IO complete */
      if ((state1 == WAITING) && (ioLeft1 == 0)) {
         state1 = READY;
         cpuLeft1 = z1;
      }  
      if ((state2 == WAITING) && (ioLeft2 == 0)) {
         state2 = READY;
         cpuLeft2 = z2;
      }  
                                    /* if both ready, depends on algorithm */
      if ( (state1 == READY) && (state2 == READY)) {
         state1 = RUNNING;
      }  
                                     /* handle one ready and CPU available */
      else if ( (state1 == READY) && (state2 != RUNNING)) {
         state1 = RUNNING;
      }  
      else if ( (state2 == READY) && (state1 != RUNNING)) {
         state2 = RUNNING;
      }  
   /* insert chars in string, but avoid putting in extra string terminators */
      if (state1 != DONE)
         s1[i] = stateChars[state1];
      if (state2 != DONE)
         s2[i] = stateChars[state2];
                                                        /* decrement counts */
      if (state1 == RUNNING)
         cpuLeft1--;
      if (state1 == WAITING)
         ioLeft1--;
      if (state2 == RUNNING)
         cpuLeft2--;
      if (state2 == WAITING)
         ioLeft2--;
   }                                               /* end of main for loop */
}


void sjf(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2){
	int i;                                   /* next string position (time) */
	int state1 = READY;                            /* start with both ready */
    int state2 = READY;
	int cpuLeft1 = x1;                       /* P1 next CPU burst remaining */
	int cpuLeft2 = x2;                       /* P2 next CPU burst remaining */
	int ioLeft1 = y1;        /* P1 next IO burst remaining, 0 if no more IO */
	int ioLeft2 = y2;        /* P2 next IO burst remaining, 0 if no more IO */

   for (i=0; (state1 != DONE) || (state2 != DONE); i++) {
                                /* running process completes its CPU burst */
      if ((state1 == RUNNING) && (cpuLeft1== 0)) {
         if (ioLeft1 == 0) {
            state1 = DONE;
            s1[i] = stateChars[state1];            /* terminate the string */
         }
         else
            state1 = WAITING;
      }
      else if ((state2 == RUNNING) && (cpuLeft2 == 0) ) {
         if (ioLeft2 == 0) {
            state2 = DONE;
            s2[i] = stateChars[state2];
         }
         else
            state2 = WAITING;
      }
                                                     /* handle IO complete */
      if ((state1 == WAITING) && (ioLeft1 == 0)) {
         state1 = READY;
         cpuLeft1 = z1;
      }
      if ((state2 == WAITING) && (ioLeft2 == 0)) {
         state2 = READY;
         cpuLeft2 = z2;
      }
                                    /* if both ready, depends on algorithm */
      if ( (state1 == READY) && (state2 == READY)) {
		 if(cpuLeft1 < cpuLeft2)
         	state1 = RUNNING;
		 else
			state2 = RUNNING;
      }
                                     /* handle one ready and CPU available */
      else if ( (state1 == READY) && (state2 != RUNNING)) {
         state1 = RUNNING;
      }
      else if ( (state2 == READY) && (state1 != RUNNING)) {
         state2 = RUNNING;
      }
   /* insert chars in string, but avoid putting in extra string terminators */
      if (state1 != DONE)
         s1[i] = stateChars[state1];
      if (state2 != DONE)
         s2[i] = stateChars[state2];
                                                        /* decrement counts */
      if (state1 == RUNNING)
         cpuLeft1--;
      if (state1 == WAITING)
         ioLeft1--;
      if (state2 == RUNNING)
         cpuLeft2--;
      if (state2 == WAITING)
         ioLeft2--;
   }                                               /* end of main for loop */
}


void psjf(char *s1, char *s2, int x1, int y1, int z1, int x2, int y2, int z2){
    int i;                                   /* next string position (time) */
    int state1 = READY;                            /* start with both ready */
    int state2 = READY;
    int cpuLeft1 = x1;                       /* P1 next CPU burst remaining */
    int cpuLeft2 = x2;                       /* P2 next CPU burst remaining */
    int ioLeft1 = y1;        /* P1 next IO burst remaining, 0 if no more IO */
 	int ioLeft2 = y2;        /* P2 next IO burst remaining, 0 if no more IO */

   for (i=0; (state1 != DONE) || (state2 != DONE); i++) {
                                /* running process completes its CPU burst */
      if ((state1 == RUNNING) && (cpuLeft1== 0)) {
         if (ioLeft1 == 0) {
            state1 = DONE;
            s1[i] = stateChars[state1];            /* terminate the string */
         }
         else
            state1 = WAITING;
      }
      else if ((state2 == RUNNING) && (cpuLeft2 == 0) ) {
         if (ioLeft2 == 0) {
            state2 = DONE;
            s2[i] = stateChars[state2];
         }
         else
            state2 = WAITING;
      }
                                                     /* handle IO complete */
      if ((state1 == WAITING) && (ioLeft1 == 0)) {
         state1 = READY;
         cpuLeft1 = z1;
      }
      if ((state2 == WAITING) && (ioLeft2 == 0)) {
         state2 = READY;
         cpuLeft2 = z2;
      }
                                    /* if both ready, depends on algorithm */
      if ( (state1 == READY) && (state2 == READY)) {
         if(cpuLeft1 < cpuLeft2)
            state1 = RUNNING;
         else
            state2 = RUNNING;
      }
                                     /* handle one ready and CPU available */
      else if ( (state1 == READY) && (state2 != RUNNING)) {
         state1 = RUNNING;
      }
      else if ( (state2 == READY) && (state1 != RUNNING)) {
         state2 = RUNNING;
      }
 	  else if ( (state1 == READY) && (cpuLeft1 < cpuLeft2)) {
         state2 = READY;
         state1 = RUNNING;
      }
      else if ( (state2 == READY) && (cpuLeft2 < cpuLeft1)) {
         state1 = READY;
         state2 = RUNNING;
      }
   /* insert chars in string, but avoid putting in extra string terminators */
      if (state1 != DONE)
         s1[i] = stateChars[state1];
      if (state2 != DONE)
         s2[i] = stateChars[state2];
                                                        /* decrement counts */
      if (state1 == RUNNING)
         cpuLeft1--;
      if (state1 == WAITING)
         ioLeft1--;
      if (state2 == RUNNING)
         cpuLeft2--;
      if (state2 == WAITING)
         ioLeft2--;
   }                                               /* end of main for loop */
}

void rr(char *s1, char *s2, int q, int x1, int y1, int z1, int x2, int y2, int z2) {
   int i;                                   /* next string position (time) */
   int state1 = READY;                            /* start with both ready */
   int state2 = READY;
   int cpuLeft1 = x1;                       /* P1 next CPU burst remaining */
   int cpuLeft2 = x2;                       /* P2 next CPU burst remaining */
   int ioLeft1 = y1;        /* P1 next IO burst remaining, 0 if no more IO */
   int ioLeft2 = y2;        /* P2 next IO burst remaining, 0 if no more IO */
   int qleft;                                         /* quantum remaining */

   for (i=0; (state1 != DONE) || (state2 != DONE); i++) {
                                /* running process completes its CPU burst */
      if ((state1 == RUNNING) && (cpuLeft1== 0)) {
         if (ioLeft1 == 0) {
            state1 = DONE;
            s1[i] = stateChars[state1];            /* terminate the string */
         }
         else
            state1 = WAITING;
      }  
      else if ((state2 == RUNNING) && (cpuLeft2 == 0) ) {
         if (ioLeft2 == 0) {
            state2 = DONE;
            s2[i] = stateChars[state2];
         }
         else
            state2 = WAITING;
      }  
                                     /* running process has quantum expire */
      if ((state1 == RUNNING) && (qleft == 0) ) {
         state1 = READY;
         qleft = q;
         if (state2 == READY)
            state2 = RUNNING;
      }  
      if ((state2 == RUNNING) && (qleft == 0) ) {
         state2 = READY;
         qleft = q;
         if (state1 == READY)
            state1 = RUNNING;
      }  
                                                     /* handle IO complete */
      if ((state1 == WAITING) && (ioLeft1 == 0)) {
         state1 = READY;
         cpuLeft1 = z1;
      }  
      if ((state2 == WAITING) && (ioLeft2 == 0)) {
         state2 = READY;
         cpuLeft2 = z2;
      }  
                                    /* if both ready, depends on algorithm */
      if ( (state1 == READY) && (state2 == READY)) {
         state1 = RUNNING;
         qleft = q;
      }  
                                     /* handle one ready and CPU available */
      else if ( (state1 == READY) && (state2 != RUNNING)) {
         state1 = RUNNING;
         qleft = q;
      }  
      else if ( (state2 == READY) && (state1 != RUNNING)) {
         state2 = RUNNING;
         qleft = q;
      }  
   /* insert chars in string, but avoid putting in extra string terminators */
      if (state1 != DONE)
         s1[i] = stateChars[state1];
      if (state2 != DONE)
         s2[i] = stateChars[state2];
                                                        /* decrement counts */
      qleft--;                   /* OK to decrement even if nothing running */
      if (state1 == RUNNING)
         cpuLeft1--;
      if (state1 == WAITING)
         ioLeft1--;
      if (state2 == RUNNING)
         cpuLeft2--;
      if (state2 == WAITING)
         ioLeft2--;
   }                                               /* end of main for loop */
}
