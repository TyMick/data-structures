class Queue:
    """Implements a queue data structure with first-in-first-out functionality."""
    
    __init__(self):
        self.collection = []

    def enqueue(element):
        """Adds an element to the end of the queue."""
        self.collection.append(element)

    def front():
        """Returns the element at the front of the queue, leaving it in place."""
        return self.collection[0]

    def dequeue():
        """Removes and returns the element at the front of the queue."""
        return self.collection.pop(0)

    def size():
        """Returns the number of elements in the queue."""
        return len(self.collection)

    def isEmpty():
        """Returns whether or not the queue is currently empty."""
        return len(self.collection) == 0

    def clear():
        """Clears the contents of the queue."""
        self.collection = []

    def print():
        """
        Prints the queue to the console as an array with elements ordered from front to
        end.
        """
        print(self.collection)
