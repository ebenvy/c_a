/*
 * diskCleaner.c
 *
 *  Created on: 2018. 8. 11.
 *      Author: ebenv
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAX_CAL 9
#define MAX_ROW 5
#define MAX_LEN 3
const char* disk[MAX_ROW][MAX_CAL]=
						{{"A","H","L","BB","","Z","K","","L"},
						 {"B","","A","","N","NN","K","F",""},
						 {"","CC","","D","","G","","","J"},
						 {"KK","","","","","D","DD","",""},
						 {"","B","","J","P","","G","","P"}};
/*
const char disk[MAX_ROW][MAX_CAL][MAX_LEN]=
						{{"A","H","L","BB","","Z","K","","L"},
						 {"B","","A","","N","NN","K","F",""},
						 {"","CC","","D","","G","","","J"},
						 {"KK","","","","","D","DD","",""},
						 {"","B","","J","P","","G","","P"}};*/
bool findSameFile(int row,int cal ,int* result_row, int* result_cal);
void MergeFiles(char*** newDisk);
void ArrangeFiles(char*** newDisk);
void printDisk(char*** newDisk);
int main()
{
	/**intialize new Disk**/
	char*** newDisk = (char***)malloc(sizeof(char**)*MAX_ROW);
	for(int i = 0; i< MAX_ROW; i++)
	{
		newDisk[i] = (char**)malloc(sizeof(char*)*MAX_CAL);
		for( int j= 0 ; j< MAX_CAL; j++)
		{
			newDisk[i][j] = (char*)malloc(sizeof(char)*MAX_LEN);
			for( int k = 0 ; k<MAX_LEN ; k++ )
			{
				newDisk[i][j][k] = 0x00;
			}
		}
	}

	/**merge Disk**/
	MergeFiles(newDisk);
	PrintDisk(newDisk);
	/*arrange Disk*/
	ArrangeFiles(newDisk);
	PrintDisk(newDisk);

	for(int i = 0; i< MAX_ROW; i++)
	{

		for( int j= 0 ; j< MAX_CAL; j++)
		{

			free(newDisk[i][j]);
		}
		free(newDisk[i]);
	}
	free(newDisk);
	return 0;
}
void MergeFiles(char*** newDisk)
{
	for(int i= 0;i< MAX_ROW;i++)
	{
		for(int j = 0 ; j< MAX_CAL; j++)
		{
			if( strlen(disk[i][j]) == 1 )
			{
				int idx_row;
				int idx_cal;
				if( findSameFile(i,j,&idx_row,&idx_cal) == true)
				{
					memset(newDisk[i][j],disk[i][j][0],2);
					newDisk[idx_row][idx_cal][0]=0x20;
					continue;
				}

			}
			if(newDisk[i][j][0] == 0x00)
			{
				strncpy(newDisk[i][j], disk[i][j],MAX_LEN);
				//empty->space
				if(newDisk[i][j][0]==0x00)
					newDisk[i][j][0]=0x20;

			}
		}
	}

}
void ArrangeFiles(char*** newDisk)
{

	char*** arrangeDisk = (char***)malloc(sizeof(char**)*MAX_ROW);
	for(int i = 0; i< MAX_ROW; i++)
	{
		arrangeDisk[i] = (char**)malloc(sizeof(char*)*MAX_CAL);
		for( int j= 0 ; j< MAX_CAL; j++)
		{
			arrangeDisk[i][j] = (char*)malloc(sizeof(char)*MAX_LEN);
			for( int k = 0 ; k<MAX_LEN ; k++ )
			{
				arrangeDisk[i][j][k] = 0x00;
			}
		}
	}
	int count = 0;
	for(int i= 0;i< MAX_ROW;i++)
	{
		for(int j = 0 ; j< MAX_CAL; j++)
		{
			if(strlen(newDisk[i][j]) == 2 )
			{
				memcpy( arrangeDisk[(int)(count/MAX_CAL)][count%MAX_CAL], newDisk[i][j], MAX_LEN );
				count++;
			}

		}
	}
	for(int i= 0;i< MAX_ROW;i++)
	{
		for(int j = 0 ; j< MAX_CAL; j++)
		{
			if(strlen(newDisk[i][j]) == 1 && newDisk[i][j][0]!= 0x20)
			{
				memcpy( arrangeDisk[(int)(count/MAX_CAL)][count%MAX_CAL] , newDisk[i][j], MAX_LEN );
				count++;
			}

		}
	}
	for(int i= 0;i< MAX_ROW;i++)
	{
		for(int j = 0 ; j< MAX_CAL; j++)
		{
			memcpy(newDisk[i][j], arrangeDisk[i][j],MAX_LEN);
		}
	}
	for(int i = 0; i< MAX_ROW; i++)
	{

		for( int j= 0 ; j< MAX_CAL; j++)
		{

			free(arrangeDisk[i][j]);
		}
		free(arrangeDisk[i]);
	}
	free(arrangeDisk);
}
void PrintDisk(char*** disk_arr)
{
	printf("-------------------------------------\n");
	for(int i= 0;i< MAX_ROW;i++)
	{
		for(int j = 0 ; j< MAX_CAL; j++)
		{
			printf("[%s] ",disk_arr[i][j]);
		}
		printf("\n");
	}
	printf("-------------------------------------\n");
}
bool findSameFile(int row,int cal ,int* result_row, int* result_cal)
{
	int i= row;
	int j = cal+1;
	for(;i< MAX_ROW;i++)
	{
		for(; j< MAX_CAL; j++)
		{
			if(strlen(disk[row][cal])==strlen(disk[i][j]) && memcmp(disk[row][cal],disk[i][j],strlen(disk[i][j]))==0)
			{
				*result_row = i;
				*result_cal = j;
				return true;
			}
			else if( disk[i][j][0]==disk[row][cal][0])
			{
				return false;
			}
		}
		j= 0;
	}
	return false;
}


