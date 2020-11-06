#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * A binary max heap implemented as an implicit data structure. Keys are stored
 * as an array, and parent-child relationships will be determined by relative
 * positions within the array: for an element at given index `i`, its children
 * will be located at `2 * i + 1` and `2 * i + 2`, and its parent will be
 * located at `(i - 1) / 2` (using integer division). All parent nodes will be
 * greater than or equal to their child nodes.
 */
typedef struct MaxHeap {
  int maxSize;
  int length;
  int array[];
} MaxHeap;

/**
 * Constructs a new instance of a max heap and returns a pointer to it. (Make
 * sure to `free` the pointer once you're finished with it.)
 */
MaxHeap *newMaxHeap(int maxSize) {
  if (maxSize < 1) {
    printf("Error: maximum size must be positive.\n");
    return NULL;
  }

  MaxHeap *ptr = malloc(sizeof(MaxHeap) + maxSize * sizeof(int));

  ptr->maxSize = maxSize;
  ptr->length = 0;

  return ptr;
}

/** Returns the number of values in a max heap. */
int length(MaxHeap *heap) { return heap->length; }

/** Returns whether or not a max heap is empty. */
bool isEmpty(MaxHeap *heap) { return length(heap) == 0; }

/** Returns whether or not a max heap is full. */
bool isFull(MaxHeap *heap) { return length(heap) == heap->maxSize; }

/**
 * Adds a value to a max heap, maintaining the heap property.
 *
 * @param heap A pointer to the max heap.
 * @param value The value to add.
 * @return `0` if the value was successfully added, `1` if the max heap was
 *   already at maximum capacity (stack overflow).
 */
int push(MaxHeap *heap, int value) {
  if (isFull(heap)) {
    printf("Error: stack overflow: heap is already at maximum capacity\n");
    return 1;
  }

  int currentIndex = heap->length;
  int parentIndex = (currentIndex - 1) / 2;
  while (currentIndex > 0 && value > heap->array[parentIndex]) {
    // Switch with parent
    heap->array[currentIndex] = heap->array[parentIndex];
    currentIndex = parentIndex;

    parentIndex = (currentIndex - 1) / 2;
  }

  heap->array[currentIndex] = value;
  heap->length++;
  return 0;
}

/**
 * Removes and returns the greatest value in a max heap, reordering the internal
 * array to maintain the heap property.
 *
 * @param heap A pointer to the max heap.
 * @return A pointer to an integer denoting the value removed, or `NULL` if the
 *   max heap was already empty.
 */
int *pop(MaxHeap *heap) {
  if (isEmpty(heap))
    return NULL;

  // Save return value
  int max = heap->array[0];

  heap->length--;

  if (heap->length == 0) {
    int *ptr = &max;
    return ptr;
  }

  // Rebalance the heap by moving the last element into the root position, then
  // continuing to swap it with its greatest-valued child until it is greater
  // than both children or it reaches the last level of the tree
  int currentIdx = 0;
  int child1Idx = 2 * currentIdx + 1;
  int child2Idx = 2 * currentIdx + 2;
  int value = heap->array[heap->length];
  while ((child1Idx < heap->length && value < heap->array[child1Idx]) ||
         (child2Idx < heap->length && value < heap->array[child2Idx])) {
    if (child2Idx >= heap->length ||
        heap->array[child1Idx] > heap->array[child2Idx]) {
      // Swap with child 1
      heap->array[currentIdx] = heap->array[child1Idx];
      currentIdx = child1Idx;
    } else {
      // Swap with child 2
      heap->array[currentIdx] = heap->array[child2Idx];
      currentIdx = child2Idx;
    }

    child1Idx = 2 * currentIdx + 1;
    child2Idx = 2 * currentIdx + 2;
  }

  heap->array[currentIdx] = value;

  int *ptr = &max;
  return ptr;
}

/**
 * Returns an array of all values currently stored in a max heap (in the order
 * of the internal data structure).
 *
 * @param heap A pointer to the max heap.
 * @return `NULL` if the heap is currently empty; otherwise, a pointer to the
 *   first element of the array of values. Take care not to attempt to access
 *   array members at indices of `heap->length` or greater, as this will produce
 *   garbage values.
 */
int *print(MaxHeap *heap) {
  if (isEmpty(heap))
    return NULL;

  int array[heap->length];
  for (int i = 0; i < heap->length; i++) {
    array[i] = heap->array[i];
  }

  int *ptr = array;
  return ptr;
}

/** Clears the contents of a max heap. */
void clear(MaxHeap *heap) { heap->length = 0; }

/** Creates a deep clone of a max heap. */
MaxHeap *clone(MaxHeap *original) {
  MaxHeap *clone = newMaxHeap(original->maxSize);
  clone->length = original->length;
  for (int i = 0; i < original->length; i++) {
    clone->array[i] = original->array[i];
  }

  return clone;
}

/**
 * Returns a pointer to an array of all values in a max heap ordered from
 * greatest to least.
 *
 * @param heap A pointer to the max heap.
 * @return `NULL` if the heap is currently empty; otherwise, a pointer to the
 *   first element of the array of values. Take care not to attempt to access
 *   array members at indices of `heap->length` or greater, as this will produce
 *   garbage values.
 */
int *sort(MaxHeap *heap) {
  if (isEmpty(heap))
    return NULL;

  MaxHeap *copy = clone(heap);

  int sorted[heap->length];
  for (int i = 0; i < heap->length; i++) {
    sorted[i] = *pop(copy);
  }

  free(copy);

  int *ptr = sorted;
  return ptr;
}

int main() {
  MaxHeap *h = newMaxHeap(10);

  assert(isEmpty(h));
  assert(length(h) == 0);
  assert(pop(h) == NULL);

  int maxValue = INT_MIN;
  for (int i = 0; i < 5; i++) {
    int value = rand() % 100;

    if (value > maxValue)
      maxValue = value;

    assert(push(h, value) == 0);
  }
  assert(length(h) == 5);
  assert(!isEmpty(h));
  assert(!isFull(h));
  for (int i = 0; i < 5; i++) {
    int value = rand() % 100;

    if (value > maxValue)
      maxValue = value;

    assert(push(h, value) == 0);
  }
  assert(length(h) == 10);
  assert(isFull(h));

  int *unsorted = print(h);
  assert(unsorted[0] == maxValue);
  // Test heap property
  for (int i = 1; i < 10; i++) {
    assert(unsorted[i] <= unsorted[(i - 1) / 2]);
  }

  int *sorted = sort(h);
  assert(sorted[0] == maxValue);
  // Test sorting
  for (int i = 1; i < 10; i++) {
    assert(sorted[i] <= sorted[i - 1]);
  }

  assert(push(h, 1) == 1);
  assert(*pop(h) == maxValue);
  assert(length(h) == 9);

  clear(h);
  assert(length(h) == 0);
  assert(isEmpty(h));
  assert(print(h) == NULL);
  assert(sort(h) == NULL);

  free(h);
  printf("All tests passed successfully.\n");

  return 0;
}