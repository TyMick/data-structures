class Node {
  data: any;
  prev: Node;
  next: Node = null;

  constructor(data: any, prev: Node) {
    this.data = data;
    this.prev = prev;
  }
}

/**
 * A doubly-linked list data structure, where each node in the list contains
 * references for both the node before it and the node after it.
 */
class DoublyLinkedList {
  head: Node = null;
  tail: Node = null;

  /** Add an element to the tail end of the list. */
  add(element: any): void {
    if (this.tail) {
      this.tail.next = new Node(element, this.tail);
      this.tail = this.tail.next;
    } else {
      this.head = new Node(element, null);
      this.tail = this.head;
    }
  }

  /** Remove all ocurrences of the given element from the list. */
  remove(element: any) {
    if (this.head) {
      // Remove as many heads as necessary
      while (this.head.data === element) {
        this.head = this.head.next;
        this.head.prev = null;
      }

      // Remove as many tails as necessary
      while (this.tail.data === element) {
        this.tail = this.tail.prev;
        this.tail.next = null;
      }

      // Iterate through rest of list
      let currentNode = this.head.next;
      while (currentNode.next) {
        if (currentNode.data === element) {
          // Link adjacent nodes
          currentNode.prev.next = currentNode.next;
          currentNode.next.prev = currentNode.prev;
        }
        currentNode = currentNode.next;
      }
    } else {
      return null;
    }
  }

  /** Clear the contents of the list. */
  clear(): void {
    this.head = null;
    this.tail = null;
  }

  /** Reverse the list in place (or return `null` if the list is empty). */
  reverse(): void | null {
    if (this.head) {
      this.head = this.tail;
      let currentNode = this.head;
      while (currentNode.prev) {
        // Swap adjacent nodes
        const oldPrev = currentNode.prev;
        currentNode.prev = currentNode.next;
        currentNode.next = oldPrev;

        currentNode = currentNode.next;
      }

      // Set new tail
      this.tail = currentNode;
      this.tail.prev = this.tail.next;
      this.tail.next = null;
    } else {
      return null;
    }
  }
}
