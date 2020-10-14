/** A queue data structure, with first-in-first-out functionality. */
class Queue {
  collection: any[] = [];

  /** Add an element to the end of the queue. */
  enqueue(element: any): void {
    this.collection.push(element);
  }

  /** Return the element at the front of the queue, leaving it in place. */
  front(): any {
    return this.collection[0];
  }

  /** Remove and return the element at the front of the queue. */
  dequeue(): any {
    return this.collection.shift();
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
   * Print the queue to the console as an array with elements ordered from front
   * to end.
   */
  print(): void {
    console.log(this.collection);
  }
}
