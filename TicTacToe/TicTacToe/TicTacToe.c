#define _CRT_SECURE_NO_WARNINGS

//Preprocessor Directives
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ROWSIZE 3
#define COLUMNSIZE 3

//Data Structures
enum Bool
{
	false,
	true
};
enum character
{
	X,
	O
};
struct Cell
{
	enum bool isOccupied;
	int position;
	enum character character;
};
typedef enum Bool bool;
typedef struct Cell cell;

//Function Prototypes
void Initialize(cell *[], int, int);
bool IsValid(cell *[], int);
void ReadUserName(char[], int);
void Input(cell *[], int);
void WriteLine(int);
void Display(cell *[], char);
int Toss();
bool AreAllSame(cell [], int);

//The main Function
int main()
{
	//Variable Declaration
	cell grid[3][3];
	char user1[40], user2[40], temp[40];
	int firstUser, count;

	//Game Logic
	do
	{
		count = 0;
		ReadUserName(user1, 1);
		ReadUserName(user2, 2);
		firstUser = Toss();
		switch (firstUser)
		{
		case 0: printf("%s won the toss.", user1);
			break;
		case 1: printf("%s won the toss.", user2);
			strcpy(temp, user1);
			strcpy(user1, user2);
			strcpy(user2, temp);
		}
		printf("\nPLAYERS");
		printf("\nPlayer 1: %s", user1);
		printf("\nPlayer 2: %s", user2);

		while (count < (ROWSIZE*COLUMNSIZE))
		{
			Display(grid, 'P');
			Input(grid, count);
			Display(grid, 'M');
			++count;
		}
	} while (1);
}

//Function Definition
void Initialize(cell grid[][COLUMNSIZE], int rowSize, int columnSize)
{
	int i, j;
	for (i = 0; i < rowSize; i++)
	{
		for (j = 0; j < columnSize; j++)
		{
			(grid[i][j]).isOccupied = false;
			(grid[i][j]).position = i*rowSize + j + 1;
		}
	}
}
bool IsValid(cell grid[][COLUMNSIZE], int position)
{
	int row, column;
	row = (position - 1) / ROWSIZE;
	column = (position - 1) % ROWSIZE;
	if ((grid[row][column]).isOccupied == true)return false;
	return true;
}
void ReadUserName(char name[], int num)
{
	printf("\nEnter player name %d: ", num);
	gets(name);
}
void Input(cell grid[][COLUMNSIZE], int number)
{
	char symbol;
	if (number % 2 == 0)symbol = 'X';
	else symbol = 'O';
	int position;
	printf("\nEnter position to draw %c: ", symbol);
	do
	{
		scanf("%d", &position);
		if (IsValid(grid, position) == false)
		{
			printf("\nYou entered an invalid position. Try again: ");
		}
	} while (IsValid(grid, position) == false);
}
void WriteLine(int rowSize)
{
	int i;
	printf("\n");
	for (i = 0; i < 2 * rowSize; i++)
	{
		if (i % 2 == 0) printf("_");
		else printf(" ");
	}
}
void Display(cell grid[][COLUMNSIZE], char mode)
{
	int i, j;
	switch (mode)
	{
	case 'M':
	{
		WriteLine(ROWSIZE);
		for (i = 0; i < ROWSIZE; i++)
		{
			printf("\n");
			for (j = 0; j < COLUMNSIZE; j++)
			{
				if (grid[i][j].isOccupied == false)
				{
					printf("%d ", grid[i][j].position);
				}
				else
				{
					printf("%c ", grid[j][i].character);
				}
			}
		}
		WriteLine(ROWSIZE);
	}

	case 'P':
	{
		WriteLine(ROWSIZE);
		for (i = 0; i < ROWSIZE; i++)
		{
			printf("\n");
			for (j = 0; j < COLUMNSIZE; j++)
			{
				if (grid[i][j].isOccupied == false)
				{
					printf("%d ", grid[i][j].position);
				}
				else
				{
					printf("  ");
				}
			}
		}
		WriteLine(ROWSIZE);
	}
	}
}
int Toss()
{
	srand(time());
	return (rand() % 2);
}
bool Check(cell grid[][COLUMNSIZE])
{
	int i, j;
	for (i = 0; i < ROWSIZE; ++i)
	{
		for (j = 0; j < COLUMNSIZE; ++j)
		{
			//TODO
		}
	}
}
bool AreAllSame(cell array[], int size)
{
	int i;
	for (i = 0; i < size - 1; ++i)
	{
		if (array[i].isOccupied == false
			|| array[i+1].isOccupied == true
			|| array[i+1].character!= array[i + 1].character)
			return false;
	}
	return true;
}