/*  This Program generates a input file with random number of random integers.
 *  Mukesh 
 *  14/09/2021
 *  */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX_SIZE 100000000

int main(int argc, char *argv[])
{
    short lower = -9, upper = 9;
    long int size = (long int)atoi(argv[1]);
    FILE *fp;
    char filename[20];

    if(size > MAX_SIZE)
    {
	size = MAX_SIZE;
    	printf("Max size excedded.\nSetting size to %d\n",MAX_SIZE);
    }

    sprintf(filename,"inputs%ld",size);
    do
    {
    	fp = fopen(filename,"w"); 
    }while(!fp);
    srand(time(0));
    long int i;
    int start,end;
    start = time(0);
    printf("Start: %d\t",start);
    for (i = 0; i < size; i++)
    {
        	short num =(short)((rand() %(upper - lower + 1)) + lower);
        	fprintf(fp,"%hi ", num);
    }
    end = time(0);
    printf("End : %d\tExecution time : %d\n",end,end-start);
    
   fclose(fp); 
    return 0;
}
