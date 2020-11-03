#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/** A stack data structure, which will have last-in-first-out functionality. */
typedef struct Stack {
  int maxSize;
  int *array;
  int top;
} Stack;

Stack *newStack(int maxSize) {
  Stack *ptr = malloc(sizeof(Stack));

  ptr->maxSize = maxSize;
  ptr->array = malloc(maxSize * sizeof(int));
  ptr->top = -1;

  return ptr;
}

/** Returns the number of elements in a stack. */
int size(Stack *stack) { return stack->top + 1; }

/** Returns whether or not a stack is empty. */
bool isEmpty(Stack *stack) { return size(stack) == 0; }

/** Returns whether or not a stack is full. */
bool isFull(Stack *stack) { return size(stack) == stack->maxSize; }

/**
 * Adds an element to the top of a stack.
 *
 * @return `0` if the element was successfully added, `1` if the stack was
 *   already full.
 */
int push(Stack *stack, int element) {
  if (isFull(stack)) {
    printf("Push error: stack is already full.\n");
    return 1;
  }

  stack->array[++stack->top] = element;
  return 0;
}

/**
 * Returns the element at the top of a stack, leaving it in place.
 *
 * @return A pointer to the element, or `NULL` if the stack is empty.
 */
int *peek(Stack *stack) {
  if (isEmpty(stack)) {
    printf("Peek error: stack is empty.\n");
    return NULL;
  }

  return &stack->array[stack->top];
}

/**
 * Removes and returns the element at the top of a stack.
 *
 * @return A pointer to the element removed, or `NULL` if the stack was already
 *   empty.
 */
int *pop(Stack *stack) {
  if (isEmpty(stack)) {
    printf("Pop error: stack is already empty.\n");
    return NULL;
  }

  int popped = stack->array[stack->top--];

  int *ptr = &popped;
  return ptr;
}

/** Clears the contents of a stack. */
void clear(Stack *stack) { stack->top = -1; }

/** Frees the allocated memory for a stack and its internal array. */
void destroy(Stack *stack) {
  free(stack->array);
  free(stack);
}

/**
 * Prints a stack to the console as comma-separated values ordered from bottom
 * to top.
 */
void print(Stack *stack) {
  if (!isEmpty(stack)) {
    printf("%d", stack->array[0]);
    for (int i = 1; i <= stack->top; i++) {
      printf(", %d", stack->array[i]);
    }
  }
  printf("\n");
}

int main() {
  Stack *s = newStack(5);

  print(s);
  assert(isEmpty(s));

  assert(pop(s) == NULL);
  assert(peek(s) == NULL);

  assert(push(s, 2) == 0);
  assert(*peek(s) == 2);

  push(s, 4);
  push(s, 6);
  assert(size(s) == 3);
  assert(!isEmpty(s));
  assert(!isFull(s));

  assert(*pop(s) == 6);
  assert(size(s) == 2);

  push(s, 99);
  push(s, 47);
  pop(s);
  assert(*peek(s) == 99);

  push(s, 34);
  push(s, 83);
  assert(size(s) == 5);
  assert(isFull(s));

  assert(push(s, 9) == 1);

  print(s);

  clear(s);
  assert(isEmpty(s));

  printf("All tests passed successfully.\n");
  destroy(s);

  return 0;
}
