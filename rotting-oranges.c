/*
In a given grid, each cell can have one of three values:

    the value 0 representing an empty cell;
    the value 1 representing a fresh orange;
    the value 2 representing a rotten orange.

Every minute, any fresh orange that is adjacent (4-directionally) to a rotten orange becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh orange.  If this is impossible, return -1 instead.



Example 1:

Input: [[2,1,1],[1,1,0],[0,1,1]]
Output: 4

Example 2:

Input: [[2,1,1],[0,1,1],[1,0,1]]
Output: -1
Explanation:  The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.

Example 3:

Input: [[0,2]]
Output: 0
Explanation:  Since there are already no fresh oranges at minute 0, the answer is just 0.



Note:

    1 <= grid.length <= 10
    1 <= grid[0].length <= 10
    grid[i][j] is only 0, 1, or 2.

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef DEBUG
#define debugPrintQueue printQueue
#define DEBUG_PRINT printf
#else
#define debugPrintQueue
#define DEBUG_PRINT
#endif

struct coord {
  int row, col;
};

// Quirks: Usable size is actually size - 1,
// due to implementation reason
struct queue {
  struct coord *coords;
  int head, tail;
  int size;
};

bool isEmpty(struct queue *q)
{
  return q->head == q->tail;
}

int enqueue(struct queue *q, int row, int col)
{
  int newTail = (q->tail + 1) % (q->size + 1);
  // Avoid clash
  if (newTail == q->head) {
    return -1;
  } else {
    struct coord *c = &(q->coords[q->tail]);
    q->tail = newTail;
    c->row = row;
    c->col = col;
    return 0;
  }
}

struct coord* dequeue(struct queue *q)
{
  if (q->head != q->tail) {
    struct coord *c = &q->coords[q->head];
    q->head = (q->head + 1) % (q->size + 1);
    return c;
  } else {
    return NULL;
  }
}

void printQueue(struct queue *q) {
  for (int i = q->head; i != q->tail; i = (i + 1) % (q->size + 1)) {
    struct coord *c = &q->coords[i];
    printf("| row=%d col=%d | ", c->row, c->col);
  }
  printf("head=%d tail=%d\n", q->head, q->tail);
}

void initQueue(struct queue *q, int size) {
  q->head = 0;
  q->tail = 0;
  q->size = size;
  q->coords = malloc(sizeof(*(q->coords)) * size + 1);
}

void freeQueue(struct queue *q) {
  free(q->coords);
}

int orangesRotting(int** grid, int gridSize, int* gridColSize) {
  int min = 0;
  struct queue q1;
  struct queue q2;

  initQueue(&q1, gridSize * gridColSize[0]);
  initQueue(&q2, gridSize * gridColSize[0]);

  struct queue *q = &q1;
  struct queue *otherQ = &q2;
  int dir[4][2] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} };
  // Initialize the queue
  for (int row = 0; row < gridSize; row++) {
    for (int col = 0; col < gridColSize[row]; col++) {
      int o = grid[row][col];
      // DEBUG_PRINT("%d", o);
      if (o == 2) {
        for (int i = 0; i < 4; i++) {
          int r = row + dir[i][0];
          int c = col + dir[i][1];
          // If direction is valid
          if (r >= 0 && r < gridSize && c >= 0 && c < gridColSize[row]) {
            // This orange is gonna rot on the next cycle
            if (grid[r][c] == 1) {
              enqueue(q, r, c);
            }
          }
        }
      }
    }
  }

  // Simulate minute-by-minte passing by
  while (!isEmpty(q)) {
    DEBUG_PRINT("min=%d\n", min);
    debugPrintQueue(q);
    bool u = false;
    while(!isEmpty(q)) {
      struct coord *c = dequeue(q);
      // If this orange isn't already made rotten by other orange
      if (grid[c->row][c->col] != 2) {
        // Make it rotten
        grid[c->row][c->col] = 2;
        u = true;
        for (int i = 0; i < 4; i++) {
          int row = c->row + dir[i][0];
          int col = c->col + dir[i][1];
          // If direction is valid
          if (row >= 0 && row < gridSize && col >= 0 && col < gridColSize[c->row]) {
            // This orange is gonna rot on the next cycle
            if (grid[row][col] == 1) {
              enqueue(otherQ, row, col);
            }
          }
        }
      }
    }

    struct queue *temp = q;
    q = otherQ;
    otherQ = temp;
    if (u)
      min++;
  }

  freeQueue(&q1);
  freeQueue(&q2);

  // Check whether there's fresh oranges
  for (int r = 0; r < gridSize; r++) {
    for (int c = 0; c < gridColSize[r]; c++) {
      // There's still unrotten orange!
      if (grid[r][c] == 1) {
        return -1;
      }
    }
  }

  return min;
}

void test1() {
  int oranges[3][3] = {
    {2,1,1},
    {1,1,0},
    {0,1,1}
  };
  int size = 3;
  int colSize[3] = {3,3,3};

  int **orangesPtr = malloc(sizeof(*orangesPtr) * size);
  for (int i = 0; i < size; i++) {
    orangesPtr[i] = oranges[i];
  }
  int min = orangesRotting(orangesPtr, size, colSize);

  free(orangesPtr);
  printf("Time taken for all oranges to rot=%d\n", min);
}

void test2() {
  int oranges[3][3] = {
    {2,1,1},
    {0,1,1},
    {1,0,1}
  };
  int size = 3;
  int colSize[3] = {3,3,3};

  int **orangesPtr = malloc(sizeof(*orangesPtr) * size);
  for (int i = 0; i < size; i++) {
    orangesPtr[i] = oranges[i];
  }
  int min = orangesRotting(orangesPtr, size, colSize);

  free(orangesPtr);
  printf("Time taken for all oranges to rot=%d\n", min);
}

void test3() {
  int oranges[4][2] = {
    {2,2},
    {1,1},
    {0,0},
    {2,0}
  };
  int size = 4;
  int colSize[4] = {2,2,2};

  int **orangesPtr = malloc(sizeof(*orangesPtr) * size);
  for (int i = 0; i < size; i++) {
    orangesPtr[i] = oranges[i];
  }
  int min = orangesRotting(orangesPtr, size, colSize);

  free(orangesPtr);
  printf("Time taken for all oranges to rot=%d\n", min);
}

void testQueue() {
  struct queue q;
  struct coord *c;
  const int size = 3;
  initQueue(&q, size);
  printQueue(&q);
  enqueue(&q, 1, 2);
  printQueue(&q);
  enqueue(&q, 2, 3);
  printQueue(&q);
  enqueue(&q, 3, 3);
  printQueue(&q);
  enqueue(&q, 4, 3);
  printQueue(&q);
  c = dequeue(&q);
  printf("dequeue: c.row=%d c.col=%d\n", c->row, c->col);
  printQueue(&q);
  c = dequeue(&q);
  printf("dequeue: c.row=%d c.col=%d\n", c->row, c->col);
  printQueue(&q);
  c = dequeue(&q);
  printf("dequeue: c.row=%d c.col=%d\n", c->row, c->col);
  printQueue(&q);
  c = dequeue(&q);
  printf("dequeue: %p\n", c);
  enqueue(&q, 999, 999);
  enqueue(&q, 123, 321);
  printQueue(&q);
}

int main(int argc, char** argv) {
  // testQueue();
  // orangesRotting();
  test3();
  return 0;
}

