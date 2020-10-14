/** A set data structure, unordered with no duplicate values. */
class Set {
  dictionary = {};
  length = 0;

  /**
   * Add a value to the set (if it is not already present).
   * @param {string} value - The value you wish to add.
   * @returns `true` if the value was successfully added, `false` if the value
   * was already present in the set.
   */
  add(value: string): boolean {
    if (this.has(value)) {
      return false;
    } else {
      this.dictionary[value] = true;
      this.length++;
      return true;
    }
  }

  /**
   * Remove a value from a set (if present).
   * @param {string} value - The value you wish to remove.
   * @returns `true` if the value was successfully removed, `false` if the value
   * was not present in the set.
   */
  remove(value: string): boolean {
    if (this.has(value)) {
      delete this.dictionary[value];
      this.length--;
      return true;
    } else {
      return false;
    }
  }

  /** Check for the presence of a value. */
  has(value: string): boolean {
    return this.dictionary[value] !== undefined;
  }

  /** Return all values in the set as an array. */
  values(): string[] {
    return Object.keys(this.dictionary);
  }

  /** Return the number of (unique) values in the set. */
  size(): number {
    return this.length;
  }

  /** Clear the contents of the set. */
  clear(): void {
    this.dictionary = {};
    this.length = 0;
  }

  /**
   * Return the union of this set and the set passed to this function; that is,
   * the set of all values present in at least one of the two sets.
   */
  union(otherSet: Set): Set {
    const union = new Set();

    // Add values from this set
    for (const value of this.values()) {
      union.add(value);
    }
    // Add values from passed set
    for (const value of otherSet.values()) {
      union.add(value);
    }

    return union;
  }

  /**
   * Return the intersection of this set and the set passed to this function;
   * that is, the set of all values present in both of the two sets.
   */
  intersection(otherSet: Set): Set {
    const intersection = new Set();

    let smallerSet: Set, largerSet: Set;
    if (this.length <= otherSet.size()) {
      smallerSet = this;
      largerSet = otherSet;
    } else {
      smallerSet = otherSet;
      largerSet = this;
    }

    for (const value of smallerSet.values()) {
      if (largerSet.has(value)) {
        intersection.add(value);
      }
    }

    return intersection;
  }

  /**
   * Return the difference of this set from the set passed to this function;
   * that is, the set of all values present in this set but not in the passed
   * set.
   */
  difference(otherSet: Set): Set {
    const difference = new Set();
    for (const value of this.values()) {
      if (!otherSet.has(value)) {
        difference.add(value);
      }
    }
    return difference;
  }

  /**
   * Return whether or not this set is a subset of the set passed to this
   * function; that is, whether or not all values in this set are also in the
   * passed set.
   */
  isSubset(otherSet: Set): boolean {
    let isSubset: boolean = true;
    for (const value of this.values()) {
      if (!otherSet.has(value)) {
        isSubset = false;
        break;
      }
    }
    return isSubset;
  }
}
