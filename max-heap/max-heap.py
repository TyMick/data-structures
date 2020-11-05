from math import floor


class MaxHeap:
    """
    A binary max heap implemented as an implicit data structure. Keys are stored as a
    list, and parent-child relationships are determined by relative positions within the
    array: in a 1-indexed array, for an element at given index `i`, its children will be
    located at `2 * i` and `2 * i + 1`, and its parent will be located at `math.floor(i
    / 2)`. All parent nodes are greater than or equal to their child nodes.
    """

    def __init__(self):
        self.heap = [None]

    def insert(self, val):
        """Adds a value to the collection, maintaining the heap property."""

        self.heap.append(val)

        parent_index = lambda index: floor(index / 2)
        parent_value = lambda index: self.heap[parent_index(index)]

        i = len(self.heap) - 1
        while parent_index(i) > 0 and val > parent_value(i):
            # Switch with parent
            self.heap[i] = parent_value(i)
            self.heap[parent_index(i)] = val
            i = parent_index(i)

    def remove(self):
        """
        Removes and returns the greatest value in the collection, then reorders it to
        maintain the heap property.
        """

        if len(self.heap) == 1: return None

        # Save return value
        max_val = self.heap[1]

        if len(self.heap) == 2:
            self.heap = [None]
            return max_val

        child_1_index = lambda index: 2 * index
        child_2_index = lambda index: 2 * index + 1

        def child_1_value(index):
            try:
                return self.heap[child_1_index(index)]
            except:
                return None

        def child_2_value(index):
            try:
                return self.heap[child_2_index(index)]
            except:
                return None

        # Rebalance the heap by moving the last element into the root position, then
        # continuing to swap it with its greatest-valued child until it is greater than
        # both children or it reaches the last level of the tree
        self.heap[1] = self.heap.pop()
        val = self.heap[1]
        i = 1
        while (child_1_value(i) is not None and val < child_1_value(i)) or (
            child_2_value(i) is not None and val < child_2_value(i)
        ):
            if child_2_value(i) is None or child_1_value(i) > child_2_value(i):
                # Swap with child 1
                self.heap[i] = child_1_value(i)
                self.heap[child_1_index(i)] = val
                i = child_1_index(i)

            else:
                # Swap with child 2
                self.heap[i] = child_2_value(i)
                self.heap[child_2_index(i)] = val
                i = child_2_index(i)

        return max_val

    def print(self):
        """
        Returns a list of all values currently in the heap (in the order of the internal
        data structure).
        """
        return self.heap[1:]

    def sort(self):
        """Returns a list of all values in the heap ordered from greatest to least."""

        clone = self.heap.copy()

        sorted = []
        while len(self.heap) > 1:
            sorted.append(self.remove())

        self.heap = clone
        return sorted
