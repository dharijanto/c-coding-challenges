/*
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?


Above is a 7 x 3 grid. How many possible unique paths are there?



Example 1:

Input: m = 3, n = 2
Output: 3
Explanation:
From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
1. Right -> Right -> Down
2. Right -> Down -> Right
3. Down -> Right -> Right

Example 2:

Input: m = 7, n = 3
Output: 28



Constraints:

    1 <= m, n <= 100
    It's guaranteed that the answer will be less than or equal to 2 * 10 ^ 9
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int uniquePaths(int m, int n){
  int c[m + 1][n + 1];
  for (int i = 0; i <= m; i++) {
    memset(c[i], 0, sizeof(c[0][0]) * (n + 1));
  }

  c[0][1] = 1;
  for (int y = 1; y <= n; y++) {
    for (int x = 1; x <= m; x++) {
      c[x][y] = c[x-1][y] + c[x][y-1];
    }
  }
  return c[m][n];
}

int main(int argc, char** argv) {
  printf("uniquePath=%d\n", uniquePaths(3,2));
  return 0;
}
