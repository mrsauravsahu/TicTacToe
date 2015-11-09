#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#define ROWSIZE 3
#define COLUMNSIZE 3

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
void Input(cell grid[][COLUMNSIZE], char symbol)
{
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

int main()
{
	cell grid[3][3];

}