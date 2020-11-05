#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_LENGTH 26

typedef struct Node {
  struct Node *keys[ALPHABET_LENGTH];
  bool end;
} Node;

Node *newNode() {
  Node *ptr = malloc(sizeof(Node));

  for (int i = 0; i < ALPHABET_LENGTH; i++)
    ptr->keys[i] = NULL;
  ptr->end = false;

  return ptr;
}

static bool isLetter(char c) {
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

static int indexOf(char c) {
  if (!isLetter(c))
    return -1;

  if (c >= 'a')
    // Character is lowercase
    return c - 97;
  else
    // Character is uppercase
    return c - 65;
}

static char charAtIndex(int i) { return i + 97; }

static int numKeys(Node *node) {
  int count = 0;
  for (int i = 0; i < ALPHABET_LENGTH; i++) {
    if (node->keys[i])
      count++;
  }

  return count;
}

/**
 * A trie search tree that stores (case-insensitive) words in an ordered tree
 * structure in which each node represents an individual letter.
 */
typedef struct Trie {
  Node *root;
  int length;
} Trie;

Trie *newTrie() {
  Trie *ptr = malloc(sizeof(Trie));

  ptr->root = newNode();
  ptr->length = 0;

  return ptr;
}

/** Returns the number of words currently stored in a trie search tree. */
int length(Trie *trie) { return trie->length; }

/**
 * Adds a new word to a trie search tree.
 *
 * @param trie A pointer to the trie search tree.
 * @param word The word to add. Only letters are allowed, and words will be
 *   stored case-insensitively.
 * @return `0` if the word was successfully added, `1` if the word was already
 *   present in the trie, or `2` if the word is invalid.
 */
int add(Trie *trie, char *word) {
  // Validate input
  char *currentChar = word;
  do {
    if (!isLetter(*currentChar)) {
      printf(*currentChar ? "Error: word may only contain letters.\n"
                          : "Error: word may not be empty.\n");
      return 2;
    }

    currentChar++;
  } while (*currentChar);

  currentChar = word;
  Node *currentNode = trie->root;

  while (*currentChar) {
    int index = indexOf(*currentChar);

    if (!currentNode->keys[index])
      currentNode->keys[index] = newNode();

    currentNode = currentNode->keys[index];
    currentChar++;
  }

  bool wordAlreadyPresent = currentNode->end;
  if (!wordAlreadyPresent)
    trie->length++;

  currentNode->end = true;

  return (int)wordAlreadyPresent;
}

/** Checks if a specific word is currently stored in a trie search tree. */
bool has(Trie *trie, char *word) {
  char *currentChar = word;
  Node *currentNode = trie->root;

  while (*currentChar) {
    if (!isLetter(*currentChar))
      // Word contains invalid characters
      return false;

    int index = indexOf(*currentChar);

    if (!currentNode->keys[index])
      // Word is not present
      return false;

    currentNode = currentNode->keys[index];
    currentChar++;
  }

  // Word is present if last node is an end point
  return currentNode->end;
}

/**
 * Removes a word from a trie search tree.
 *
 * @param trie A pointer to the trie search tree.
 * @param word The word to remove.
 * @return `0` if the word was successfully removed, `1` if the word was not
 *   present in the trie.
 */
int del(Trie *trie, char *word) {
  int wordLength = strlen(word);

  if (wordLength == 0)
    // Word is empty
    return 1;

  typedef struct {
    Node *node;
    char nextLetter;
  } NodeVector;
  NodeVector nodeVectors[wordLength];

  // Queue nodes for this word while searching
  Node *currentNode = trie->root;
  for (int wordIndex = 0; wordIndex < wordLength; wordIndex++) {
    if (!isLetter(word[wordIndex]))
      // Word contains invalid characters
      return 1;

    int keyIndex = indexOf(word[wordIndex]);

    if (!currentNode->keys[keyIndex])
      // Word is not present
      return 1;

    nodeVectors[wordIndex] = (NodeVector){currentNode, word[wordIndex]};

    currentNode = currentNode->keys[keyIndex];
  }

  if (!currentNode->end)
    // No word endpoint, so word is not present
    return 1;

  // Remove endpoint from last node
  currentNode->end = false;

  bool onSharedPath = numKeys(currentNode) > 0;

  // Remove nodes that aren't part of any other word
  for (int wordIndex = wordLength - 1; wordIndex >= 0 && !onSharedPath;
       wordIndex--) {
    currentNode = nodeVectors[wordIndex].node;
    int nextLetterIndex = indexOf(nodeVectors[wordIndex].nextLetter);

    free(currentNode->keys[nextLetterIndex]);
    currentNode->keys[nextLetterIndex] = NULL;

    onSharedPath = numKeys(currentNode) > 0 || currentNode->end;
  }

  trie->length--;
  return 0;
}

/** Recursively frees memory for a given node and all nodes in its keys. */
static void freeNodesFrom(Node *node) {
  for (int i = 0; i < ALPHABET_LENGTH; i++) {
    if (node->keys[i]) {
      freeNodesFrom(node->keys[i]);
    }
  }
  free(node);
}
/** Clears the contents of a trie search tree. */
void clear(Trie *trie) {
  freeNodesFrom(trie->root);
  trie->root = newNode();
  trie->length = 0;
}

/** Frees the allocated memory for a trie search tree and its contents. */
void destroy(Trie *trie) {
  clear(trie);
  free(trie);
}

/**
 * Recursively adds words accessible through a given node of a trie search tree
 * to a given array.
 */
static void addWordsFrom(Node *node, char *wordSoFar, int lengthSoFar,
                         char **foundWords, int *currentIndex) {
  if (node->end) {
    foundWords[*currentIndex] = wordSoFar;
    *currentIndex += 1;
  }

  for (int i = 0; i < ALPHABET_LENGTH; i++) {
    if (node->keys[i]) {
      char nextSegment[lengthSoFar + 2];
      strcpy(nextSegment, wordSoFar);
      nextSegment[lengthSoFar] = charAtIndex(i);
      nextSegment[lengthSoFar + 1] = '\0';
      addWordsFrom(node->keys[i], nextSegment, lengthSoFar + 1, foundWords,
                   currentIndex);
    }
  }
}
/**
 * Returns a pointer to an array of all words storied in a trie search tree,
 * arranged in alphabetical order (or `NULL` if the tree is empty). Make sure to
 * `free` the pointer when finished with the array.
 */
char **getAll(Trie *trie) {
  if (length(trie) == 0)
    return NULL;

  char **words = malloc(length(trie) * sizeof(char *));
  int currentIndex = 0;

  addWordsFrom(trie->root, "\0", 0, words, &currentIndex);

  return words;
}

int main() {
  Trie *t = newTrie();

  assert(length(t) == 0);
  assert(del(t, "stuff") == 1);
  assert(add(t, "H4Ckz0r5;") == 2);
  assert(add(t, "") == 2);

  assert(add(t, "antidisestablishmentarianism") == 0);
  assert(length(t) == 1);
  assert(add(t, "antidishes") == 0);
  assert(add(t, "antidishes") == 1);
  assert(length(t) == 2);

  assert(add(t, "Ty") == 0);
  assert(add(t, "Tyler") == 0);
  assert(del(t, "antidishes") == 0);
  assert(del(t, "tYlEr") == 0);
  assert(has(t, "tY"));
  assert(has(t, "antidisestablishmentarianism"));
  assert(!has(t, "Tyler"));
  assert(del(t, "Tyler") == 1);

  assert(length(t) == 2);

  char **words = getAll(t);
  assert(strcmp(words[0], "antidisestablishmentarianism") == 0);
  assert(strcmp(words[1], "ty") == 0);
  free(words);

  clear(t);
  clear(t);
  assert(getAll(t) == NULL);
  assert(length(t) == 0);

  add(t, "uhtenohutna");
  destroy(t);

  return 0;
}