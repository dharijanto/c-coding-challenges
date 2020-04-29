#include "stdio.h"
#define MAX(a,b) (a > b) ? (a) : (b)
/*

Problem
This problem was asked by Airbnb.

Given a list of integers, write a function that returns the largest sum of non-adjacent numbers. Numbers can be 0 or negative.

For example, [2, 4, 6, 2, 5] should return 13, since we pick 2, 6, and 5. [5, 1, 1, 5] should return 10, since we pick 5 and 5.

Follow-up: Can you do this in O(N) time and constant space?

*/


int largestNonAdjSum (int* arr, int arrLength) {
  if (arrLength <= 2) {
    return MAX(arr[0], arr[1]);
  }
  int cache[arrLength];
  cache[0] = arr[0];
  cache[1] = MAX(arr[0], arr[1]);
  for (int i = 2; i < arrLength; i++) {
    // There are two possibilities
    // 1. Largest of last adjacent element
    // or
    // 2. Current value + largest of last non-adjacent element
    const int larger = MAX(cache[i-1], arr[i] + cache[i-2]);
    cache[i] = larger;
    printf("cache[%d]=%d\n", i, cache[i]);
  }

  return cache[sizeof(cache)/sizeof(cache[0]) -1];
}

int main (char** argv, int argc) {
  /*
   * largestArr[] = [1, 2, 3,
   */
  int arr[] = {5,1,1,5};
  const int ans = largestNonAdjSum(arr, sizeof(arr) / sizeof(arr[0]));
  printf("answer=%d\n", ans);

  return 0;
}
