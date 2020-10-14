class Node:
    def __init__(self, element):
        self.element = element
        self.next = None


class LinkedList:
    """
    A linked list data structure, where each node in the list contains a reference to
    the node after it.
    """

    def __init__(self):
        self.length = 0
        self.head = None

    def add(self, element):
        """Add a new element to the end of the list."""
        if self.head:
            currentNode = self.head
            while currentNode.next:
                currentNode = currentNode.next
            currentNode.next = Node(element)
        else:
            self.head = Node(element)
        self.length += 1

    def remove(self, element):
        """
        Remove the first occurrence of a given element from the list (if possible).
        """
        if self.head:
            if self.head.element == element:
                self.head = self.head.next
                self.length -= 1
            else:
                # Search for element
                currentNode = self.head.next
                previousNode = self.head
                while currentNode:
                    if currentNode.element == element:
                        # Link adjacent nodes to each other
                        previousNode.next = currentNode.next
                        self.length -= 1
                        break
                    currentNode = currentNode.next

    def size(self):
        """Return the current number of elements in the list."""
        return self.length

    def is_empty(self):
        """Return whether or not the list is empty."""
        return self.length == 0

    def clear(self):
        """Clear the contents of the list."""
        self.head = None
        self.length = 0

    def index_of(self, element):
        """
        Return the numerical index of the first occurrence of the given element in the
        list (or `-1` if the list does not contain this element).
        """
        index = 0
        currentNode = self.head
        while currentNode:
            if currentNode.element == element:
                return index
            currentNode = currentNode.next
            index += 1
        return -1

    def element_at(self, index):
        """
        Return the element at the given index in the list (or `None` if the list has no
        such index).
        """
        if index < 0 or index >= self.length:
            return None
        else:
            currentNode = self.head
            for _ in range(index):
                currentNode = currentNode.next
            return currentNode.element

    def remove_at(self, index):
        """
        Remove and return the element at the given index from the list (or return `None`
        if the list has no such index).
        """

        if index < 0 or index >= self.length:
            return None
        elif index == 0:
            removed = self.head.element
            self.head = self.head.next
            self.length -= 1
            return removed
        else:
            # Find nodes at and around index
            currentIndex = 1
            previousNode = self.head
            currentNode = self.head.next
            while currentIndex < index:
                previousNode = currentNode
                currentNode = currentNode.next
                currentIndex += 1

            # Link adjacent nodes to each other
            previousNode.next = currentNode.next

            self.length -= 1
            return currentNode.element

    def add_at(self, index, element):
        """
        Insert a given element at a given index in the list (or return `False` if given
        an invalid index).
        """

        if index < 0 or index > self.length:
            return False
        elif index == 0:
            newNode = Node(element)
            newNode.next = self.head
            self.head = newNode
            self.length += 1
        else:
            # Find nodes at and around index
            currentIndex = 1
            currentNode = self.head.next
            previousNode = self.head
            while currentIndex < index:
                previousNode = currentNode
                currentNode = currentNode.next
                currentIndex += 1

            # Add and link up
            newNode = Node(element)
            newNode.next = currentNode
            previousNode.next = newNode

            self.length += 1
