#!/usr/bin/env python
# -*- coding:gbk -*-

class TrieTree:
    def __init__(self):
        self.__root = self.__TreeNode()

    def isEmpty(self) -> bool:
        for i in range(26):
            if self.__root.next[i]:
                return False
        return True

    def add(self, text: str) -> None:
        current = self.__root
        for value in text:
            index = ord(value) - ord('a')
            if not current.next[index]:
                current.next[index] = self.__TreeNode()
                current.depth += 1
            current = current.next[index]
        current.ended = True

    def erase(self, text: str) -> None:
        index = ord(text[0]) - ord('a')
        self.__root.next[index] = self.__eraseNode(self.__root.next[index], text, len(text), 1)

    def contains(self, text: int) -> bool:
        current = self.__root
        for value in text:
            index = ord(value) - ord('a')
            next = current.next[index]
            if not next:
                return False
            current = next
        return current.ended

    def clear(self) -> None:
        for i in range(26):
            self.__root.next[i] = None

    def __eraseNode(self, current: '__TreeNode', text: str, depth: int, pos: int) -> '__TreeNode':
        if not current:
            return None

        if pos >= depth:
            if not current.depth:
                return None
            current.ended = False
            return current

        index = ord(text[pos]) - ord('a')
        current.next[index] = self.__eraseNode(current.next[index], text, depth, pos + 1)
        if current.next[index]:
            return current

        if current.depth:
            current.depth -= 1
        if not current.depth and not current.ended:
            return None
        return current

    class __TreeNode:
        def __init__(self):
            self.next, self.depth, self.ended = [None for _ in range(26)], 0, False
