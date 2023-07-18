#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxsize 100

struct block
{
	int value;
	struct block *next;
};

struct fileEntry
{
	char *name;
	int start;
	int length;
};

struct block disk[maxsize];
int freeSpace = maxsize;
struct fileEntry files[30];

void init()
{
	int i;
	for (i = 0; i < 30; i++)
	{
		files[i].name = NULL;          //No files present
	}
	for (i = 0; i < maxsize; i++)
	{
		disk[i].value = 0;            //Disk is Empty & blocks do not point to any other block
		disk[i].next = NULL;
	}
}

int getEmptySlot()                    //checking empty slots
{
	int i;
	for (i = 0; i < 30; i++)
	{
		if (files[i].name == NULL)
			return i;
	}
	return -1;
}

void insertFile(char *name, int blocks)           //inserting files
{
	if (blocks > freeSpace)
	{
		printf("\nFile size too big\n");
		return;
	}
	int start = -1;
	int i, j, allocated = 0;
	int prev = -1;
	for (i = 0; i<maxsize; i++)
	{
		if (disk[i].value == 0)
		{
			if (start == -1)
			{
				start = i;
			}
			disk[i].value = 1;
			if(prev != -1)
				disk[prev].next = &disk[i];
			allocated++;
			prev = i;
		}
		if (allocated == blocks)
		{
			disk[i].next = NULL;
			break;
		}
	}
	int slot = getEmptySlot();
	files[slot].name = malloc(0);
	strcpy(files[slot].name, name);
	files[slot].length = blocks;
	files[slot].start = start;
	freeSpace -= blocks;
	printf("Inserted\n");
}

void displaySize()                                    //free space
{
	printf("Free space in disk = %d", freeSpace);
}

void displayFiles()                                  //displaying files
{
	int i;
	printf("Files in disk:\n");
	printf("Name\tStart\tLength\n\n");
	for (i = 0; i < 30; i++)
	{
		if (files[i].name != NULL)
		{
			printf("%s\t%4d\t%3d\n", files[i].name, files[i].start, files[i].length);
			printf("Blocks: %d -> ", files[i].start);
			struct block *temp = disk[files[i].start].next;
			while (temp!= NULL)
			{
				printf("%d -> ", (temp-disk));
				temp = temp->next;
			}
			printf("NULL\n");
		}
	}
	printf("\n");
}


int main()
{
	int option;
	char* name = (char*)malloc(20 * sizeof(char));
	int blocks, start;
	init();
	printf("Linked File allocation technique");
	printf("\n1. Insert a File");
	printf("\t2. Display all files");
	printf("\t3. Exit\n");
	while (1)
	{
		displaySize();                              
		printf("\nEnter option: ");
		scanf_s("%d", &option);
		switch (option)
		{
		case 1:
			printf("Enter file name: ");
			getchar();
			gets(name);
			printf("Enter number of blocks: ");
			scanf_s("%d", &blocks);
			insertFile(name, blocks);
			break;
		case 2:
			displayFiles();
			break;
		case 3:
			exit(1);
		default:
			printf("Wrong Choice\n");
		}
	}
	return 0;
}


