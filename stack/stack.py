class Stack:
    """A stack data structure, with last-in-first-out functionality."""

    def __init__(self):
        self.collection = []

    def push(self, element):
        """Adds an element to the top of the stack."""
        self.collection.append(element)

    def peek(self):
        """Returns the element at the top of the stack, leaving it in place."""
        return self.collection[-1]

    def pop(self):
        """Removes and returns the element at the top of the stack."""
        return self.collection.pop()

    def size(self):
        """
        Returns the number of elements in the stack. Calling `len(stack)` is identical
        to this method.
        """
        return len(self.collection)

    __len__ = size

    def is_empty(self):
        """Returns whether or not the stack is currently empty."""
        return len(self.collection) == 0

    def clear(self):
        """Clears the contents of the stack."""
        self.collection = []

    def print(self):
        """
        Prints the stack to the console as a list with elements ordered from from bottom
        to top.
        """
        print(self.collection)
