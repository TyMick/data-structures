#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item {
  char *key;
  int value;
  struct Item *next;
} Item;

Item *newItem(char *key, int value) {
  Item *ptr = malloc(sizeof(Item));

  ptr->key = key;
  ptr->value = value;
  ptr->next = NULL;

  return ptr;
}

/**
 * A hash table data structure. Will hash string keys deterministically to
 * numerical indices (using an admittedly naive hashing function) and store key-
 * value pairs at those hashed indices to provide more efficient lookup times.
 * This implementation will handle collisions by simply storing multiple key-
 * value pairs at the same hashed index in a linked list structure.
 */
typedef struct HashTable {
  int numBuckets;
  Item **array;
} HashTable;

HashTable *newHashTable(int numBuckets) {
  HashTable *ptr = malloc(sizeof(HashTable));

  ptr->numBuckets = numBuckets;
  ptr->array = calloc(numBuckets, sizeof(Item *));

  return ptr;
}

static int hash(char *string, int size) {
  int hashed = 0;
  for (int i = 0; string[i]; i++) {
    hashed += string[i];
  }
  return hashed % size;
}

/**
 * Adds a key-value pair to a hash table, overwriting a matching key if one is
 * already present in the table.
 */
void set(HashTable *table, char *key, int value) {
  int index = hash(key, table->numBuckets);

  if (table->array[index]) {
    Item *currentItem = table->array[index];

    while (currentItem) {
      if (strcmp(currentItem->key, key) == 0) {
        // Matching key is present; overwrite existing value
        currentItem->value = value;
        break;
      }

      if (!currentItem->next) {
        // Add new key-value item
        currentItem->next = newItem(key, value);
        break;
      }

      currentItem = currentItem->next;
    }
  } else {
    table->array[index] = newItem(key, value);
  }
}

/**
 * Retrieves a given key's associated value in a hash table.
 *
 * @param table A pointer to the hash table.
 * @param key The key to search for.
 * @return A pointer to the key's associated value (or `NULL` if the key is not
 *   present in the table).
 */
int *get(HashTable *table, char *key) {
  int index = hash(key, table->numBuckets);

  Item *currentItem = table->array[index];

  while (currentItem) {
    if (strcmp(currentItem->key, key) == 0) {
      return &currentItem->value;
    }

    currentItem = currentItem->next;
  }

  // Key was not found
  return NULL;
}

/**
 * Given a key, removes its key-value pair from a hash table (if present).
 *
 * @param table A pointer to the hash table.
 * @param key The key to remove.
 * @return `0` if a key-value pair was removed, `1` if the key was not present
 *   in the table.
 */
int del(HashTable *table, char *key) {
  int index = hash(key, table->numBuckets);

  if (!table->array[index])
    return 1;

  if (strcmp(table->array[index]->key, key) == 0) {
    Item *deletedItem = table->array[index];

    table->array[index] = table->array[index]->next;

    free(deletedItem);

    return 0;
  }

  Item *previousItem = table->array[index];
  Item *currentItem = table->array[index]->next;

  while (currentItem) {
    if (strcmp(currentItem->key, key) == 0) {
      previousItem->next = currentItem->next;

      free(currentItem);

      return 0;
    }

    previousItem = currentItem;
    currentItem = currentItem->next;
  }

  // Key was not present
  return 1;
}

/** Clears the contents of a hash table. */
void clear(HashTable *table) {
  for (int i = 0; i < table->numBuckets; i++) {
    Item *currentItem = table->array[i];
    while (currentItem) {
      Item *nextItem = currentItem->next;
      free(currentItem);
      currentItem = nextItem;
    }

    table->array[i] = NULL;
  }
}

/**
 * Prints the contents of a hash table to the console (in an arbitrary order
 * determined by internal structure, not by keys, values, or insertion order).
 */
void print(HashTable *table) {
  printf("{");

  bool firstItemAlreadyPrinted = false;
  for (int i = 0; i < table->numBuckets; i++) {
    Item *currentItem = table->array[i];

    while (currentItem) {
      if (firstItemAlreadyPrinted) {
        printf(",");
      } else {
        firstItemAlreadyPrinted = true;
      }

      printf(" \"%s\": %d", currentItem->key, currentItem->value);

      currentItem = currentItem->next;
    }
  }

  printf(" }\n");
}

int main() {
  HashTable *t = newHashTable(100);

  assert(del(t, "things") == 1);
  print(t);

  set(t, "legs", 4);
  set(t, "tails", 1);
  assert(*get(t, "legs") == 4);
  assert(*get(t, "tails") == 1);
  print(t);

  set(t, "legs", 6);
  assert(*get(t, "legs") == 6);
  print(t);

  assert(get(t, "eyes") == NULL);

  assert(del(t, "tails") == 0);
  assert(get(t, "tails") == NULL);
  print(t);

  assert(del(t, "noses") == 1);
  assert(del(t, "tails") == 1);

  clear(t);
  assert(get(t, "legs") == NULL);
  print(t);

  free(t);
  return 0;
}