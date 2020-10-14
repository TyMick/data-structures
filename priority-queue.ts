/**
 * A priority queue data structure, in which items may specify their priority.
 * Items will be ordered first in descending order of priority, then in
 * descending order of length of time in the queue.
 */
class PriorityQueue {
  collection: Array<[any, number]> = [];

  /**
   * Add an element to the end of the queue, then move it in front of any lower-
   * priority items.
   * @param element - The element you wish to add.
   * @param {number} [priority=0] - The priority you wish to give this element
   * in the queue. Greater numbers indicate higher priority.
   */
  enqueue(element: any, priority: number = 0): void {
    let insertIndex = this.collection.length;
    while (insertIndex > 0 && this.collection[insertIndex - 1][1] < priority) {
      insertIndex--;
    }

    this.collection.splice(insertIndex, 0, [element, priority]);
  }

  /** Return the element at the front of the queue, leaving it in place. */
  front(): any {
    return this.collection[0][0];
  }

  /** Remove and return the element at the front of the queue. */
  dequeue(): any {
    return this.collection.shift()[0];
  }

  /** Return the number of elements in the queue. */
  size(): number {
    return this.collection.length;
  }

  /** Return whether or not the queue is currently empty. */
  isEmpty(): boolean {
    return this.collection.length === 0;
  }

  /** Clear the contents of the queue. */
  clear(): void {
    this.collection = [];
  }

  /**
   * Print the priority queue to the console as an array of [element, priority]
   * tuples, ordered from front to end.
   */
  print(): void {
    console.log(JSON.stringify(this.collection));
  }
}
