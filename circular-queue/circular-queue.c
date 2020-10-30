#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * A circlular queue: a first-in-first-out data structure with a fixed buffer
 * size.
 */
typedef struct CircularQueue {
  int size;
  int *array;
  int readPos; // Will be `-1` when the queue is empty
  int writePos;
} CircularQueue;

CircularQueue *newCircularQueue(int bufferSize) {
  CircularQueue *ptr = malloc(sizeof(CircularQueue));

  ptr->size = bufferSize;
  ptr->array = malloc(bufferSize * sizeof(int));
  ptr->readPos = -1;
  ptr->writePos = 0;

  return ptr;
}

/** Returns whether or not a circular queue is empty. */
bool isEmpty(CircularQueue *queue) { return queue->readPos == -1; }

/** Returns whether or not a circular queue is full. */
bool isFull(CircularQueue *queue) { return queue->readPos == queue->writePos; }

/**
 * Adds an element to a circular queue if the queue is not already full.
 *
 * @param queue A pointer to the circular queue.
 * @param element The element to add.
 * @return `0` if the element was successfully added, `1` if the circular queue
 *   was already full.
 */
int enqueue(CircularQueue *queue, int element) {
  if (isFull(queue)) {
    printf("Enqueue error: circular queue is already full.\n");
    return 1;
  }

  if (isEmpty(queue))
    queue->readPos = queue->writePos;

  queue->array[queue->writePos] = element;
  queue->writePos = (queue->writePos + 1) % queue->size;

  return 0;
}

/**
 * Removes an element from a circular queue if the queue is not already empty.
 *
 * @param queue A pointer to the circular queue.
 * @return A pointer to the element removed, or `NULL` if the circular queue was
 *   already empty.
 */
int *dequeue(CircularQueue *queue) {
  if (isEmpty(queue)) {
    printf("Dequeue error: circular queue is already empty.\n");
    return NULL;
  }

  int dequeued = queue->array[queue->readPos];

  queue->readPos = (queue->readPos + 1) % queue->size;
  if (queue->readPos == queue->writePos)
    queue->readPos = -1;

  int *ptr = &dequeued;
  return ptr;
}

/** Clears the contents of a circular queue. */
void clear(CircularQueue *queue) {
  queue->readPos = -1;
  queue->writePos = 0;
}

/**
 * Prints the contents of a circular queue to the console as comma-separated
 * values, in read order.
 */
void print(CircularQueue *queue) {
  if (!isEmpty(queue)) {
    printf("%d", queue->array[queue->readPos]);

    int i = queue->readPos + 1;
    while (i != queue->writePos) {
      printf(", %d", queue->array[i]);
      i = (i + 1) % queue->size;
    }
  }
  printf("\n");
}

int main() {
  CircularQueue *q = newCircularQueue(5);

  print(q);
  assert(isEmpty(q));
  assert(dequeue(q) == NULL);

  assert(enqueue(q, 2) == 0);
  enqueue(q, 34);
  assert(*dequeue(q) == 2);

  enqueue(q, 1);
  enqueue(q, 58);
  enqueue(q, 29);
  enqueue(q, 37);

  assert(isFull(q));
  assert(enqueue(q, 9) == 1);

  print(q);

  clear(q);
  assert(isEmpty(q));

  enqueue(q, 1);
  assert(*dequeue(q) == 1);

  printf("All tests passed successfully.\n");

  return 0;
}
