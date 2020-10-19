class Queue:
    """A queue data structure, with first-in-first-out functionality."""

    def __init__(self):
        self.collection = []

    def enqueue(self, element):
        """Add an element to the end of the queue."""
        self.collection.append(element)

    def front(self):
        """Return the element at the front of the queue, leaving it in place."""
        return self.collection[0]

    def dequeue(self):
        """Remove and return the element at the front of the queue."""
        return self.collection.pop(0)

    def size(self):
        """
        Return the number of elements in the queue. Calling `len(queue)` is identical to
        this method.
        """
        return len(self.collection)

    __len__ = size

    def is_empty(self):
        """Return whether or not the queue is currently empty."""
        return len(self.collection) == 0

    def clear(self):
        """Clear the contents of the queue."""
        self.collection = []

    def print(self):
        """
        Print the queue to the console as a list with elements ordered from front to
        end.
        """
        print(self.collection)
