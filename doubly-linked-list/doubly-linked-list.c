#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  char *element;
  struct Node *prev;
  struct Node *next;
} Node;

static Node *newNode(char *element, Node *prev) {
  Node *ptr = malloc(sizeof(Node));

  ptr->element = element;
  ptr->prev = prev;
  ptr->next = NULL;

  return ptr;
}

/**
 * A doubly-linked list data structure, where each node in the list will contain
 * references for both the node before it and the node after it.
 */
typedef struct DoublyLinkedList {
  Node *head;
  Node *tail;
} DoublyLinkedList;

DoublyLinkedList *newDoublyLinkedList() {
  DoublyLinkedList *ptr = malloc(sizeof(DoublyLinkedList));

  ptr->head = NULL;
  ptr->tail = NULL;

  return ptr;
}

/** Returns whether or not a doubly-linked-list is empty. */
bool isEmpty(DoublyLinkedList *list) { return list->head == NULL; }

/** Adds an element to the tail end of a doubly-linked list. */
void add(DoublyLinkedList *list, char *element) {
  if (list->tail) {
    list->tail->next = newNode(element, list->tail);
    list->tail = list->tail->next;
  } else {
    list->head = newNode(element, NULL);
    list->tail = list->head;
  }
}

/**
 * Removes all occurrences of a given element from a doubly-linked list.
 *
 * @param list A pointer to the doubly-linked list.
 * @param element The element to be removed.
 * @return The number of occurrences removed.
 */
int removeAll(DoublyLinkedList *list, char *element) {
  if (isEmpty(list))
    return 0;

  int numRemoved = 0;

  // Remove as many heads as necessary
  while (list->head->element == element) {
    Node *removedNode = list->head;

    list->head = list->head->next;
    list->head->prev = NULL;
    numRemoved++;

    free(removedNode);
  }

  // Remove as many tails as necessary
  while (list->tail->element == element) {
    Node *removedNode = list->tail;

    list->tail = list->tail->prev;
    list->tail->next = NULL;
    numRemoved++;

    free(removedNode);
  }

  // Iterate through rest of list
  Node *currentNode = list->head->next;
  while (currentNode->next) {
    if (currentNode->element == element) {
      Node *removedNode = currentNode;

      // Link adjacent nodes
      currentNode->prev->next = currentNode->next;
      currentNode->next->prev = currentNode->prev;
      numRemoved++;

      free(removedNode);
    }
    currentNode = currentNode->next;
  }

  return numRemoved;
}

/** Clears the contents of a doubly-linked list */
void clear(DoublyLinkedList *list) {
  // Free allocated memory
  Node *currentNode = list->head;
  while (currentNode) {
    Node *nextNode = currentNode->next;
    free(currentNode);
    currentNode = nextNode;
  }

  list->head = NULL;
  list->tail = NULL;
}

/** Frees the allocated memory for a doubly-linked list and its contents. */
void destroy(DoublyLinkedList *list) {
  clear(list);
  free(list);
}

/** Reverses a doubly-linked list in place. */
void reverse(DoublyLinkedList *list) {
  if (isEmpty(list))
    return;

  list->head = list->tail;
  Node *currentNode = list->head;
  while (currentNode->prev) {
    // Swap adjacent nodes
    Node *oldPrev = currentNode->prev;
    currentNode->prev = currentNode->next;
    currentNode->next = oldPrev;

    currentNode = currentNode->next;
  }

  // Set new tail
  list->tail = currentNode;
  list->tail->prev = list->tail->next;
  list->tail->next = NULL;
}

/**
 * Prints the contents of a doubly-linked list to the console, head to tail,
 * separated by commas.
 */
void print(DoublyLinkedList *list) {
  if (!isEmpty(list)) {
    printf("\"%s\"", list->head->element);
    Node *currentNode = list->head->next;
    while (currentNode) {
      printf(", \"%s\"", currentNode->element);
      currentNode = currentNode->next;
    }
  }
  printf("\n");
}

int main() {
  DoublyLinkedList *l = newDoublyLinkedList();

  print(l);
  assert(isEmpty(l));

  add(l, "hey");
  add(l, "unicorn");
  print(l);

  add(l, "squirrel");
  add(l, "opera");

  assert(removeAll(l, "boring") == 0);
  add(l, "unicorn");
  assert(removeAll(l, "unicorn") == 2);

  assert(strcmp(l->head->element, "hey") == 0);
  assert(strcmp(l->tail->element, "opera") == 0);
  assert(!isEmpty(l));

  add(l, "gerrymander");

  print(l);
  reverse(l);
  print(l);
  assert(strcmp(l->head->element, "gerrymander") == 0);
  assert(strcmp(l->tail->prev->element, "squirrel") == 0);

  clear(l);
  assert(isEmpty(l));
  assert(l->tail == NULL);

  destroy(l);
  printf("All tests passed successfully.\n");

  return 0;
}
