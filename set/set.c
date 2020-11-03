#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item {
  char *value;
  struct Item *next;
} Item;

Item *newItem(char *value) {
  Item *ptr = malloc(sizeof(Item));

  ptr->value = value;
  ptr->next = NULL;

  return ptr;
}

/**
 * A set data structure, unordered with no duplicate values, implemented as a
 * hash table. Will hash string keys deterministically to numerical indices
 * (using an admittedly naive hashing function) and store values at those hashed
 * indices to provide more efficient lookup times. This implementation will
 * handle collisions by simply storing multiple values at the same hashed index
 * in a linked list structure.
 */
typedef struct HashTable {
  int numBuckets;
  Item **array;
  int length;
} Set;

Set *newSet(int numBuckets) {
  Set *ptr = malloc(sizeof(Set));

  ptr->numBuckets = numBuckets;
  ptr->array = calloc(numBuckets, sizeof(Item *));
  ptr->length = 0;

  return ptr;
}

static int hash(char *string, int size) {
  int hashed = 0;
  for (int i = 0; string[i]; i++) {
    hashed += string[i];
  }
  return hashed % size;
}

/** Returns the number of items in a set. */
int size(Set *set) { return set->length; }

/** Returns whether or not a set is empty. */
bool isEmpty(Set *set) { return size(set) == 0; }

/**
 * Adds a value to a set (if it is not already present).
 *
 * @param set A pointer to the set.
 * @param value The value to add.
 * @return `0` if the value was successfully added, `1` if the value was already
 *   present in the set.
 */
int add(Set *set, char *value) {
  int index = hash(value, set->numBuckets);

  if (set->array[index]) {
    Item *currentItem = set->array[index];

    if (strcmp(currentItem->value, value) == 0) {
      // Matching value is present
      return 1;
    }

    while (currentItem->next) {
      currentItem = currentItem->next;

      if (strcmp(currentItem->value, value) == 0) {
        // Matching value is present
        return 1;
      }
    }

    // Add new value item
    currentItem->next = newItem(value);
  } else {
    // Add new value item
    set->array[index] = newItem(value);
  }

  set->length++;
  return 0;
}

/** Checks for the presence of a given value in a set. */
bool has(Set *set, char *value) {
  int index = hash(value, set->numBuckets);

  Item *currentItem = set->array[index];

  while (currentItem) {
    if (strcmp(currentItem->value, value) == 0) {
      return true;
    }

    currentItem = currentItem->next;
  }

  // Value was not found
  return false;
}

/**
 * Removes a value from a set (if present).
 *
 * @param set A pointer to the set.
 * @param value The value to remove.
 * @return `0` if a value was removed, `1` if the value was not present in the
 *   set.
 */
int del(Set *set, char *value) {
  int index = hash(value, set->numBuckets);

  if (!set->array[index])
    return 1;

  if (strcmp(set->array[index]->value, value) == 0) {
    Item *deletedItem = set->array[index];

    set->array[index] = set->array[index]->next;
    set->length--;

    free(deletedItem);

    return 0;
  }

  Item *previousItem = set->array[index];
  Item *currentItem = set->array[index]->next;

  while (currentItem) {
    if (strcmp(currentItem->value, value) == 0) {
      previousItem->next = currentItem->next;
      set->length--;

      free(currentItem);

      return 0;
    }

    previousItem = currentItem;
    currentItem = currentItem->next;
  }

  // Value was not present
  return 1;
}

/** Clears the contents of a set. */
void clear(Set *set) {
  for (int i = 0; i < set->numBuckets; i++) {
    Item *currentItem = set->array[i];
    while (currentItem) {
      Item *nextItem = currentItem->next;
      free(currentItem);
      currentItem = nextItem;
    }

    set->array[i] = NULL;
  }

  set->length = 0;
}

/**
 * Frees the allocated memory for a set, its internal array, and its contents.
 */
void destroy(Set *set) {
  clear(set);
  free(set->array);
  free(set);
}

/**
 * Prints the contents of a set to the console (in an arbitrary order determined
 * by internal structure, not by values or insertion order).
 */
void print(Set *set) {
  printf("{");

  bool firstItemAlreadyPrinted = false;
  for (int i = 0; i < set->numBuckets; i++) {
    Item *currentItem = set->array[i];

    while (currentItem) {
      if (firstItemAlreadyPrinted) {
        printf(",");
      } else {
        firstItemAlreadyPrinted = true;
      }

      printf(" \"%s\"", currentItem->value);

      currentItem = currentItem->next;
    }
  }

  printf(" }\n");
}

int main() {
  Set *s = newSet(100);

  assert(isEmpty(s));
  assert(size(s) == 0);
  assert(del(s, "things") == 1);
  print(s);

  add(s, "legs");
  add(s, "tails");
  assert(has(s, "legs"));
  assert(has(s, "tails"));
  print(s);

  add(s, "legs");
  assert(has(s, "legs"));
  assert(!isEmpty(s));
  assert(size(s) == 2);
  print(s);

  assert(!has(s, "eyes"));

  assert(del(s, "tails") == 0);
  assert(!has(s, "tails"));
  print(s);

  assert(del(s, "noses") == 1);
  assert(del(s, "tails") == 1);

  clear(s);
  assert(isEmpty(s));
  assert(!has(s, "legs"));
  print(s);

  destroy(s);
  return 0;
}
