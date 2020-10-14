class CircularQueue:
    """
    Implements a circlular queue, a first-in-first-out data structure with a fixed
    buffer size.
    """

    def __init__(self, size):
        self.queue = []
        self.read_pos = 0
        self.write_pos = 0
        self.size = size
        self.queue = [None for i in range(size)]

    def enqueue(self, element):
        """
        Adds an element to the buffer if the buffer is not already full.

        Parameters
        ----------
        element :
            The element you wish to add.

        Returns
        -------
        The element itself if it was added, or `None` if the buffer was full.
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
        Removes an element from the buffer if the buffer is not already empty.

        Returns
        -------
        The element removed (or `None` if the buffer was empty).
        """

        if self.queue[self.read_pos] is None:
            # Buffer is empty
            return None
        else:
            item = self.queue[self.read_pos]
            self.queue[self.read_pos] = None
            self.read_pos = (self.read_pos + 1) % self.size
            return item

    def print(self):
        """
        Prints the queue to the console as an array, starting with the element that will
        be read next.
        """
        return self.queue[self.read_pos :] + self.queue[: self.read_pos]
