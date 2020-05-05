/*
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

Now consider if some obstacles are added to the grids. How many unique paths would there be?

An obstacle and empty space is marked as 1 and 0 respectively in the grid.

Note: m and n will be at most 100.

Example 1:

Input:
[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
Output: 2
Explanation:
There is one obstacle in the middle of the 3x3 grid above.
There are two ways to reach the bottom-right corner:
1. Right -> Right -> Down -> Down
2. Down -> Down -> Right -> Right

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef DEBUG
#define DEBUG_PRINT printf
#define printArr
#else
#define DEBUG_PRINT
#define printArr _printArr
#endif

void _printArr(int* arr, int row, int col)
{
  for (int x = 1; x <= col; x++) {
    for (int y = 1; y <= row; y++) {
      printf("%d ", arr[y * (col + 1) + x]);
    }
    printf("\n");
  }
  printf("\n");
}

int uniquePathsWithObstacles(int** obstacleGrid,
    int obstacleGridSize, int* obstacleGridColSize)
{
	int rows = obstacleGridSize;
	int cols = obstacleGridColSize[0];

  unsigned int c[(rows + 1) * (cols + 1)];
  memset(c, 0, sizeof(*c) * (cols + 1) * (rows + 1));

  c[1 * (cols + 1)] = 1;
  for (int y = 1; y <= rows; y++) {
    for (int x = 1; x <= cols; x++) {
      int i = y * (cols + 1) + x;
      if (obstacleGrid[y - 1][x - 1] == 1) {
        c[i] = 0;
      } else {
        c[i] = c[(x - 1) + y * (cols + 1)] + c[x + (y - 1) * (cols + 1)];
      }
    }
  }
  printArr(c, rows, cols);
  return c[rows * (cols + 1) + cols];
}

void test1() {
  int grid[3][3] = {
    {0,0,0},
    {0,1,0},
    {0,0,0}
  };

  int** gridPtr = malloc(sizeof(*gridPtr) * 3);
  for (int i = 0; i < 3; i++) {
    gridPtr[i] = grid[i];
  }

  int colSize[3] = { 3, 3, 3 };
  int paths = uniquePathsWithObstacles(gridPtr, 3, colSize);
  free(gridPtr);
  printf("Num unique paths=%d\n", paths);
}

void test2() {
  int grid[1][2] = {
    {0,0}
  };

  int** gridPtr = malloc(sizeof(*gridPtr) * 1);
  for (int i = 0; i < 1; i++) {
    gridPtr[i] = grid[i];
  }

  int colSize[1] = { 2 };
  int paths = uniquePathsWithObstacles(gridPtr, 1, colSize);
  free(gridPtr);
  printf("Num unique paths=%d\n", paths);
}



int main(int argc, char** argv) {
  test2();
  return 0;
}
