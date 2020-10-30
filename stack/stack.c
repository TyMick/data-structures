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

/** Constructor */
Stack *newStack(int maxSize) {
  Stack *pt = malloc(sizeof(Stack));

  pt->maxSize = maxSize;
  pt->array = malloc(maxSize * sizeof(int));
  pt->top = -1;

  return pt;
}

/** Return the number of elements in a stack. */
int size(Stack *stack) { return stack->top + 1; }

/** Return whether or not a stack is empty. */
bool isEmpty(Stack *stack) { return size(stack) == 0; }

/** Return whether or not a stack is full. */
bool isFull(Stack *stack) { return size(stack) == stack->maxSize; }

/** Add an element to the top of a stack. */
void push(Stack *stack, int element) {
  if (isFull(stack)) {
    printf("Error: stack is already full.\n");
    exit(EXIT_FAILURE);
  }

  stack->array[++stack->top] = element;
}

/** Return the element at the top of a stack, leaving it in place. */
int peek(Stack *stack) {
  if (isEmpty(stack)) {
    printf("Error: stack is empty.\n");
    exit(EXIT_FAILURE);
  }

  return stack->array[stack->top];
}

/** Remove and return the element at the top of a stack. */
int pop(Stack *stack) {
  if (isEmpty(stack)) {
    printf("Error: stack is already empty.\n");
    exit(EXIT_FAILURE);
  }

  return stack->array[stack->top--];
}

/** Clear the contents of a stack. */
void clear(Stack *stack) { stack->top = -1; }

/**
 * Print the stack to the console as comma-separated values ordered from bottom
 * to top.
 */
void print(Stack *stack) {
  if (!isEmpty(stack)) {
    printf("%d", stack->array[0]);
    for (int i = 1; i <= stack->top; i++) {
      printf(", %d", stack->array[i]);
    }
    printf("\n");
  }
}

int main() {
  Stack *s = newStack(5);

  assert(isEmpty(s));

  push(s, 2);
  push(s, 4);
  push(s, 6);
  assert(size(s) == 3);
  assert(!isEmpty(s));
  assert(!isFull(s));

  assert(pop(s) == 6);
  assert(size(s) == 2);

  push(s, 99);
  assert(peek(s) == 99);

  push(s, 34);
  push(s, 83);
  assert(size(s) == 5);
  assert(isFull(s));

  print(s);

  clear(s);
  assert(isEmpty(s));

  printf("All tests passed successfully.\n");

  return 0;
}