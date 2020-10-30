class Node:
    def __init__(self, data, prev):
        self.data = data
        self.prev = prev
        self.next = None


class DoublyLinkedList:
    """
    A doubly-linked list data structure, where each node in the list contains references
    for both the node before it and the node after it.
    """

    def __init__(self):
        self.head = None
        self.tail = None

    def add(self, element):
        """Adds an element to the tail end of the list."""
        if self.tail:
            self.tail.next = Node(element, prev=self.tail)
            self.tail = self.tail.next
        else:
            self.head = Node(element, prev=None)
            self.tail = self.head

    def remove(self, element):
        """Removes all ocurrences of the given element from the list."""
        if self.head:
            # Remove as many heads as necessary
            while self.head.data == element:
                self.head = self.head.next
                self.head.prev = None

            # Remove as many tails as necessary
            while self.tail.data == element:
                self.tail = self.tail.prev
                self.tail.next = None

            # Iterate through rest of list
            current_node = self.head.next
            while current_node.next:
                if current_node.data == element:
                    # Link adjacent nodes
                    current_node.prev.next = current_node.next
                    current_node.next.prev = current_node.prev
                current_node = current_node.next

        else:
            return None

    def clear(self):
        """Clears the contents of the list."""
        self.head = self.tail = None

    def reverse(self):
        """Reverses the list in place (or returns `None` if the list is empty)."""
        if self.head:
            self.head = self.tail
            current_node = self.head
            while current_node.prev:
                # Swap adjacent nodes
                old_prev = current_node.prev
                current_node.prev = current_node.next
                current_node.next = old_prev

                current_node = current_node.next

            # Set new tail
            self.tail = current_node
            self.tail.prev = self.tail.next
            self.tail.next = None

        else:
            return None
