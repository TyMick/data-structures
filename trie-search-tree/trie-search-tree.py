import re


class Node:
    def __init__(self):
        self.keys = {}
        self.end = False


class Trie:
    """
    A trie search tree that stores words in an ordered tree structure in which each node
    represents an individual letter.
    """

    def __init__(self):
        self.root = Node()

    def add(self, word):
        """Adds a new word to the trie."""

        if re.search("^[A-Za-z]+$", word) is None:
            raise ValueError(
                "Argument must be a single word with no special characters."
            )

        def add_from(node, remaining_ltrs):
            if remaining_ltrs:
                # Move to next letter, creating new node if necessary
                add_from(
                    node.keys.setdefault(remaining_ltrs[0], Node()), remaining_ltrs[1:]
                )

            else:
                # Mark end of word
                node.end = True

        add_from(self.root, word)

    def contains(self, string):
        """
        Checks if a specific word is currently stored in the trie. Using the `in`
        keyword is equivalent to this method (e.g., `string in trie` is the same as
        `trie.contains(string)`).
        """

        if re.search("^[A-Za-z]+$", string) is None:
            return False

        def search_from(node, remaining_ltrs):
            if remaining_ltrs:
                try:
                    # Move to next letter
                    return search_from(node.keys[remaining_ltrs[0]], remaining_ltrs[1:])

                except:
                    # String not present
                    return False

            else:
                # Word exists if this node is an end point
                return node.end

        return search_from(self.root, string)

    __contains__ = contains

    def remove(self, word):
        """
        Removes a word from the trie and returns a boolean confirming whether or not the
        word was present (and was therefore removed).
        """

        if re.search("^[A-Za-z]+$", word) is None:
            return False

        # List of (current node, next letter) tuples
        word_nodes = []

        def collect_nodes_from(node, remaining_ltrs):

            if remaining_ltrs:
                word_nodes.append((node, remaining_ltrs[0]))

                try:
                    # Move to next letter
                    return collect_nodes_from(
                        node.keys[remaining_ltrs[0]], remaining_ltrs[1:]
                    )

                except:
                    # String not present
                    return False

            else:
                word_nodes.append((node, None))

                # Word exists if this node is an end point
                return node.end

        if not collect_nodes_from(self.root, word):
            return False

        # Removes endpoint from last node
        current_node, next_ltr = word_nodes.pop()
        current_node.end = False

        on_shared_path = len(current_node.keys) > 0

        # Removes nodes that aren't part of any other word
        while word_nodes and not on_shared_path:
            current_node, next_ltr = word_nodes.pop()
            del current_node.keys[next_ltr]

            on_shared_path = len(current_node.keys) > 0 or current_node.end

        return True

    def clear(self):
        """Clears the contents of the trie."""
        self.root = Node()

    def get_all(self):
        """Returns a set of all words stored in the trie."""

        words = set()

        def search_from(node, word_so_far):
            if node.end:
                words.add(word_so_far)

            for letter, next_node in node.keys.items():
                search_from(next_node, word_so_far + letter)

        search_from(self.root, "")

        return words
