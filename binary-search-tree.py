def is_left_of(value1, value2, mode):
    return value1 < value2 if mode == "left-to-right" else value1 > value2


def is_right_of(value1, value2, mode):
    return value2 < value1 if mode == "left-to-right" else value2 > value1


class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None


class BinarySearchTree:
    """
    A binary search tree data structure, ordered with respect to the child subtrees such
    that (in the default "left-to-right" mode) the value of each node in a left subtree
    is less than the value of the parent node, and the value of each node in a right
    subtree is greater than the value of the parent node (or vice versa in "right-to-
    left" mode). The `mode` property is included so that the binary tree can be inverted
    in-place.
    """

    def __init__(self, mode="left-to-right"):
        self.root = None
        self.mode = mode

    def add(self, value):
        """
        Add a value to the tree.

        :param value: The value you wish to add.
        :type value: integer or float
        :returns: `True` if the value was added successfully or `False` if the value was
            already present in the tree.
        """

        if self.root:

            def add_to(node, new_value):
                if is_left_of(new_value, node.value, self.mode):
                    if node.left:
                        # Recurse
                        return add_to(node.left, new_value)
                    else:
                        # Add new value
                        node.left = Node(new_value)
                        return True

                elif is_right_of(new_value, node.value, self.mode):
                    if node.right:
                        # Recurse
                        return add_to(node.right, new_value)
                    else:
                        # Add new value
                        node.right = Node(new_value)
                        return True

                else:
                    # Value is already present
                    return False

            return add_to(self.root, value)

        else:
            # Add new value as root
            self.root = Node(value)
            return True

    def remove(self, value):
        """
        Remove a given value from the tree, maintaining binary tree structure (or return
        `None` if the value is not present).
        """

        if self.root is None:
            return None

        def find_target_from(node, parent):
            if is_left_of(value, node.value, self.mode):
                return find_target_from(node.left, node) if node.left else None, None
            elif is_right_of(value, node.value, self.mode):
                return find_target_from(node.right, node) if node.right else None, None
            else:
                return node, parent

        target, parent = find_target_from(self.root, None)

        if target is None:
            return None

        num_children = bool(target.left) + bool(target.right)

        # Case 1: target has no children
        if num_children == 0:
            if parent:
                # Remove parent reference
                if target == parent.left:
                    parent.left = None
                else:
                    parent.right = None
            else:
                # Root is the only node
                self.root = None

        # Case 2: target has one child
        elif num_children == 1:
            if parent:
                # Link child to parent
                if target == parent.left:
                    parent.left = target.left or target.right
                else:
                    parent.right = target.left or target.right
            else:
                # Make child the new root
                self.root = target.left or target.right

        # Case 3: target has two children
        else:
            # Find replacement
            replacement = target.right
            leaf_parent = None
            while replacement.left:
                leaf_parent = replacement
                replacement = replacement.left

            if leaf_parent:
                # Replacement is a leaf
                # Remove parent reference
                leaf_parent.left = None

                # Link replacement to target children
                replacement.left = target.left
                replacement.right = target.right
            else:
                # Link replacement to target left child
                replacement.left = target.left

            # Link replacement to parent
            if parent:
                if target == parent.left:
                    parent.left = replacement
                else:
                    parent.right = replacement
            else:
                self.root = replacement

    def is_present(self, value):
        """Return whether or not the given value is present in the tree."""

        def is_present_from(node, search_value):
            if node:
                if is_left_of(search_value, node.value, self.mode):
                    return is_present_from(node.left, search_value)
                elif is_right_of(search_value, node.value, self.mode):
                    return is_present_from(node.right, search_value)
                else:
                    # Search value has been found
                    return True
            else:
                # Search value is not present
                return False

        return is_present_from(self.root, value)

    def clear(self):
        """Clear the contents of the tree."""
        self.root = None
        self.mode = "left-to-right"

    def find_min(self):
        """Return the minimum value in the tree (or `None` if the tree is empty)."""

        if self.root:
            # Find leftmost node
            current_node = self.root
            while current_node.left:
                current_node = current_node.left

            return current_node.value

        else:
            return None

    def find_max(self):
        """Return the maximum value in the tree (or `None` if the tree is empty)."""

        if self.root:
            # Find rightmost node
            current_node = self.root
            while current_node.right:
                current_node = current_node.right

            return current_node.value

        else:
            return None

    def find_max_height(self):
        """
        Return the distance from the root node to the farthest leaf node (or `-1` if the
        tree is empty).
        """

        if self.root:

            def max_height_from(node, current_depth):
                if node.left is None and node.right is None:
                    return current_depth

                elif node.left is None:
                    return max_height_from(node.right, current_depth + 1)

                elif node.right is None:
                    return max_height_from(node.left, current_depth + 1)

                else:
                    return max(
                        max_height_from(node.left, current_depth + 1),
                        max_height_from(node.right, current_depth + 1),
                    )

            return max_height_from(self.root, 0)

        else:
            return -1

    def find_min_height(self):
        """
        Return the distance from the root node to the nearest leaf node (or `-1` if the
        tree is empty).
        """

        if self.root:
            # I previously used recursion here as I did in `find_max_height`, but then I
            # thought of this method, which saves time by stopping the search when the
            # nearest leaf node is found.

            current_depth = 0
            current_tree_level = [self.root]

            while current_tree_level:
                next_tree_level = []

                for node in current_tree_level:
                    if node.left is None and node.right is None:
                        return current_depth

                    if node.left:
                        next_tree_level.append(node.left)
                    if node.right:
                        next_tree_level.append(node.right)

                current_depth += 1
                current_tree_level = next_tree_level

        else:
            return -1

    def is_balanced(self):
        """
        Return whether or not the tree is balanced (if its minimum height and maximum
        height differ by at most 1).
        """

        # return self.find_max_height() - self.find_min_height() <= 1

        # The above method is more concise, but the below method is more efficient
        # (because you don't have to traverse the tree twice):

        if self.root:
            current_depth = 0
            current_tree_level = [self.root]

            while current_tree_level:
                next_tree_level = []

                for node in current_tree_level:
                    if node.left is None and node.right is None:
                        try:
                            min_height
                        except NameError:
                            min_height = current_depth

                    if node.left:
                        next_tree_level.append(node.left)
                    if node.right:
                        next_tree_level.append(node.right)

                current_depth += 1
                current_tree_level = next_tree_level

            max_height = current_depth - 1
            return max_height - min_height <= 1

        else:
            return True

    def inorder(self):
        """
        Return an array of all values in the tree arranged in the sequence of an in-
        order depth-first traversal of the tree (or `None` if the tree is empty).
        """

        values = []

        def add_values_from(node):
            if node:
                # Add left values
                add_values_from(node.left)
                # Add self.node's value
                values.append(node.value)
                # Add right values
                add_values_from(node.right)

        add_values_from(self.root)

        return values if values else None

    def preorder(self):
        """
        Return an array of all values in the tree arranged in the sequence of a pre-
        order depth-first traversal of the tree (or `None` if the tree is empty).
        """

        values = []

        def add_values_from(node):
            if node:
                # Add self.node's value
                values.append(node.value)
                # Add left values
                add_values_from(node.left)
                # Add right values
                add_values_from(node.right)

        add_values_from(self.root)

        return values if values else None

    def postorder(self):
        """
        Return an array of all values in the tree arranged in the sequence of a post-
        order depth-first traversal of the tree (or `None` if the tree is empty).
        """

        values = []

        def add_values_from(node):
            if node:
                # Add left values
                add_values_from(node.left)
                # Add right values
                add_values_from(node.right)
                # Add self.node's value
                values.append(node.value)

        add_values_from(self.root)

        return values if values else None

    def level_order(self):
        """
        Return an array of all values in the tree arranged in the sequence of a left-to-
        right breadth-first traversal of the tree (or `None` if the tree is empty).
        """

        if self.root:
            values = []
            queue = [self.root]

            while queue:
                current_node = queue.pop(0)

                # Add current value
                values.append(current_node.value)

                # Add children to queue
                if current_node.left:
                    queue.append(current_node.left)
                if current_node.right:
                    queue.append(current_node.right)

            return values

        else:
            return None

    def reverse_level_order(self):
        """
        Return an array of all values in the tree arranged in the sequence of a right-
        to-left breadth-first traversal of the tree (or `None` if the tree is empty).
        """

        if self.root:
            values = []
            queue = [self.root]

            while queue:
                current_node = queue.pop(0)

                # Add current value
                values.append(current_node.value)

                # Add children to queue
                if current_node.right:
                    queue.append(current_node.right)
                if current_node.left:
                    queue.append(current_node.left)

            return values

        else:
            return None

    def invert(self):
        """
        Invert the tree in-place in linear time, transforming it into its mirror image,
        such that an in-order traversal of self.inverted tree will visit nodes in the
        reverse order of an in-order traversal of the original tree.
        """

        def invert_from(node):
            if node:
                # Swap children
                old_left = node.left
                node.left = node.right
                node.right = old_left

                if node.left:
                    invert_from(node.left)
                if node.right:
                    invert_from(node.right)

        invert_from(self.root)

        self.mode = "right-to-left" if self.mode == "left-to-right" else "left-to-right"


def is_binary_search_tree(tree: any, mode="left-to-right"):
    """
    Check if the passed argument is a properly structured binary search tree (that uses
    "root", "left", "right", and "value" properties) without just checking if it's an
    instance of the `BinarySearchTree` class.
    """

    if hasattr(tree, "root"):

        def is_binary_search_node(node: any):
            if node is None:
                return True

            try:
                if (
                    node.left is None
                    and node.right is None
                    and (type(node.value) is int or type(node.value) is float)
                ):
                    return True

                elif node.left is None and is_right_of(
                    node.right.value, node.value, mode
                ):
                    return is_binary_search_node(node.right)

                elif node.right is None and is_left_of(
                    node.left.value, node.value, mode
                ):
                    return is_binary_search_node(node.left)

                elif is_left_of(node.left.value, node.value, mode) and is_right_of(
                    node.right.value, node.value, mode
                ):
                    return is_binary_search_node(node.left) and is_binary_search_node(
                        node.right
                    )

            finally:
                return False

        return is_binary_search_node(tree.root)

    else:
        return False
