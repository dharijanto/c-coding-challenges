#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef DEBUG
  #define DEBUG_PRINT printf
#else
  #define DEBUG_PRINT
#endif

/*
Write an algorithm to determine if a number n is "happy".

A happy number is a number defined by the following process: Starting with any positive integer, replace the number by the sum of the squares of its digits, and repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1. Those numbers for which this process ends in 1 are happy numbers.

Return True if n is a happy number, and False if not.

Example:

Input: 19
Output: true
Explanation:
12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1

*/

unsigned int sumOfSquare(unsigned int value) {
  unsigned int sum = 0;
  while (value > 0) {
    unsigned short digit = value % 10;
    sum += digit * digit;
    value /= 10;
  }
  return sum;
}

typedef struct node {
  unsigned int value;
  struct node* next;
} node;

typedef struct set {
  node** nodes;
  unsigned int size;
} set;

// Insert a value into the set
int insert(set* currSet, unsigned int value) {
  // Hash key
  unsigned int key = value % currSet->size;

  node* currentNode = currSet->nodes[key];
  if (currentNode != NULL) {
    // Iterate through the node to find
    if (currentNode->value == value) {
      // Found the value on the first node
      return 0;
    } else {
      // Loop through the node
      while(currentNode->next != NULL) {
        if (currentNode->next->value == value) {
          return 0;
        }
        currentNode = currentNode->next;
      }
      // The value is not on the nodes
      currentNode->next = malloc(sizeof(node));
      currentNode->next->value = value;
      currentNode->next->next = 0;
      return 0;
    }
  } else {
    currSet->nodes[key] = malloc(sizeof(node));
    currSet->nodes[key]->value = value;
    currSet->nodes[key]->next = 0;
    return 0;
  }
}

bool hasValue(set* cSet, unsigned int value) {
  unsigned int key = value % cSet->size;
  node* cNode = cSet->nodes[key];
  if (cNode == NULL) {
    return 0;
  } else {
    while (cNode != NULL) {
      if (cNode->value == value) {
        return 1;
      }
      cNode = cNode->next;
    }
    return 0;
  }
}

/*
 To solve this problem, we gonna use a unique set
 to track whether we come back to a the same number
 when looping through the square of sum. If we do
 it's not a happy number.
*/
bool isHappy(int n){
  set cSet;
  unsigned int size = 99999;
  cSet.nodes = calloc(sizeof(node*), size);
  cSet.size = size;

  while (true) {
    unsigned int sum = sumOfSquare(n);
    DEBUG_PRINT("sum=%ld\n", sum);
    if (sum == 1) {
      return 1;
    } else if (hasValue(&cSet, sum) == true) {
      return 0;
    }
    insert(&cSet, sum);
    n = sum;
  }
}

int main(int argc, char** argv) {
  int number = 19;
  bool happy = isHappy(number);
  DEBUG_PRINT("is %d a happy number? %d\n", number, happy);

  return 0;
}
