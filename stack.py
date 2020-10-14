class Stack:
    """A stack data structure, with last-in-first-out functionality."""

    def __init__(self):
        self.collection = []

    def push(self, element):
        """Add an element to the top of the stack."""
        self.collection.append(element)

    def peek(self):
        """Return the element at the top of the stack, leaving it in place."""
        return self.collection[-1]

    def pop(self):
        """Remove and return the element at the top of the stack."""
        return self.collection.pop()

    def size(self):
        """Return the number of elements in the stack."""
        return len(self.collection)

    def isEmpty(self):
        """Return whether or not the stack is currently empty."""
        return len(self.collection) == 0

    def clear(self):
        """Clear the contents of the stack."""
        self.collection = []

    def print(self):
        """
        Print the stack to the console as a list with elements ordered from from bottom
        to top.
        """
        print(self.collection)
