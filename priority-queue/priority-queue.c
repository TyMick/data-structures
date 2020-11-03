#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct QueueItem {
  char *element;
  int priority;
} QueueItem;

/**
 * A priority queue data structure, in which items will specify their priority.
 * Items will be ordered first in descending order of priority, then in
 * descending order of length of time in the queue.
 */
typedef struct PriorityQueue {
  int maxSize;
  QueueItem *array;
  int end;
} PriorityQueue;

PriorityQueue *newPriorityQueue(int maxSize) {
  PriorityQueue *ptr = malloc(sizeof(PriorityQueue));

  ptr->maxSize = maxSize;
  ptr->array = malloc(maxSize * sizeof(QueueItem));
  ptr->end = -1;

  return ptr;
}

/** Returns the number of elements in a priority queue. */
int size(PriorityQueue *queue) { return queue->end + 1; }

/** Returns whether or not a priority queue is empty. */
bool isEmpty(PriorityQueue *queue) { return size(queue) == 0; }

/** Returns whether or not a priority queue is full. */
bool isFull(PriorityQueue *queue) { return size(queue) == queue->maxSize; }

/**
 * Adds an element to the end of a priority queue, then moves it in front of any
 * lower-priority items.
 *
 * @param queue A pointer to the priority queue.
 * @param element The element to be added.
 * @return `0` if the element was successfully added, `1` if the queue was
 *   already full.
 */
int enqueue(PriorityQueue *queue, char *element, int priority) {
  if (isFull(queue)) {
    printf("Enqueue error: priority queue is already full.\n");
    return 1;
  }

  // Move elements toward the end until the correct insert index is found
  int insertIndex = size(queue);
  while (insertIndex > 0 && queue->array[insertIndex - 1].priority < priority) {
    queue->array[insertIndex] = queue->array[insertIndex - 1];
    insertIndex--;
  }

  queue->array[insertIndex] = (QueueItem){element, priority};
  queue->end++;

  return 0;
}

/**
 * Returns the element at the front of a priority queue, leaving it in place.
 *
 * @param queue A pointer to the priority queue.
 * @return The element at the front of the queue, or `NULL` if the queue is
 *   empty.
 */
char *front(PriorityQueue *queue) {
  if (isEmpty(queue)) {
    printf("Front error: priority queue is empty.\n");
    return NULL;
  }

  return queue->array[0].element;
}

/**
 * Removes and returns the element at the front of a priority queue.
 *
 * @param queue A pointer to the priority queue.
 * @return The element removed, or `NULL` if the queue was already empty.
 */
char *dequeue(PriorityQueue *queue) {
  if (isEmpty(queue)) {
    printf("Dequeue error: priority queue is already empty.\n");
    return NULL;
  }

  char *dequeued = queue->array[0].element;

  for (int i = 0; i < queue->end; i++) {
    queue->array[i] = queue->array[i + 1];
  }

  queue->end--;

  return dequeued;
}

/** Clears the contents of a priority queue. */
void clear(PriorityQueue *queue) { queue->end = -1; }

/** Frees the allocated memory for a priority queue and its internal array. */
void destroy(PriorityQueue *queue) {
  free(queue->array);
  free(queue);
}

/**
 * Prints a priority queue to the console as comma-separated [element, priority]
 * tuples, ordered from front to end.
 */
void print(PriorityQueue *queue) {
  if (!isEmpty(queue)) {
    printf("[\"%s\", %d]", queue->array[0].element, queue->array[0].priority);
    for (int i = 1; i <= queue->end; i++) {
      printf(", [\"%s\", %d]", queue->array[i].element,
             queue->array[i].priority);
    }
  }
  printf("\n");
}

int main() {
  PriorityQueue *q = newPriorityQueue(5);

  print(q);
  assert(isEmpty(q));
  assert(dequeue(q) == NULL);
  assert(front(q) == NULL);

  assert(enqueue(q, "this", 9) == 0);
  enqueue(q, "air", 3);
  enqueue(q, "elephant", 12);
  print(q);
  assert(strcmp(front(q), "elephant") == 0);
  assert(size(q) == 3);
  assert(!isFull(q));
  assert(!isEmpty(q));

  enqueue(q, "forge", 4);
  enqueue(q, "elbow", 90);
  assert(isFull(q));
  assert(enqueue(q, "not gonna happen", 0) == 1);

  print(q);
  clear(q);
  assert(isEmpty(q));
  assert(front(q) == NULL);

  printf("All tests passed successfully.\n");
  destroy(q);

  return 0;
}
