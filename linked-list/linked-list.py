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
        """Adds a new element to the end of the list."""
        if self.head:
            current_node = self.head
            while current_node.next:
                current_node = current_node.next
            current_node.next = Node(element)
        else:
            self.head = Node(element)
        self.length += 1

    def remove(self, element):
        """
        Removes the first occurrence of a given element from the list (if possible).
        """
        if self.head:
            if self.head.element == element:
                self.head = self.head.next
                self.length -= 1
            else:
                # Search for element
                current_node = self.head.next
                previous_node = self.head
                while current_node:
                    if current_node.element == element:
                        # Link adjacent nodes to each other
                        previous_node.next = current_node.next
                        self.length -= 1
                        break
                    previous_node = current_node
                    current_node = current_node.next

    def size(self):
        """
        Returns the current number of elements in the list. Calling `len(linked_list)`
        is identical to this method.
        """
        return self.length

    __len__ = size

    def is_empty(self):
        """Returns whether or not the list is empty."""
        return self.length == 0

    def clear(self):
        """Clears the contents of the list."""
        self.head = None
        self.length = 0

    def index_of(self, element):
        """
        Returns the numerical index of the first occurrence of the given element in the
        list (or `-1` if the list does not contain this element).
        """
        index = 0
        current_node = self.head
        while current_node:
            if current_node.element == element:
                return index
            current_node = current_node.next
            index += 1
        return -1

    def element_at(self, index):
        """
        Returns the element at the given index in the list (or `None` if the list has no
        such index). Calling `linked_list[index]` is identical to this method.
        """
        if index < 0 or index >= self.length:
            return None
        else:
            current_node = self.head
            for _ in range(index):
                current_node = current_node.next
            return current_node.element

    __getitem__ = element_at

    def remove_at(self, index):
        """
        Removes and returns the element at the given index from the list (or returns
        `None` if the list has no such index). Calling `del linked_list[index]` is
        identical to this method.
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
            current_index = 1
            previous_node = self.head
            current_node = self.head.next
            while current_index < index:
                previous_node = current_node
                current_node = current_node.next
                current_index += 1

            # Link adjacent nodes to each other
            previous_node.next = current_node.next

            self.length -= 1
            return current_node.element

    __delitem__ = remove_at

    def add_at(self, index, element):
        """
        Inserts a given element at a given index in the list (or returns `False` if
        given an invalid index).
        """

        if index < 0 or index > self.length:
            return False
        elif index == 0:
            new_node = Node(element)
            new_node.next = self.head
            self.head = new_node
            self.length += 1
        else:
            # Find nodes at and around index
            current_index = 1
            current_node = self.head.next
            previous_node = self.head
            while current_index < index:
                previous_node = current_node
                current_node = current_node.next
                current_index += 1

            # Adds and link up
            new_node = Node(element)
            new_node.next = current_node
            previous_node.next = new_node

            self.length += 1
