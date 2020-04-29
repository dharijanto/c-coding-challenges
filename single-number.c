/*
Given a non-empty array of integers, every element appears twice except for one. Find that single one.

Note:

Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

Example 1:

Input: [2,2,1]
Output: 1

Example 2:

Input: [4,1,2,1,2]
Output: 4
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef DEBUG
  #define DEBUG_PRINT
#else
  #define DEBUG_PRINT
#endif

typedef struct node {
  int value;
  int count;
  struct node* next;
} node;

int getCount(node* hashTable[], int numsSize, int value) {
  int key = abs(value % numsSize);
  DEBUG_PRINT("key=%d\n", key);
  if (key >= numsSize) {
    return -1;
  }
  node* entry = hashTable[key];

  while (entry != NULL) {
    if (entry->value == value) {
      return entry->count;
    }
    entry = entry->next;
  }
  return 0;
}

int setCount(node* hashTable[], int numsSize, int value, int count) {
  int key = abs(value % numsSize);
  node* entry = hashTable[key];
  if (entry == NULL) {
    hashTable[key] = malloc(sizeof(node));
    hashTable[key]->value = value;
    hashTable[key]->count = count;
    hashTable[key]->next = NULL;
  } else {
    if (entry->value == value) {
      entry->count = count;
    } else {
      while (entry->next != NULL) {
        if (entry->next->value == value) {
          entry->next->count = count;
          break;
        } else {
          entry = entry->next;
        }
      }
      // This means no value was found
      if (entry->next == NULL) {
        entry->next = malloc(sizeof(node));
        entry->next->value = value;
        entry->next->count = count;
        entry->next->next = NULL;
      }
    }
  }
  return 0;
}

void printHashTable(node* hashTable[], int numsSize) {
  for (int i = 0; i < numsSize; i++) {
    node* entry = hashTable[i];
    while (entry != NULL) {
      DEBUG_PRINT("{%d}->{%d}\n", entry->value, entry->count);
      entry = entry->next;
    }
  }
}

int findSingleNumber(node* hashTable[], int numsSize) {
  for (int i = 0; i < numsSize; i++) {
    node* entry = hashTable[i];
    while (entry != NULL) {
      if (entry->count == 1) {
        return entry->value;
      }
      entry = entry->next;
    }
  }
  return -1;
}

void freeHashTable(node* hashTable[], int numsSize) {

}

int singleNumber(int* nums, int numsSize) {
  node* hashTable[numsSize];
  memset(hashTable, 0, sizeof(hashTable));

  for (int i = 0; i < numsSize; i++) {
    DEBUG_PRINT("value=%d\n", nums[i]);
    int count = getCount(hashTable, numsSize, nums[i]);
    int ret = setCount(hashTable, numsSize, nums[i], count + 1);
    if (ret == -1) {
      DEBUG_PRINT("Error on setting value!");
      exit(1);
    }

    printHashTable(hashTable,numsSize);
  }

  DEBUG_PRINT("finished!\n");
  printHashTable(hashTable, numsSize);
  freeHashTable(hashTable, numsSize);
  int single = findSingleNumber(hashTable,numsSize);
  DEBUG_PRINT("single number=%d\n", single);
  return single;
  // Iterate through the hash table to find
  // the key whose count is 1
}

int main(int argc, char** argv) {
  // int arr[] = {4,1,2,1,2};
  int arr[] = {-1,-1,-2};
  singleNumber(arr, sizeof(arr) / sizeof(int));
  DEBUG_PRINT("Hello world!\n");
}
