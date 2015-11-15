#define _CRT_SECURE_NO_WARNINGS

//Preprocessor Directives
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ROWSIZE 3
#define COLUMNSIZE 3

//Data Structures
enum Bool
{
	false,
	true
};
enum Character
{
	X=88,
	O=79
};
struct Cell
{
	enum bool isOccupied;
	int position;
	enum character character;
};
typedef enum Bool bool;
typedef enum Character character;
typedef struct Cell cell;

//Function Prototypes
void Initialize(cell [][COLUMNSIZE], int, int);
bool IsValid(cell[][COLUMNSIZE], int);
void ReadUserName(char[], int);
void Input(cell[][COLUMNSIZE], int);
void WriteLine(int);
void Display(cell[][COLUMNSIZE], char);
int Toss();
int IsGameOver(cell[][COLUMNSIZE]);

//The main Function
int main()
{
	//Variable Declaration
	cell grid[3][3];
	char user1[40], user2[40], temp[40], playAgain;
	int firstUser, count, isItOver;
	//Game Logic
	while (1)
	{
		Initialize(grid, ROWSIZE, COLUMNSIZE);
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
		printf("\nPlayer 1: %s: Assigned piece: X", user1);
		printf("\nPlayer 2: %s: Assigned piece: O", user2);

		while (count < (ROWSIZE*COLUMNSIZE))
		{
			Display(grid, 'P');
			Input(grid, count);
			Display(grid, 'M');
			if (count >= 4)
			{
				isItOver = IsGameOver(grid);
				if (isItOver != -1)
				{
					if (isItOver == 79)
						strcpy(user1, user2);
					printf("\n%s won! Congratulations!!", user1);
					break;
				}
			}
			++count;
		}
		if (count == 8)
		{
			printf("\nIt's a draw. Well played, both of you!");
		}
		printf("\nDo you want to start a new game? (y/n): ");
		scanf("%c", &playAgain);
		if (playAgain == 'Y' || playAgain == 'y')
		{
			system("cls");
			continue;
		}
		else
		{
			break;
		}
	}
}

//Function Definition
void Initialize(cell grid[ROWSIZE][COLUMNSIZE], int rowSize, int columnSize)
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
bool IsValid(cell grid[ROWSIZE][COLUMNSIZE], int position)
{
	int row, column;
	if(position > ROWSIZE*COLUMNSIZE)return false;
	row = (position - 1) / ROWSIZE;
	column = (position - 1) % ROWSIZE;
	if ((grid[row][column]).isOccupied == true)return false;
	return true;
}
void ReadUserName(char name[], int num)
{
	printf("\nEnter player name %d: ", num);
	scanf("%s", name);
}
void Input(cell grid[ROWSIZE][COLUMNSIZE], int number)
{
	char symbol; character enumSymbol;
	if (number % 2 == 0)
	{
		symbol = 'X';
		enumSymbol = X;
	}
	else
	{
		symbol = 'O';
		enumSymbol = O;
	}
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
	grid[(position - 1) / ROWSIZE][(position - 1) % ROWSIZE].isOccupied = true;
	grid[(position - 1) / ROWSIZE][(position - 1) % ROWSIZE].character = enumSymbol;
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
void Display(cell grid[ROWSIZE][COLUMNSIZE], char mode)
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
					printf("%c ", (int)grid[i][j].character);
				}
			}
		}
		WriteLine(ROWSIZE);
	}
	break;

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
	srand((int)time(NULL));
	return (rand() % 2);
}
void InitializeTheArray(int a[], int size, int num)
{
	int i;
	for (i = 0; i < size; i++)
	{
		a[i] = num;
	}
}
int IsGameOver(cell grid[ROWSIZE][COLUMNSIZE])
{
	int i, j;
	bool flag = false;
	int rows[ROWSIZE];
	int columns[COLUMNSIZE];
	int diag[2];

	InitializeTheArray(rows, ROWSIZE, 0);
	InitializeTheArray(columns, COLUMNSIZE, 0);
	InitializeTheArray(diag, 2, 0);
	for (i = 0; i < ROWSIZE; ++i)
	{
		rows[i] = columns[i] = 0;
		for (j = 0; j < COLUMNSIZE; ++j)
		{
			if (grid[i][j].isOccupied == true && grid[i][j].character == X)
			{
				rows[i]++;
				columns[j]++;
			}
			if (grid[i][j].isOccupied == true && grid[i][j].character == O)
			{
				rows[i]--;
				columns[j]--;
			}
		}
	}
	for (i = 0; i < ROWSIZE; i++)
	{
		if (grid[i][i].isOccupied == true && grid[i][i].character == X)
		{
			diag[0]++;
		}
		if (grid[i][i].isOccupied == true && grid[i][i].character == O)
		{
			diag[0]--;
		}
	}
	for (i = 0; i < ROWSIZE; i++)
	{
		if (grid[i][ROWSIZE - i - 1].isOccupied == true && grid[i][ROWSIZE - i - 1].character == X)
		{
			diag[1]++;
		}
		if (grid[i][ROWSIZE - i - 1].isOccupied == true && grid[i][ROWSIZE - i - 1].character == O)
		{
			diag[1]--;
		}
	}
	
	for (i = 0; i < ROWSIZE; i++)
	{
		if (rows[i] == 3 || columns[i] == 3)return 88;
		if (rows[i] == -3 || columns[i] == -3)return 79;
	}
	for (i = 0; i < 2; i++)
	{
		if (diag[i] == 3)return 88;
		if (diag[i] == -3)return 79;
	}
	return -1;
}