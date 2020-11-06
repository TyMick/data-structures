#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int value;
  struct Node *left;
  struct Node *right;
} Node;

static Node *newNode(int value) {
  Node *ptr = malloc(sizeof(Node));

  ptr->value = value;
  ptr->left = NULL;
  ptr->right = NULL;

  return ptr;
}

/**
 * A binary search tree data structure, which will be ordered with respect to
 * the child subtrees such that the value of each node in a left subtree is less
 * than the value of the parent node, and the value of each node in a right
 * subtree is greater than the value of the parent node.
 */
typedef struct BinarySearchTree {
  Node *root;
  int size;
} BinarySearchTree;

BinarySearchTree *NewBinarySearchTree() {
  BinarySearchTree *ptr = malloc(sizeof(BinarySearchTree));

  ptr->root = NULL;
  ptr->size = 0;

  return ptr;
}

/** Returns the current number of values in a binary search tree. */
int size(BinarySearchTree *tree) { return tree->size; }

/**
 * Adds a value to a binary search tree.
 *
 * @param tree A pointer to the binary search tree.
 * @param value The value to be added.
 * @return `0` if the value was successfully added, `1` if the value was already
 *   present in the tree.
 */
int add(BinarySearchTree *tree, int value) {
  if (tree->root) {
    Node *currentNode = tree->root;
    while (currentNode->value != value) {
      if (value < currentNode->value) {
        if (currentNode->left) {
          // Continue
          currentNode = currentNode->left;
        } else {
          // Add new value
          currentNode->left = newNode(value);
          tree->size++;
          return 0;
        }
      } else {
        if (currentNode->right) {
          // Continue
          currentNode = currentNode->right;
        } else {
          // Add new value
          currentNode->right = newNode(value);
          tree->size++;
          return 0;
        }
      }
    }

    // Value is already present
    return 1;
  } else {
    // Add new value as root
    tree->root = newNode(value);
    tree->size++;
    return 0;
  }
}

/**
 * Removes a given value from a binary search tree, maintaining binary tree
 * structure.
 *
 * @param tree A pointer to the binary search tree.
 * @param value The value to be removed.
 * @return `0` if the value was successfully removed, `1` if the value was not
 *   present in the tree.
 */
int del(BinarySearchTree *tree, int value) {
  if (!tree->root)
    return 1;

  Node *target = tree->root;
  Node *parent = NULL;
  while (target) {
    if (value < target->value) {
      parent = target;
      target = target->left;
    } else if (value > target->value) {
      parent = target;
      target = target->right;
    } else {
      break;
    }
  }

  if (!target)
    // Value was not found
    return 1;

  int numChildren = !!target->left + !!target->right;

  // Case 1: target has no children
  if (numChildren == 0) {
    if (parent) {
      // Remove parent reference
      if (target == parent->left) {
        parent->left = NULL;
      } else {
        parent->right = NULL;
      }
    } else {
      // Root is the only node
      tree->root = NULL;
    }
  }

  // Case 2: target has one child
  else if (numChildren == 1) {
    if (parent) {
      // Link child to parent
      if (target == parent->left) {
        parent->left = target->left ? target->left : target->right;
      } else {
        parent->right = target->left ? target->left : target->right;
      }
    } else {
      // Make child the new root
      tree->root = target->left ? target->left : target->right;
    }
  }

  // Case 3: target has two children
  else {
    // Find replacement
    Node *replacement = target->right;
    Node *leafParent = NULL;
    while (replacement->left) {
      leafParent = replacement;
      replacement = replacement->left;
    }

    if (leafParent) {
      // Replacement is a leaf
      // Remove parent reference
      leafParent->left = NULL;

      // Link replacement to target children
      replacement->left = target->left;
      replacement->right = target->right;
    } else {
      // Link replacement to target left child
      replacement->left = target->left;
    }

    // Link replacement to parent
    if (parent) {
      if (target == parent->left) {
        parent->left = replacement;
      } else {
        parent->right = replacement;
      }
    } else {
      tree->root = replacement;
    }
  }

  free(target);
  tree->size--;
  return 0;
}

/**
 * Returns whether or not the given value is present in a binary search tree.
 */
bool has(BinarySearchTree *tree, int value) {
  Node *currentNode = tree->root;
  while (currentNode) {
    if (value < currentNode->value) {
      currentNode = currentNode->left;
    } else if (value > currentNode->value) {
      currentNode = currentNode->right;
    } else {
      return true;
    }
  }

  // Value is not present
  return false;
}

/** Recursively frees memory for a given node and all child nodes. */
static void freeNodesFrom(Node *node) {
  if (node->left)
    freeNodesFrom(node->left);
  if (node->right)
    freeNodesFrom(node->right);
  free(node);
}
/** Clears the contents of a binary search tree. */
void clear(BinarySearchTree *tree) {
  if (tree->root)
    freeNodesFrom(tree->root);

  tree->root = NULL;
  tree->size = 0;
}

/** Frees the allocated memory for a binary search tree and its contents. */
void destroy(BinarySearchTree *tree) {
  clear(tree);
  free(tree);
}

/**
 * Finds the minimum value in a binary search tree.
 *
 * @param tree A pointer to the binary search tree.
 * @return A pointer to the minimum value, or `NULL` if the tree is empty. Make
 *   sure to `free` the pointer once you're done with it.
 */
int *findMin(BinarySearchTree *tree) {
  if (!tree->root)
    return NULL;

  Node *currentNode = tree->root;
  while (currentNode->left) {
    currentNode = currentNode->left;
  }

  return &currentNode->value;
}

/**
 * Finds the maximum value in a binary search tree.
 *
 * @param tree A pointer to the binary search tree.
 * @return A pointer to the maximum value, or `NULL` if the tree is empty.
 */
int *findMax(BinarySearchTree *tree) {
  if (!tree->root)
    return NULL;

  Node *currentNode = tree->root;
  while (currentNode->right) {
    currentNode = currentNode->right;
  }

  return &currentNode->value;
}

/**
 * Recursively returns the maximum tree height accessible through a given node.
 */
static int maxHeightThrough(Node *node, int currentDepth) {
  if (node->left == NULL && node->right == NULL) {
    return currentDepth;
  } else if (node->left == NULL) {
    return maxHeightThrough(node->right, currentDepth + 1);
  } else if (node->right == NULL) {
    return maxHeightThrough(node->left, currentDepth + 1);
  } else {
    int leftMax = maxHeightThrough(node->left, currentDepth + 1);
    int rightMax = maxHeightThrough(node->right, currentDepth + 1);
    return leftMax >= rightMax ? leftMax : rightMax;
  }
}
/**
 * Returns the distance from a binary search tree's root node to its farthest
 * leaf node (or `-1` if the tree is empty).
 */
int maxHeight(BinarySearchTree *tree) {
  if (tree->root)
    return maxHeightThrough(tree->root, 0);
  else
    return -1;
}

/**
 * Recursively returns the minimum tree height accessible through a given node.
 */
static int minHeightThrough(Node *node, int currentDepth) {
  if (node->left == NULL && node->right == NULL) {
    return currentDepth;
  } else if (node->left == NULL) {
    return maxHeightThrough(node->right, currentDepth + 1);
  } else if (node->right == NULL) {
    return maxHeightThrough(node->left, currentDepth + 1);
  } else {
    int leftMax = maxHeightThrough(node->left, currentDepth + 1);
    int rightMax = maxHeightThrough(node->right, currentDepth + 1);
    return leftMax <= rightMax ? leftMax : rightMax;
  }
}
/**
 * Returns the distance from a binary search tree's root node to its nearest
 * leaf node (or `-1` if the tree is empty).
 */
int minHeight(BinarySearchTree *tree) {
  if (tree->root)
    return minHeightThrough(tree->root, 0);
  else
    return -1;
}

/**
 * Recursively finds both the minimum and maximum tree height accessible through
 * a given node, returning the two values via passed parameters.
 */
static void minMaxHeightThrough(Node *node, int currentDepth, int *min,
                                int *max) {
  if (node->left == NULL && node->right == NULL) {
    *min = *max = currentDepth;
  } else if (node->left == NULL) {
    minMaxHeightThrough(node->right, currentDepth + 1, min, max);
  } else if (node->right == NULL) {
    minMaxHeightThrough(node->left, currentDepth + 1, min, max);
  } else {
    int leftMin, leftMax, rightMin, rightMax;
    minMaxHeightThrough(node->left, currentDepth + 1, &leftMin, &leftMax);
    minMaxHeightThrough(node->right, currentDepth + 1, &rightMin, &rightMax);

    *min = leftMin <= rightMin ? leftMin : rightMin;
    *max = leftMax >= rightMax ? leftMax : rightMax;
  }
}
/**
 * Returns whether or not a binary search tree is balanced (if its minimum
 * height and maximum height differ by at most 1).
 */
bool isBalanced(BinarySearchTree *tree) {
  if (tree->root) {
    int minHeight, maxHeight;
    minMaxHeightThrough(tree->root, 0, &minHeight, &maxHeight);

    return maxHeight - minHeight <= 1;
  } else {
    return true;
  }
}

/**
 * Recursively adds values to a given array in an in-order depth-first traversal
 * manner, starting from a given node.
 */
static void addValuesInorderFrom(Node *node, int *valuesArray,
                                 int *currentIndex) {
  if (node) {
    // Add left values
    addValuesInorderFrom(node->left, valuesArray, currentIndex);
    // Add this node's value
    valuesArray[*currentIndex] = node->value;
    *currentIndex += 1;
    // Add right values
    addValuesInorderFrom(node->right, valuesArray, currentIndex);
  }
}
/**
 * Returns a pointer to an array of all values in a binary search tree arranged
 * in the sequence of an in-order depth-first traversal of the tree (or `NULL`
 * if the tree is empty). Make sure to `free` the pointer when finished with the
 * array.
 */
int *inorder(BinarySearchTree *tree) {
  if (tree->size == 0)
    return NULL;

  int *values = malloc(tree->size * sizeof(int));
  int currentIndex = 0;

  addValuesInorderFrom(tree->root, values, &currentIndex);

  return values;
}

/**
 * Recursively adds values to a given array in a pre-order depth-first traversal
 * manner, starting from a given node.
 */
static void addValuesPreorderFrom(Node *node, int *valuesArray,
                                  int *currentIndex) {
  if (node) {
    // Add this node's value
    valuesArray[*currentIndex] = node->value;
    *currentIndex += 1;
    // Add left values
    addValuesPreorderFrom(node->left, valuesArray, currentIndex);
    // Add right values
    addValuesPreorderFrom(node->right, valuesArray, currentIndex);
  }
}
/**
 * Returns an array of all values in a binary search tree arranged in the
 * sequence of a pre-order depth-first traversal of the tree (or `NULL` if the
 * tree is empty). Make sure to `free` the pointer when finished with the array.
 */
int *preorder(BinarySearchTree *tree) {
  if (tree->size == 0)
    return NULL;

  int *values = malloc(tree->size * sizeof(int));
  int currentIndex = 0;

  addValuesPreorderFrom(tree->root, values, &currentIndex);

  return values;
}

/**
 * Recursively adds values to a given array in a post-order depth-first
 * traversal manner, starting from a given node.
 */
static void addValuesPostorderFrom(Node *node, int *valuesArray,
                                   int *currentIndex) {
  if (node) {
    // Add left values
    addValuesPostorderFrom(node->left, valuesArray, currentIndex);
    // Add right values
    addValuesPostorderFrom(node->right, valuesArray, currentIndex);
    // Add this node's value
    valuesArray[*currentIndex] = node->value;
    *currentIndex += 1;
  }
}
/**
 * Returns an array of all values in a binary search tree arranged in the
 * sequence of a post-order depth-first traversal of the tree (or `NULL` if the
 * tree is empty). Make sure to `free` the pointer when finished with the array.
 */
int *postorder(BinarySearchTree *tree) {
  if (tree->size == 0)
    return NULL;

  int *values = malloc(tree->size * sizeof(int));
  int currentIndex = 0;

  addValuesPostorderFrom(tree->root, values, &currentIndex);

  return values;
}

/**
 * Returns a pointer to an array of all values in a binary search tree arranged
 * in the sequence of a left-to-right breadth-first traversal of the tree (or
 * `NULL` if the tree is empty). Make sure to `free` the pointer when finished
 * with the array.
 */
int *levelOrder(BinarySearchTree *tree) {
  if (tree->size == 0)
    return NULL;

  int *values = malloc(tree->size * sizeof(int));

  Node **nodeQueue = malloc(tree->size * sizeof(Node));
  nodeQueue[0] = tree->root;
  int write = 1;
  int read = 0;

  while (read < tree->size) {
    // Add current value
    values[read] = nodeQueue[read]->value;

    // Add children to queue
    if (nodeQueue[read]->left)
      nodeQueue[write++] = nodeQueue[read]->left;
    if (nodeQueue[read]->right)
      nodeQueue[write++] = nodeQueue[read]->right;

    read++;
  }

  free(nodeQueue);

  return values;
}

/**
 * Returns a pointer to an array of all values in a binary search tree arranged
 * in the sequence of a right-to-left breadth-first traversal of the tree (or
 * `NULL` if the tree is empty). Make sure to `free` the pointer when finished
 * with the array.
 */
int *reverseLevelOrder(BinarySearchTree *tree) {
  if (tree->size == 0)
    return NULL;

  int *values = malloc(tree->size * sizeof(int));

  Node **nodeQueue = malloc(tree->size * sizeof(Node));
  nodeQueue[0] = tree->root;
  int write = 1;
  int read = 0;

  while (read < tree->size) {
    // Add current value
    values[read] = nodeQueue[read]->value;

    // Add children to queue
    if (nodeQueue[read]->right)
      nodeQueue[write++] = nodeQueue[read]->right;
    if (nodeQueue[read]->left)
      nodeQueue[write++] = nodeQueue[read]->left;

    read++;
  }

  free(nodeQueue);

  return values;
}

/**
 * Recursively inverts a binary search tree in-place from a given node downward.
 */
static void invertFrom(Node *node) {
  if (node) {
    // Swap children
    Node *oldLeft = node->left;
    node->left = node->right;
    node->right = oldLeft;

    if (node->left)
      invertFrom(node->left);
    if (node->right)
      invertFrom(node->right);
  }
}
/**
 * Inverts a binary search tree in-place in linear time, transforming it into
 * its mirror image, such that an in-order traversal of this inverted tree will
 * visit nodes in the reverse order of an in-order traversal of the original
 * tree.
 */
void invert(BinarySearchTree *tree) { invertFrom(tree->root); }

/**
 * Checks if a sub-tree from a given node downward is a properly structured
 * binary search tree (that uses "root", "left", "right", and "value"
 * properties).
 */
static bool isBinarySearchNode(Node *node) {
  if (node == NULL)
    return true;

  if (node->left == NULL && node->right == NULL)
    return true;
  else if (node->left == NULL && node->right->value > node->value)
    return isBinarySearchNode(node->right);
  else if (node->right == NULL && node->left->value < node->value)
    return isBinarySearchNode(node->left);
  else if (node->left->value < node->value && node->right->value > node->value)
    return isBinarySearchNode(node->left) && isBinarySearchNode(node->right);
  else
    return false;
}
/**
 * Checks if a passed argument is a properly structured binary search tree (that
 * uses "root", "left", "right", and "value" properties).
 */
bool isBinarySearchTree(BinarySearchTree *tree) {
  return isBinarySearchNode(tree->root);
}

int main() {
  BinarySearchTree *t = NewBinarySearchTree();

  assert(size(t) == 0);
  assert(del(t, 84) == 1);
  assert(minHeight(t) == -1);
  assert(maxHeight(t) == -1);
  assert(isBalanced(t));

  assert(add(t, 1) == 0);
  assert(add(t, 1) == 1);
  assert(add(t, 5) == 0);
  assert(add(t, 3) == 0);
  assert(add(t, 2) == 0);
  assert(add(t, 4) == 0);

  assert(size(t) == 5);
  assert(has(t, 3));
  assert(!has(t, -5));

  int *v = inorder(t);
  assert(v[0] == 1);
  assert(v[1] == 2);
  assert(v[2] == 3);
  assert(v[3] == 4);
  assert(v[4] == 5);
  free(v);

  v = preorder(t);
  assert(v[0] == 1);
  assert(v[1] == 5);
  assert(v[2] == 3);
  assert(v[3] == 2);
  assert(v[4] == 4);
  free(v);

  v = postorder(t);
  assert(v[0] == 2);
  assert(v[1] == 4);
  assert(v[2] == 3);
  assert(v[3] == 5);
  assert(v[4] == 1);
  free(v);

  add(t, 0);

  v = levelOrder(t);
  assert(v[0] == 1);
  assert(v[1] == 0);
  assert(v[2] == 5);
  assert(v[3] == 3);
  assert(v[4] == 2);
  assert(v[5] == 4);
  free(v);

  v = reverseLevelOrder(t);
  assert(v[0] == 1);
  assert(v[1] == 5);
  assert(v[2] == 0);
  assert(v[3] == 3);
  assert(v[4] == 4);
  assert(v[5] == 2);
  free(v);

  assert(isBinarySearchTree(t));

  invert(t);
  v = levelOrder(t);
  assert(v[0] == 1);
  assert(v[1] == 5);
  assert(v[2] == 0);
  assert(v[3] == 3);
  assert(v[4] == 4);
  assert(v[5] == 2);
  free(v);
  assert(!isBinarySearchTree(t));
  invert(t);

  assert(minHeight(t) == 1);
  assert(maxHeight(t) == 3);
  assert(!isBalanced(t));

  add(t, -1);
  assert(minHeight(t) == 2);
  assert(isBalanced(t));

  assert(del(t, 1) == 0);
  assert(t->root->value == 2);

  add(t, 8);
  add(t, -8);
  add(t, -4);
  add(t, -2);
  add(t, -3);
  del(t, -4);
  del(t, 5);
  add(t, 6);

  v = inorder(t);
  for (int i = 1; i < size(t); i++) {
    assert(v[i] > v[i - 1]);
  }
  free(v);

  destroy(t);
  printf("All tests passed successfully.\n");

  return 0;
}
