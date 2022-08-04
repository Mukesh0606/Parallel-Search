/*  This parallel program finds all occurrences of certain set of integers and writes all the array indices where each target was found to an output file.
 *  Mukesh
 *  25/09/2021
 *  */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<omp.h>

#define MAX_DISP 10

void main (int argc, char *argv[])
{
	char* filename1;
        int targetSetLength = atoi(argv[2]);
	int number_of_threads = atoi(argv[3]);
	do
	{
		filename1 = malloc(sizeof(char)*20);
	}while(!filename1);
	int size =0 ;
	FILE* fp;
	int* A;
	int i;
        if(targetSetLength <= 0)
        {
             printf("\nIncorrect targetSetLength : expected > 1, received <=0\n");
             return;
        }
	fp = fopen(argv[1],"r");
	if(fp == NULL)
	{
		printf("\nThe required file doesnot exist / didn't open.\n");
		return;
	}
	int digit;
	while(fscanf(fp, "%d", &digit) == 1)
		size++;
	printf("Size : %d\n",size);
        if (size <= targetSetLength)
        {
            printf("\nNumber of Elements in the set less than / equal to number of targets.\n");
            return;
        }
	do 
        {
		A = malloc(sizeof(int)*size);
	} while (!A);
	rewind(fp);
	int k;
	for(k=0; (fscanf(fp, "%d", &A[k]) == 1) && k<size; k++);
	fclose(fp);
	
	if(size<MAX_DISP)
	for(i=0; i< size; i++)
	{
		printf("%d ",A[i]);

		if(i%10 == 0)
		printf("\n");
	}

	int j;
	double start,end;
	FILE *fq;
	char filename[20];
	sprintf(filename, "targetset%d",size);
	do
	{
		fq = fopen(filename,"w");
	}while(!fq);
	start = omp_get_wtime();
	printf("Start : %f\t",start);
    #pragma omp parallel for schedule(dynamic) default(none) shared(fq,A,targetSetLength,size) num_threads(number_of_threads)
	for(j = 0; j < targetSetLength; j++)
		#pragma omp parallel for default(none) firstprivate(j) shared(fq,A,targetSetLength,size)
		for(i = targetSetLength; i < size; i++)
		{
			if(A[i] == A[j])
			{ 
				fprintf(fq,"%4d ",i);
		
			}
		}
	end = omp_get_wtime();
	printf("Time taken : %f\n",end-start);
        free(A);
}
