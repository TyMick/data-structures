/**
 * A binary max heap implemented as an implicit data structure. Keys are stored
 * as an array, and parent-child relationships are determined by relative
 * positions within the array: in a 1-indexed array, for an element at given
 * index `i`, its children will be located at `2i` and `2i + 1`, and its parent
 * will be located at `Math.floor(i / 2)`. All parent nodes are greater than or
 * equal to their child nodes.
 */
export class MaxHeap {
  heap: number[] = [null];

  /** Adds a value to the collection, maintaining the heap property. */
  insert(val: number): void {
    this.heap.push(val);

    const parentIndex = (index: number): number => Math.floor(index / 2);
    const parentValue = (index: number): number =>
      this.heap[parentIndex(index)];

    let i = this.heap.length - 1;
    while (parentIndex(i) > 0 && val > parentValue(i)) {
      // Switch with parent
      this.heap[i] = parentValue(i);
      this.heap[parentIndex(i)] = val;
      i = parentIndex(i);
    }
  }

  /**
   * Removes and returns the greatest value in the collection, then reorders it
   * to maintain the heap property.
   */
  remove(): number {
    if (this.heap.length === 1) return null;

    // Save return value
    const max = this.heap[1];

    if (this.heap.length === 2) {
      this.heap = [null];
      return max;
    }

    const child1Index = (index: number): number => 2 * index;
    const child2Index = (index: number): number => 2 * index + 1;
    const child1Value = (index: number): number =>
      this.heap[child1Index(index)];
    const child2Value = (index: number): number =>
      this.heap[child2Index(index)];

    // Rebalance the heap by moving the last element into the root position,
    // then continuing to swap it with its greatest-valued child until it is
    // greater than both children or it reaches the last level of the tree
    this.heap[1] = this.heap.pop();
    let val = this.heap[1];
    let i = 1;
    while (val < child1Value(i) || val < child2Value(i)) {
      if (child1Value(i) > child2Value(i) || child2Value(i) === undefined) {
        // Swap with child 1
        this.heap[i] = child1Value(i);
        this.heap[child1Index(i)] = val;
        i = child1Index(i);
      } else {
        // Swap with child 2
        this.heap[i] = child2Value(i);
        this.heap[child2Index(i)] = val;
        i = child2Index(i);
      }
    }

    return max;
  }

  /**
   * Returns an array of all values currently in the heap (in the order of the
   * internal data structure).
   */
  print(): number[] {
    return this.heap.slice(1);
  }

  /**
   * Returns an array of all values in the heap ordered from greatest to least.
   */
  sort(): number[] {
    let clone = [...this.heap];

    let sorted = [];
    while (this.heap.length > 1) {
      sorted.push(this.remove());
    }

    this.heap = clone;

    return sorted;
  }
}
