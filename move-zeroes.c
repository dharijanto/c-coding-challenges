/*
Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.

Example:

Input: [0,1,0,3,12]
Output: [1,3,12,0,0]

Note:

    You must do this in-place without making a copy of the array.
    Minimize the total number of operations.
*/

#include <stdio.h>
#include <stdlib.h>

void moveZeroes(int* nums, int numsSize) {
  for (int i = 0; i < numsSize; i++) {
    if (nums[i] == 0) {
      // Find the next non-0 value
      for (int j = i + 1; j < numsSize; j++) {
        // Swap them out
        if (nums[j] != 0) {
          int temp = nums[j];
          nums[j] = nums[i];
          nums[i] = temp;
          break;
        }
      }
    }
  }
}

void printArr(int *nums, int numsSize) {
  printf("[");
  for (int i = 0; i < numsSize; i++) {
    printf("%d", nums[i]);
    if (i < numsSize - 1) {
        printf(", ");
    }
  }
  printf("]\n");
}

int main(int argc, char** argv) {
  int nums[] = {0,1,0,3,12};
  int len = sizeof(nums) / sizeof(int);
  moveZeroes(nums, len);
  printArr(nums, len);
  return 0;
}
