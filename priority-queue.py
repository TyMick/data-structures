class PriorityQueue:
    """
    A priority queue data structure, in which items may specify their priority. Items
    will be ordered first in descending order of priority, then in descending order of
    length of time in the queue.
    """

    def __init__(self):
        self.collection = []

    def enqueue(self, element, priority=0):
        """
        Add an element to the end of the queue, then move it in front of any lower-
        priority items.

        :param element: The element you wish to add.
        :param int priority: The priority you wish to give this element in the queue
            (default 0). Greater numbers indicate higher priority.
        """

        insert_index = len(self.collection)
        while insert_index > 0 and self.collection[insert_index - 1][1] < priority:
            insert_index -= 1

        self.collection.insert(insert_index, (element, priority))

    def front(self):
        """Return the element at the front of the queue, leaving it in place."""
        return self.collection[0][0]

    def dequeue(self):
        """Remove and return the element at the front of the queue."""
        return self.collection.pop(0)[0]

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
        Print the priority queue to the console as a list of (element, priority) tuples,
        ordered from front to end.
        """
        print(self.collection)
