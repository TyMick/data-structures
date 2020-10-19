class Node {
  value: number;
  left: Node = null;
  right: Node = null;

  constructor(value: number) {
    this.value = value;
  }
}

/**
 * A binary search tree data structure, ordered with respect to the child
 * subtrees such that (in the default "left-to-right" mode) the value of each
 * node in a left subtree is less than the value of the parent node, and the
 * value of each node in a right subtree is greater than the value of the parent
 * node (or vice versa in "right-to-left" mode). The `mode` property is included
 * so that the binary tree can be inverted in-place.
 */
export default class BinarySearchTree {
  root: Node = null;
  mode: "left-to-right" | "right-to-left";

  constructor(mode: "left-to-right" | "right-to-left" = "left-to-right") {
    this.mode = mode;
  }

  /**
   * Add a value to the tree.
   * @param {number} value - The value you wish to add.
   * @returns `true` if the value was added successfully or `false` if the value
   * was already present in the tree.
   */
  add(value: number): boolean {
    if (this.root) {
      const addTo = (node: Node, newValue: number): boolean => {
        if (isLeftOf(newValue, node.value, this.mode)) {
          if (node.left) {
            // Recurse
            return addTo(node.left, newValue);
          } else {
            // Add new value
            node.left = new Node(newValue);
            return true;
          }
        } else if (isRightOf(newValue, node.value, this.mode)) {
          if (node.right) {
            // Recurse
            return addTo(node.right, newValue);
          } else {
            // Add new value
            node.right = new Node(newValue);
            return true;
          }
        } else {
          // Value is already present
          return false;
        }
      };

      return addTo(this.root, value);
    } else {
      // Add new value as root
      this.root = new Node(value);
      return true;
    }
  }

  /**
   * Remove a given value from the tree, maintaining binary tree structure (or
   * return `null` if the value is not present).
   */
  remove(value: number): void | null {
    if (!this.root) return null;

    const findTargetFrom = (node: Node, parent: Node): [Node, Node] => {
      if (isLeftOf(value, node.value, this.mode)) {
        return node.left ? findTargetFrom(node.left, node) : [null, null];
      } else if (isRightOf(value, node.value, this.mode)) {
        return node.right ? findTargetFrom(node.right, node) : [null, null];
      } else {
        return [node, parent];
      }
    };
    const [target, parent] = findTargetFrom(this.root, null);

    if (!target) return null;

    let numChildren = Number(!!target.left) + Number(!!target.right);

    // Case 1: target has no children
    if (numChildren === 0) {
      if (parent) {
        // Remove parent reference
        if (target === parent.left) {
          parent.left = null;
        } else {
          parent.right = null;
        }
      } else {
        // Root is the only node
        this.root = null;
      }
    }

    // Case 2: target has one child
    else if (numChildren === 1) {
      if (parent) {
        // Link child to parent
        if (target === parent.left) {
          parent.left = target.left || target.right;
        } else {
          parent.right = target.left || target.right;
        }
      } else {
        // Make child the new root
        this.root = target.left || target.right;
      }
    }

    // Case 3: target has two children
    else {
      // Find replacement
      let replacement: Node = target.right;
      let leafParent: Node = null;
      while (replacement.left) {
        leafParent = replacement;
        replacement = replacement.left;
      }

      if (leafParent) {
        // Replacement is a leaf
        // Remove parent reference
        leafParent.left = null;

        // Link replacement to target children
        replacement.left = target.left;
        replacement.right = target.right;
      } else {
        // Link replacement to target left child
        replacement.left = target.left;
      }

      // Link replacement to parent
      if (parent) {
        if (target === parent.left) {
          parent.left = replacement;
        } else {
          parent.right = replacement;
        }
      } else {
        this.root = replacement;
      }
    }
  }

  /** Return whether or not the given value is present in the tree. */
  contains(value: number): boolean {
    const searchFrom = (node: Node, searchValue: number): boolean => {
      if (node) {
        if (isLeftOf(searchValue, node.value, this.mode)) {
          return searchFrom(node.left, searchValue);
        } else if (isRightOf(searchValue, node.value, this.mode)) {
          return searchFrom(node.right, searchValue);
        } else {
          // Search value has been found
          return true;
        }
      } else {
        // Search value is not present
        return false;
      }
    };

    return searchFrom(this.root, value);
  }

  /** Clear the contents of the tree. */
  clear(): void {
    this.root = null;
    this.mode = "left-to-right";
  }

  /** Return the minimum value in the tree (or `null` if the tree is empty). */
  findMin(): number | null {
    // Find leftmost node
    let currentNode: Node = this.root;
    while (currentNode?.left) {
      currentNode = currentNode.left;
    }

    return currentNode?.value ?? null;
  }

  /** Return the maximum value in the tree (or `null` if the tree is empty). */
  findMax(): number | null {
    // Find rightmost node
    let currentNode: Node = this.root;
    while (currentNode?.right) {
      currentNode = currentNode.right;
    }

    return currentNode?.value ?? null;
  }

  /**
   * Return the distance from the root node to the farthest leaf node (or `-1`
   * if the tree is empty).
   */
  findMaxHeight(): number {
    if (this.root) {
      return (function maxHeightFrom(node: Node, currentDepth: number): number {
        if (node.left === null && node.right === null) {
          return currentDepth;
        } else if (node.left === null) {
          return maxHeightFrom(node.right, currentDepth + 1);
        } else if (node.right === null) {
          return maxHeightFrom(node.left, currentDepth + 1);
        } else {
          return Math.max(
            maxHeightFrom(node.left, currentDepth + 1),
            maxHeightFrom(node.right, currentDepth + 1)
          );
        }
      })(this.root, 0);
    } else {
      return -1;
    }
  }

  /**
   * Return the distance from the root node to the nearest leaf node (or `-1` if
   * the tree is empty).
   */
  findMinHeight(): number {
    if (this.root) {
      // I previously used recursion here as I did in `findMaxHeight`, but then
      // I thought of this method, which saves time by stopping the search when
      // the nearest leaf node is found.

      let currentDepth = 0;
      let currentTreeLevel: Node[] = [this.root];

      while (currentTreeLevel.length) {
        let nextTreeLevel: Node[] = [];

        for (const node of currentTreeLevel) {
          if (node.left === null && node.right === null) {
            return currentDepth;
          }

          if (node.left) nextTreeLevel.push(node.left);
          if (node.right) nextTreeLevel.push(node.right);
        }

        currentDepth++;
        currentTreeLevel = nextTreeLevel;
      }
    } else {
      return -1;
    }
  }

  /**
   * Return whether or not the tree is balanced (if its minimum height and
   * maximum height differ by at most 1).
   */
  isBalanced(): boolean {
    // return this.findMaxHeight() - this.findMinHeight() <= 1;

    // The above method is more concise, but the below method is more efficient
    // (because you don't have to traverse the tree twice):

    if (this.root) {
      let currentDepth = 0;
      let currentTreeLevel: Node[] = [this.root];
      let minHeight: number;

      while (currentTreeLevel.length) {
        let nextTreeLevel: Node[] = [];

        for (const node of currentTreeLevel) {
          if (
            minHeight === undefined &&
            node.left === null &&
            node.right === null
          ) {
            minHeight = currentDepth;
          }

          if (node.left) nextTreeLevel.push(node.left);
          if (node.right) nextTreeLevel.push(node.right);
        }

        currentDepth++;
        currentTreeLevel = nextTreeLevel;
      }

      const maxHeight = currentDepth - 1;
      return maxHeight - minHeight <= 1;
    } else {
      return true;
    }
  }

  /**
   * Return an array of all values in the tree arranged in the sequence of an
   * in-order depth-first traversal of the tree (or `null` if the tree is
   * empty).
   */
  inorder(): number[] | null {
    let values: number[] = [];

    (function addValuesFrom(node: Node): void {
      if (node) {
        // Add left values
        addValuesFrom(node.left);
        // Add this node's value
        values.push(node.value);
        // Add right values
        addValuesFrom(node.right);
      }
    })(this.root);

    return values.length ? values : null;
  }

  /**
   * Return an array of all values in the tree arranged in the sequence of a
   * pre-order depth-first traversal of the tree (or `null` if the tree is
   * empty).
   */
  preorder(): number[] | null {
    let values: number[] = [];

    (function addValuesFrom(node: Node): void {
      if (node) {
        // Add this node's value
        values.push(node.value);
        // Add left values
        addValuesFrom(node.left);
        // Add right values
        addValuesFrom(node.right);
      }
    })(this.root);

    return values.length ? values : null;
  }

  /**
   * Return an array of all values in the tree arranged in the sequence of a
   * post-order depth-first traversal of the tree (or `null` if the tree is
   * empty).
   */
  postorder(): number[] | null {
    let values: number[] = [];

    (function addValuesFrom(node: Node): void {
      if (node) {
        // Add left values
        addValuesFrom(node.left);
        // Add right values
        addValuesFrom(node.right);
        // Add this node's value
        values.push(node.value);
      }
    })(this.root);

    return values.length ? values : null;
  }

  /**
   * Return an array of all values in the tree arranged in the sequence of a
   * left-to-right breadth-first traversal of the tree (or `null` if the tree is
   * empty).
   */
  levelOrder(): number[] | null {
    if (this.root) {
      let values: number[] = [];
      let queue: Node[] = [this.root];

      while (queue.length) {
        const currentNode = queue.shift();
        // Add current value
        values.push(currentNode.value);
        // Add children to queue
        if (currentNode.left) queue.push(currentNode.left);
        if (currentNode.right) queue.push(currentNode.right);
      }

      return values;
    } else {
      return null;
    }
  }

  /**
   * Return an array of all values in the tree arranged in the sequence of a
   * right-to-left breadth-first traversal of the tree (or `null` if the tree is
   * empty).
   */
  reverseLevelOrder(): number[] | null {
    if (this.root) {
      let values: number[] = [];
      let queue: Node[] = [this.root];

      while (queue.length) {
        const currentNode = queue.shift();
        // Add current value
        values.push(currentNode.value);
        // Add children to queue
        if (currentNode.right) queue.push(currentNode.right);
        if (currentNode.left) queue.push(currentNode.left);
      }

      return values;
    } else {
      return null;
    }
  }

  /**
   * Invert the tree in-place in linear time, transforming it into its mirror
   * image, such that an in-order traversal of this inverted tree will visit
   * nodes in the reverse order of an in-order traversal of the original tree.
   */
  invert(): void {
    (function invertFrom(node: Node): void {
      if (node) {
        // Swap children
        const oldLeft = node.left;
        node.left = node.right;
        node.right = oldLeft;

        if (node.left) invertFrom(node.left);
        if (node.right) invertFrom(node.right);
      }
    })(this.root);

    this.mode =
      this.mode === "left-to-right" ? "right-to-left" : "left-to-right";
  }

  /**
   * Check if the passed argument is a properly structured binary search tree
   * (that uses "root", "left", "right", and "value" properties) without just
   * checking if it's an instance of the `BinarySearchTree` class.
   */
  static isBinarySearchTree(
    tree: any,
    mode: "left-to-right" | "right-to-left" = "left-to-right"
  ): boolean {
    if ("root" in tree) {
      const isBinarySearchNode = (node: any): boolean => {
        if (node === null) {
          return true;
        } else {
          if (node?.left === null && node?.right === null) {
            if (typeof node?.value === "number") {
              return true;
            } else {
              return false;
            }
          } else if (node?.left === null) {
            if (isRightOf(node?.right?.value, node?.value, mode)) {
              return isBinarySearchNode(node.right);
            } else {
              return false;
            }
          } else if (node?.right === null) {
            if (isLeftOf(node?.left?.value, node?.value, mode)) {
              return isBinarySearchNode(node.left);
            } else {
              return false;
            }
          } else {
            if (
              isLeftOf(node?.left?.value, node?.value, mode) &&
              isRightOf(node?.right?.value, node?.value, mode)
            ) {
              return (
                isBinarySearchNode(node.left) && isBinarySearchNode(node.right)
              );
            } else {
              return false;
            }
          }
        }
      };

      return isBinarySearchNode(tree.root);
    } else {
      return false;
    }
  }
}

function isLeftOf(
  value1: number,
  value2: number,
  mode: "left-to-right" | "right-to-left"
): boolean {
  return mode === "left-to-right" ? value1 < value2 : value1 > value2;
}
function isRightOf(
  value1: number,
  value2: number,
  mode: "left-to-right" | "right-to-left"
): boolean {
  return mode === "left-to-right" ? value2 < value1 : value2 > value1;
}
