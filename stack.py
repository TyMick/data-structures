class Stack:
    """Implements a stack data structure with last-in-first-out functionality."""

    def __init__(self):
        self.collection = []

    def push(element):
        """Adds an element to the top of the stack."""
        self.collection.append(element)

    def peek():
        """Returns the element at the top of the stack, leaving it in place."""
        return self.collection[-1]

    def pop():
        """Removes and returns the element at the top of the stack."""
        return self.collection.pop()

    def print():
        """
        Prints the stack to the console as an array with elements ordered from from
        bottom to top.
        """
        print(self.collection)

    def isEmpty():
        """Returns whether or not the stack is currently empty."""
        return len(self.collection == 0)

    def clear():
        """Clears the contents of the stack."""
        self.collection = []
