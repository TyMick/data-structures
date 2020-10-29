class CircularQueue:
    """
    A circlular queue: a first-in-first-out data structure with a fixed buffer size.
    """

    def __init__(self, size):
        if type(size) is not int:
            raise TypeError("Queue size must be a postive integer.")
        if size <= 0:
            raise ValueError("Queue size must be a postive integer.")

        self.queue = []
        self.read_pos = 0
        self.write_pos = 0
        self.size = size
        self.queue = [None for i in range(size)]

    def enqueue(self, element):
        """
        Add an element to the buffer if the buffer is not already full.

        :param element: The element you wish to add.
        :returns: The element itself if it was added, or `None` if the buffer was full.
        """

        if self.queue[self.write_pos] is None:
            self.queue[self.write_pos] = element
            self.write_pos = (self.write_pos + 1) % self.size
            return element
        else:
            # Buffer is full
            return None

    def dequeue(self):
        """
        Remove an element from the buffer if the buffer is not already empty.

        :returns: The element removed (or `None` if the buffer was empty).
        """

        if self.queue[self.read_pos] is None:
            # Buffer is empty
            return None
        else:
            item = self.queue[self.read_pos]
            self.queue[self.read_pos] = None
            self.read_pos = (self.read_pos + 1) % self.size
            return item

    def clear(self):
        """Clear the contents of the queue."""
        self.queue = [None for i in range(self.size)]
        self.read_pos = self.write_pos = 0

    def print(self):
        """
        Print the queue to the console as a list, starting with the element that will be
        read next.
        """
        return self.queue[self.read_pos :] + self.queue[: self.read_pos]
