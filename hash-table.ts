/**
 * A hash table data structure. Hashes string keys deterministically to
 * numerical indices (using an admittedly naive hashing function) and stores
 * key-value pairs at those hashed indices to provide more efficient lookup
 * times. This implementation handles collisions by simply storing multiple key-
 * value pairs at the same hashed index as needed.
 */
class HashTable {
  collection: { [index: number]: { [key: string]: any } } = {};

  private hash(string: string): number {
    let hashed: number = 0;
    for (let i = 0; i < string.length; i++) {
      hashed += string.charCodeAt(i);
    }
    return hashed;
  }

  /** Add a key-value pair to the table. */
  add(key: string, value: any): void {
    const index = this.hash(key);
    if (this.collection[index] === undefined) {
      this.collection[index] = {};
    }
    this.collection[index][key] = value;
  }

  /** Given a key, remove its key-value pair from the table (if present). */
  remove(key: string): void {
    const index = this.hash(key);
    try {
      delete this.collection[index][key];
      if (Object.keys(this.collection[index]).length === 0) {
        delete this.collection[index];
      }
    } finally {
    }
  }

  /**
   * Return a given key's associated value (or `null` if the key is not present
   * in the table).
   */
  lookup(key: string): any {
    const index = this.hash(key);
    try {
      return this.collection[index][key];
    } catch {
      return null;
    }
  }

  /** Clear the contents of the table. */
  clear(): void {
    this.collection = {};
  }
}
