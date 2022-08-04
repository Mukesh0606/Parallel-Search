/*  This Sequential program finds all occurrences of certain integer and writes all the array indices where the integer was found to an output file.
 *  Mukesh 
 *  17/09/2021
 *  */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<omp.h>

#define MAX_DISP 10

void search(int* A, int N, int target)
{
	int i;
	double start,end;
	FILE *fp;
	char filename[20];

	sprintf(filename, "target%d",N);

	do
	{
		fp = fopen(filename,"w");
	}while(!fp);

	start = omp_get_wtime();
	printf("Start : %f\t",start);
	for(i = 1; i < N; i++)
	{
		if(A[i] == target)
			fprintf(fp,"%4d ",i);
	}
	end = omp_get_wtime();
	printf("Time taken : %f\n",end-start);
}

void main (int argc, char *argv[])
{
	char* filename1; 
	long int target;
	
	do
	{
		filename1 = malloc(sizeof(char)*20);
	}while(!filename1);
	int size = 0;
	FILE* fp;
	int* A;
	int i;
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
	do {
		A = malloc(sizeof(int)*size);
	}while(!A);

	rewind(fp);
	for(int j=0; (fscanf(fp, "%d", &A[j]) == 1) && j<size; j++);
	fclose(fp);

	if(size<MAX_DISP)
	for(i=0; i< size; i++)
	{
		printf("%d ",A[i]);

		if(i%10 == 0)
		printf("\n");
	}
	target = A[0];
	search(A, size, target);
		free(A);
}
