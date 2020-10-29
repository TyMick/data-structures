class Node {
  keys: { [key: string]: Node } = {};
  end = false;
}

/**
 * A trie search tree that stores words in an ordered tree structure in which
 * each node represents an individual letter.
 */
export class Trie {
  root = new Node();

  /** Add a new word to the trie. */
  add(word: string): void {
    if (!word.match(/^[A-Za-z]+$/)) {
      throw new TypeError(
        "Argument must be a single word with no special characters."
      );
    }

    (function addFrom(node: Node, remainingLtrs: string): void {
      if (remainingLtrs) {
        if (node.keys[remainingLtrs[0]] === undefined) {
          // Create new node at letter
          node.keys[remainingLtrs[0]] = new Node();
        }

        // Move to next letter
        addFrom(node.keys[remainingLtrs[0]], remainingLtrs.slice(1));
      } else {
        // Mark end of word
        node.end = true;
      }
    })(this.root, word);
  }

  /** Check if a specific word is currently stored in the trie. */
  contains(string: string): boolean {
    if (!string.match(/^[A-Za-z]+$/)) return false;

    return (function searchFrom(node: Node, remainingLtrs: string): boolean {
      if (remainingLtrs) {
        if (node.keys[remainingLtrs[0]]) {
          // Move to next letter
          return searchFrom(
            node.keys[remainingLtrs[0]],
            remainingLtrs.slice(1)
          );
        } else {
          // String not present
          return false;
        }
      } else {
        // Word exists if this node is an end point
        return node.end;
      }
    })(this.root, string);
  }

  /**
   * Remove a word from the trie, returning a boolean confirming whether or not
   * the word was present (and was therefore removed).
   */
  remove(word: string): boolean {
    if (!word.match(/^[A-Za-z]+$/)) return false;

    // Array of [current node, next letter] tuples
    let wordNodes: Array<[Node, string]> = [];

    const collectNodesFrom = (node: Node, remainingLtrs: string): boolean => {
      wordNodes.push([node, remainingLtrs[0]]);

      if (remainingLtrs) {
        if (node.keys[remainingLtrs[0]]) {
          // Move to next letter
          return collectNodesFrom(
            node.keys[remainingLtrs[0]],
            remainingLtrs.slice(1)
          );
        } else {
          // String not present
          return false;
        }
      } else {
        // Word exists if this node is an end point
        return node.end;
      }
    };

    if (!collectNodesFrom(this.root, word)) return false;

    // Remove endpoint from last node
    let [currentNode, nextLtr]: [Node, string] = wordNodes.pop();
    currentNode.end = false;

    let onSharedPath = Object.keys(currentNode.keys).length > 0;

    // Remove nodes that aren't part of any other word
    while (wordNodes.length && !onSharedPath) {
      [currentNode, nextLtr] = wordNodes.pop();
      delete currentNode.keys[nextLtr];

      onSharedPath =
        Object.keys(currentNode.keys).length > 0 || currentNode.end;
    }

    return true;
  }

  /** Clear the contents of the trie. */
  clear(): void {
    this.root = new Node();
  }

  /** Return an array of all words stored in the trie. */
  getAll(): string[] {
    let words: string[] = [];

    (function searchFrom(node: Node, wordSoFar: string): void {
      if (node.end) words.push(wordSoFar);

      for (const key of Object.keys(node.keys)) {
        searchFrom(node.keys[key], wordSoFar + key);
      }
    })(this.root, "");

    return words;
  }
}
