/*
An image is represented by a 2-D array of integers, each integer representing the pixel value of the image (from 0 to 65535).

Given a coordinate (sr, sc) representing the starting pixel (row and column) of the flood fill, and a pixel value newColor, "flood fill" the image.

To perform a "flood fill", consider the starting pixel, plus any pixels connected 4-directionally to the starting pixel of the same color as the starting pixel, plus any pixels connected 4-directionally to those pixels (also with the same color as the starting pixel), and so on. Replace the color of all of the aforementioned pixels with the newColor.

At the end, return the modified image.

Example 1:

Input:
image = [[1,1,1],[1,1,0],[1,0,1]]
sr = 1, sc = 1, newColor = 2
Output: [[2,2,2],[2,2,0],[2,0,1]]
Explanation:
From the center of the image (with position (sr, sc) = (1, 1)), all pixels connected
by a path of the same color as the starting pixel are colored with the new color.
Note the bottom corner is not colored 2, because it is not 4-directionally connected
to the starting pixel.

Note:
The length of image and image[0] will be in the range [1, 50].
The given starting pixel will satisfy 0 <= sr < image.length and 0 <= sc < image[0].length.
The value of each color in image[i][j] and newColor will be an integer in [0, 65535].
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifdef DEBUG
#define DEBUG_PRINT printf
#else
#define DEBUG_PRINT
#endif

typedef struct node {
	int row;
	int col;
	struct node* next;
} node;

typedef struct queue {
	node* head;
	node* tail;
} queue;


void printImage(int **image, int imageSize, int* imageColSize);

int enqueue(queue* q, int row, int col) {
	if (q->tail == NULL) {
		q->tail = calloc(1, sizeof(node));
		q->tail->row = row;
		q->tail->col = col;
		q->head = q->tail;
	} else {
		q->tail->next = calloc(1, sizeof(node));
		q->tail->next->row = row;
		q->tail->next->col = col;
		q->tail = q->tail->next;
	}
	return 0;
}

node* dequeue(queue* q) {
	if (q->head == NULL) {
		return NULL;
	} else {
		node *temp = q->head;
		// Queue only has 1 element
		if (q->tail == q->head) {
			q->tail = q->head->next;
		}
		q->head = q->head->next;
		return temp;
	}
}

bool isEmpty(queue* q) {
	return q->head == NULL;
}

/**
* Return an array of arrays of size *returnSize.
* The sizes of the arrays are returned as *returnColumnSizes array.
* Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
*/
int** floodFill(int** image, int imageSize, int* imageColSize,
	int sr, int sc, int newColor, int* returnSize, int** returnColumnSizes) {

	*returnSize = imageSize;
	*returnColumnSizes = malloc(imageSize * sizeof(int));
	int** filledImage = calloc(imageSize, sizeof(int*));
	// Initialize of the rows
	for (int row = 0; row < imageSize; row++) {
		filledImage[row] = calloc(imageColSize[row], sizeof(int));
		(*returnColumnSizes)[row] = imageColSize[row];

		// Copy the original image into return image
		memcpy(filledImage[row], image[row], imageColSize[row] * sizeof(int));
	}

	queue q = { .head = NULL, .tail = NULL };

	enqueue(&q, sr, sc);
	int originalColor = image[sr][sc];
	while (!isEmpty(&q)) {
		node* n = dequeue(&q);

		// Skip redundant task
		if (filledImage[n->row][n->col] == newColor) {
			continue;
		}

		// Update the color
		filledImage[n->row][n->col] = newColor;

		// Check the 4 directions: up, down, left, right
		int combo[4][2] = {
			{-1, 0}, {1, 0}, {0, -1}, {0, 1}
		};
		for (int c = 0; c < 4; c++) {
			int i = combo[c][0];
			int j = combo[c][1];
			int row = n->row + i;
			int col = n->col + j;
			if (row >= 0 && row < imageSize && col >= 0 && col < imageColSize[row]) {
				if (filledImage[row][col] == originalColor) {
					enqueue(&q, row, col);
				}
			}
		}
		DEBUG_PRINT("filled up %d %d\n", n->row, n->col);
		printImage(filledImage, *returnSize, *returnColumnSizes);
	}

	return filledImage;
}

void printImage(int **image, int imageSize, int* imageColSize) {
	for (int row = 0; row < imageSize; row++) {
		for (int col = 0; col < imageColSize[row]; col++) {
			DEBUG_PRINT("%d ", image[row][col]);
		}
		DEBUG_PRINT("\n");
	}
	DEBUG_PRINT("\n");
}

void printArray(int *arr, int len) {
	for (int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main(int argc, char** argv) {
	#define imageSize 3
	#define imageColSize 3
	int image[imageSize][imageColSize] = {
		{1, 1, 1},
		{1, 1, 0},
		{1, 0, 1}

	};

	int** imagePtr = malloc(imageSize * sizeof(int*));
	for (int i = 0; i < imageSize; i++) {
		imagePtr[i] = image[i];
	}

	int colSize[imageSize];
	for (int i = 0; i < imageSize; i++) {
		colSize[i] = imageColSize;
	}

	// printf("colSize=");
	// printArray(colSize, imageSize);

	int filledSize;
	int* filledColumnSizes;


	printf("original image:\n");
	printImage(imagePtr, imageSize, colSize);

	int** floodedImage = floodFill(imagePtr, imageSize, colSize,
		1, 1, 2, &filledSize, &filledColumnSizes);

	// printf("filledSize=%d\n", filledSize);
	// printf("filledColumnSizes=");
	// printArray(filledColumnSizes, filledSize);
	return 0;
}
