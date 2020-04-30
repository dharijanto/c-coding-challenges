/*
Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

Example:

Input: [-2,1,-3,4,-1,2,1,-5,4],
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.

Follow up:

If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.

*/

#ifdef DEBUG
#define DEBUG_PRINT printf
#else
#define DEBUG_PRINT
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int maxSubArray(int* nums, int numsSize){
  int max[numsSize];
  // This is not needed, but good for debugging (i.e. backtracking)
  int start[numsSize];
  int globalMax;

  for (int i = 0; i < numsSize; i++) {
    int num = nums[i];
    if (i == 0) {
      globalMax = num;
      max[i] = num;
      start[i] = 0;
    } else {
      if (max[i-1] + num > num) {
        max[i] = max[i-1] + num;
        start[i] = start[i-1];
      } else {
        max[i] = num;
        start[i] = i;
      }
      globalMax = max[i] > globalMax ? max[i] : globalMax;
    }
  }
  return globalMax;
}

int main(int argc, char** argv) {
  int nums[] = {-2,1,-3,4,-1,2,1,-5,4};
  int max = maxSubArray(nums, sizeof(nums) / sizeof(int));
  printf("max=%d\n", max);
  return 0;
}
