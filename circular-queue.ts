/**
 * A circlular queue: a first-in-first-out data structure with a fixed buffer
 * size.
 */
class CircularQueue {
  queue: any[] = [];
  readPos: number = 0;
  writePos: number = 0;
  size: number;

  constructor(size: number) {
    const isInteger = (number: number) =>
      number === parseInt(number.toString(), 10);
    if (!isInteger(size) || size <= 0) {
      throw new RangeError("Queue size must be a postive integer.");
    }

    this.size = size;
    for (let i = 0; i < size; i++) {
      this.queue.push(null);
    }
  }

  /**
   * Add an element to the buffer if the buffer is not already full.
   * @param element - The element you wish to add.
   * @returns The element itself if it was added, or `null` if the buffer was
   * full.
   */
  enqueue(element: any): any {
    if (this.queue[this.writePos] === null) {
      this.queue[this.writePos] = element;
      this.writePos = (this.writePos + 1) % this.size;
      return element;
    } else {
      // Buffer is full
      return null;
    }
  }

  /**
   * Remove an element from the buffer if the buffer is not already empty.
   * @returns The element removed (or `null` if the buffer was empty).
   */
  dequeue(): any {
    if (this.queue[this.readPos] === null) {
      // Buffer is empty
      return null;
    } else {
      const element = this.queue[this.readPos];
      this.queue[this.readPos] = null;
      this.readPos = (this.readPos + 1) % this.size;
      return element;
    }
  }

  /** Clear the contents of the queue. */
  clear(): void {
    for (let i = 0; i < this.size; i++) {
      this.queue[i] = null;
    }
    this.readPos = 0;
    this.writePos = 0;
  }

  /**
   * Print the queue to the console as an array, starting with the element that
   * will be read next.
   */
  print(): any[] {
    return [
      ...this.queue.slice(this.readPos),
      ...this.queue.slice(0, this.readPos),
    ];
  }
}
