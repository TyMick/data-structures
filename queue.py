class Queue:
    """Implements a queue data structure with first-in-first-out functionality."""
    
    def __init__(self):
        self.collection = []

    def enqueue(self, element):
        """Adds an element to the end of the queue."""
        self.collection.append(element)

    def front(self):
        """Returns the element at the front of the queue, leaving it in place."""
        return self.collection[0]

    def dequeue(self):
        """Removes and returns the element at the front of the queue."""
        return self.collection.pop(0)

    def size(self):
        """Returns the number of elements in the queue."""
        return len(self.collection)

    def isEmpty(self):
        """Returns whether or not the queue is currently empty."""
        return len(self.collection) == 0

    def clear(self):
        """Clears the contents of the queue."""
        self.collection = []

    def print(self):
        """
        Prints the queue to the console as an array with elements ordered from front to
        end.
        """
        print(self.collection)
