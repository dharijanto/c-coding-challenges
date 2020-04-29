#include "stdio.h"
#include "stdlib.h"

/*
This problem was asked by Google.

An XOR linked list is a more memory efficient doubly linked list. Instead of each node holding next and prev fields, it holds a field named both, which is an XOR of the next node and the previous node. Implement an XOR linked list; it has an add(element) which adds the element to the end, and a get(index) which returns the node at index.

If using a language that has no pointers (such as Python), you can assume you have access to get_pointer and dereference_pointer functions that converts between nodes and memory addresses.
*/

struct Node {
  int value;
  void* both;
};

struct Node* head = NULL;
struct Node* tail = NULL;

void add(int value) {
  if (head == NULL) {
    head = malloc(sizeof(struct Node));
    head->value = value;
    head->both = NULL;
    tail = head;
  } else {
    /*
     * Original:
     * ... -> [TAIL]
     * New:
     * ... -> [TAIL] -> [NEW]
     */
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->value = value;
    // newNode is the new tail and since it has no 'next', its both is just 'prev'
    newNode->both = (void*) tail;
    // tail->both previously onlyt refers to 'prev' element, hence we can just xor it
    tail->both = (void*) ((long) tail->both ^ (long) newNode);
    tail = newNode;
  }
}

struct Node* get(int index) {
  void* prevPtr = 0;
  struct Node* current = head;
  while (current != tail && index > 0) {
     struct Node* next = (void*) ((long)current->both ^ (long)prevPtr);
     prevPtr = current;
     current = next;
     index--;
  }

  if (index > 0) {
    return NULL;
  } else {
    return current;
  }
}

int main(int argc, char** argv) {
  add(5);
  add(3);
  add(2);

  struct Node* node;
  for (int i = 0; i < 5; i++) {
    node = get(i);
    if (node) {
      printf("hello! value=%d\n", node->value);
    } else {
      printf("node is NULL!\n");
    }
  }
}
