#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/** A queue data structure, which will have first-in-first-out functionality. */
typedef struct Queue {
  int maxSize;
  int *array;
  int end;
} Queue;

Queue *newQueue(int maxSize) {
  Queue *ptr = malloc(sizeof(Queue));

  ptr->maxSize = maxSize;
  ptr->array = malloc(maxSize * sizeof(int));
  ptr->end = -1;

  return ptr;
}

/** Returns the number of elements in a queue. */
int size(Queue *queue) { return queue->end + 1; }

/** Returns whether or not a queue is empty. */
bool isEmpty(Queue *queue) { return size(queue) == 0; }

/** Returns whether or not a queue is full. */
bool isFull(Queue *queue) { return size(queue) == queue->maxSize; }

/**
 * Adds an element to the end of a queue.
 *
 * @param queue A pointer to the queue.
 * @param element The element to be added.
 * @return `0` if the element was successfully added, `1` if the queue was
 *   already full.
 */
int enqueue(Queue *queue, int element) {
  if (isFull(queue)) {
    printf("Enqueue error: queue is already full.\n");
    return 1;
  }

  queue->array[++queue->end] = element;
  return 0;
}

/**
 * Returns the element at the front of a queue, leaving it in place.
 *
 * @param queue A pointer to the queue.
 * @return A pointer to the element, or `NULL` if the queue is empty.
 */
int *front(Queue *queue) {
  if (isEmpty(queue)) {
    printf("Front error: queue is empty.\n");
    return NULL;
  }

  return &queue->array[0];
}

/**
 * Removes and returns the element at the front of a queue.
 *
 * @param queue A pointer to the queue.
 * @return A pointer to the element removed, or `NULL` if the queue was already
 *   empty.
 */
int *dequeue(Queue *queue) {
  if (isEmpty(queue)) {
    printf("Dequeue error: queue is already empty.\n");
    return NULL;
  }

  int dequeued = queue->array[0];

  for (int i = 0; i < queue->end; i++) {
    queue->array[i] = queue->array[i + 1];
  }

  queue->end--;

  int *ptr = &dequeued;
  return ptr;
}

/** Clears the contents of a queue. */
void clear(Queue *queue) { queue->end = -1; }

/**
 * Prints a queue to the console as comma-separated values ordered from front to
 * end.
 */
void print(Queue *queue) {
  if (!isEmpty(queue)) {
    printf("%d", queue->array[0]);
    for (int i = 1; i <= queue->end; i++) {
      printf(", %d", queue->array[i]);
    }
  }
  printf("\n");
}

int main() {
  Queue *q = newQueue(5);

  print(q);
  assert(isEmpty(q));

  assert(dequeue(q) == NULL);
  assert(front(q) == NULL);

  assert(enqueue(q, 2) == 0);
  enqueue(q, 34);
  assert(*dequeue(q) == 2);
  assert(size(q) == 1);

  enqueue(q, 1);
  enqueue(q, 58);
  enqueue(q, 29);
  enqueue(q, 37);

  assert(isFull(q));
  assert(*front(q) == 34);
  assert(enqueue(q, 9) == 1);

  print(q);

  clear(q);
  assert(isEmpty(q));

  printf("All tests passed successfully.\n");
  free(q);

  return 0;
}