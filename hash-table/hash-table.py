class HashTable:
    """
    A hash table data structure. Hashes string keys deterministically to numerical
    indices (using an admittedly naive hashing function) and stores key-value pairs at
    those hashed indices to provide more efficient lookup times. This implementation
    handles collisions by simply storing multiple key-value pairs at the same hashed
    index as needed.
    """

    def __init__(self):
        self.collection = {}

    def _hash(self, string):
        hashed = 0
        for character in string:
            hashed += ord(character)
        return hashed

    def add(self, key, value):
        """
        Adds a key-value pair to the table. Assigning values via `table[key] = value` is
        identical to this method.
        """
        index = self._hash(key)
        self.collection.setdefault(index, {})[key] = value

    __setitem__ = add

    def remove(self, key):
        """
        Given a key, removes its key-value pair from the table (if present). Calling
        `del table[key]` is identical to this method.
        """
        index = self._hash(key)
        try:
            del self.collection[index][key]
            if len(self.collection[index]) == 0:
                del self.collection[index]
        finally:
            pass

    __delitem__ = remove

    def lookup(self, key):
        """
        Returns a given key's associated value (or `None` if the key is not present in
        the table). Calling `table[key]` is identical to this method.
        """
        index = self._hash(key)
        return self.collection.get(index, {}).get(key, None)

    __getitem__ = lookup

    def clear(self):
        """Clears the contents of the table."""
        self.collection = {}
