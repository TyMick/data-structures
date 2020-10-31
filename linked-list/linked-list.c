#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  char *element;
  struct Node *next;
} Node;

Node *newNode(char *element) {
  Node *ptr = malloc(sizeof(Node));

  ptr->element = element;
  ptr->next = NULL;

  return ptr;
}

/*
 * A linked list data structure, where each node in thi list will contain a
 * reference to the node after it.
 */
typedef struct LinkedList {
  int length;
  Node *head;
} LinkedList;

LinkedList *newLinkedList() {
  LinkedList *ptr = malloc(sizeof(LinkedList));

  ptr->length = 0;
  ptr->head = NULL;

  return ptr;
}

/** Returns the number of elements in a linked list. */
int size(LinkedList *list) { return list->length; }

/** Returns whether or not a linked list is empty. */
bool isEmpty(LinkedList *list) { return size(list) == 0; }

/**
 * Adds an new element to the end of a linked list.
 *
 * @param list A pointer to the linked list.
 * @param element The element to be added.
 */
void add(LinkedList *list, char *element) {
  if (list->head) {
    Node *currentNode = list->head;
    while (currentNode->next) {
      currentNode = currentNode->next;
    }
    currentNode->next = newNode(element);
  } else {
    list->head = newNode(element);
  }
  list->length++;
}

/**
 * Removes the first occurrence of a given element from a linked list (if
 * possible).
 *
 * @param list A pointer to the linked list.
 * @param element The element to be removed.
 * @return The number of occurrences removed.
 */
int removeOne(LinkedList *list, char *element) {
  if (list->head) {
    if (list->head->element == element) {
      Node *removedNode = list->head;

      list->head = list->head->next;
      list->length--;

      free(removedNode);
      return 1;
    } else {
      // Search for element
      Node *currentNode = list->head->next;
      Node *previousNode = list->head;
      while (currentNode) {
        if (currentNode->element == element) {
          // Link adjacent nodes to each other
          previousNode->next = currentNode->next;
          list->length--;

          free(currentNode);
          return 1;
        }

        previousNode = currentNode;
        currentNode = currentNode->next;
      }
    }
  }

  // Element wasn't found
  return 0;
}

/**
 * Removes all occurrences of a given element from a linked list.
 *
 * @param list A pointer to the linked list.
 * @param element The element to be removed.
 * @return The number of occurrences removed.
 */
int removeAll(LinkedList *list, char *element) {
  if (isEmpty(list))
    return 0;

  int oldLength = list->length;

  // Remove as many heads as necessary
  while (list->head->element == element) {
    Node *removedNode = list->head;

    list->head = list->head->next;
    list->length--;

    free(removedNode);
  }

  // Search the rest of list for element
  Node *currentNode = list->head->next;
  Node *previousNode = list->head;
  while (currentNode) {
    if (currentNode->element == element) {
      Node *removedNode = currentNode;

      // Link adjacent nodes to each other
      previousNode->next = currentNode->next;
      list->length--;

      currentNode = currentNode->next;
      free(removedNode);
    } else {
      previousNode = currentNode;
      currentNode = currentNode->next;
    }
  }

  return oldLength - list->length;
}

/**
 * Returns the numerical index of the first occurrence of a given element in a
 * linked list (or `-1` if the list does not contain this element).
 */
int indexOf(LinkedList *list, char *element) {
  int index = 0;
  Node *currentNode = list->head;
  while (currentNode) {
    if (currentNode->element == element) {
      return index;
    }
    currentNode = currentNode->next;
    index++;
  }

  return -1;
}

/**
 * Returns the element at a given index in a linked list (or `NULL` if the list
 * has no such index).
 */
char *elementAt(LinkedList *list, int index) {
  if (index < 0 || index >= list->length) {
    return NULL;
  }

  Node *currentNode = list->head;
  for (int i = 0; i < index; i++) {
    currentNode = currentNode->next;
  }
  return currentNode->element;
}

/**
 * Removes and returns the element at a given index from a linked list (or
 * returns `NULL` if the list has no such index).
 */
char *removeAt(LinkedList *list, int index) {
  if (index < 0 || index >= list->length) {
    return NULL;
  }

  if (index == 0) {
    Node *removedNode = list->head;

    list->head = list->head->next;
    list->length--;

    char *removedElement = removedNode->element;
    free(removedNode);
    return removedElement;
  } else {
    // Find nodes at and around index
    int currentIndex = 1;
    Node *previousNode = list->head;
    Node *currentNode = list->head->next;
    while (currentIndex < index) {
      previousNode = currentNode;
      currentNode = currentNode->next;
      currentIndex++;
    }

    previousNode->next = currentNode->next;
    list->length--;

    char *removedElement = currentNode->element;
    free(currentNode);
    return removedElement;
  }
}

/**
 * Inserts a given element at a given index in a linked list.
 *
 * @param list A pointer to the linked list.
 * @param index The index at which to insert the element.
 * @param element The element to be inserted.
 * @return `0` if the element was successfully inserted, `1` if given an invalid
 *   index.
 */
int insertAt(LinkedList *list, int index, char *element) {
  if (index < 0 || index > list->length) {
    return 1;
  }

  if (index == 0) {
    Node *oldHead = list->head;
    list->head = newNode(element);
    list->head->next = oldHead;
    list->length++;
  } else {
    // Find nodes at and around index
    int currentIndex = 1;
    Node *currentNode = list->head->next;
    Node *previousNode = list->head;
    while (currentIndex < index) {
      previousNode = currentNode;
      currentNode = currentNode->next;
      currentIndex++;
    }

    // Add and link up
    previousNode->next = newNode(element);
    previousNode->next->next = currentNode;

    list->length++;
  }

  return 0;
}

/** Clears the contents of a linked list. */
void clear(LinkedList *list) {
  // Free allocated memory
  Node *currentNode = list->head;
  while (currentNode) {
    Node *nextNode = currentNode->next;
    free(currentNode);
    currentNode = nextNode;
  }

  list->head = NULL;
  list->length = 0;
}

/** Prints the contents of a linked list to a console, separated by commas. */
void print(LinkedList *list) {
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
  LinkedList *l = newLinkedList();

  print(l);
  assert(isEmpty(l));

  add(l, "hey");
  add(l, "unicorn");
  assert(size(l) == 2);
  print(l);

  add(l, "squirrel");
  add(l, "opera");
  assert(insertAt(l, 2, "gait") == 0);
  assert(indexOf(l, "squirrel") == 3);

  assert(removeOne(l, "boring") == 0);
  add(l, "unicorn");
  assert(removeAll(l, "unicorn") == 2);

  assert(strcmp(elementAt(l, 1), "gait") == 0);
  assert(strcmp(removeAt(l, 0), "hey") == 0);
  assert(size(l) == 3);
  assert(!isEmpty(l));

  print(l);

  clear(l);
  assert(isEmpty(l));

  printf("All tests passed successfully.\n");
  free(l);

  return 0;
}
