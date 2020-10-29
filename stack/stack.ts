/** A stack data structure, with last-in-first-out functionality. */
export default class Stack {
  collection: any[] = [];

  /** Add an element to the top of the stack. */
  push(element: any): void {
    this.collection.push(element);
  }

  /** Return the element at the top of the stack, leaving it in place. */
  peek(): any {
    return this.collection[this.collection.length - 1];
  }

  /** Remove and return the element at the top of the stack. */
  pop(): any {
    return this.collection.pop();
  }

  /** Return the number of elements in the stack. */
  size(): number {
    return this.collection.length;
  }

  /** Return whether or not the stack is currently empty. */
  isEmpty(): boolean {
    return this.collection.length === 0;
  }

  /** Clear the contents of the stack. */
  clear(): void {
    this.collection = [];
  }

  /**
   * Print the stack to the console as an array with elements ordered from
   * bottom to top.
   */
  print(): void {
    console.log(this.collection);
  }
}
