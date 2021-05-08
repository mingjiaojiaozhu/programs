#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class AhoCorasick:
    def search(self, text: str, patterns: List[str]) -> List[int]:
        root = self.__getRoot(patterns)

        result, current = [-1 for _ in range(len(patterns))], root
        for i, value in enumerate(text):
            aux = None
            while not aux:
                aux = current.next[ord(value) - ord('a')]
                if current == root:
                    break

                if not aux:
                    current = current.failure
            if aux:
                current = aux

            for index in current.indexes:
                result[index] = i - len(patterns[index]) + 1
        return result

    def __getRoot(self, patterns: List[str]) -> '__TreeNode':
        root = self.__TreeNode()
        for i, pattern in enumerate(patterns):
            current = root
            for value in pattern:
                index = ord(value) - ord('a')
                if not current.next[index]:
                    current.next[index] = self.__TreeNode()
                current = current.next[index]
            current.indexes.append(i)

        queue = []
        for i in range(26):
            if root.next[i]:
                root.next[i].failure = root
                queue.append(root.next[i])
        while queue:
            current = queue.pop(0)
            for i in range(26):
                if not current.next[i]:
                    continue

                child, failure = current.next[i], current.failure
                while failure and not failure.next[i]:
                    failure = failure.failure
                if not failure:
                    child.failure = root
                else:
                    child.failure = failure.next[i]
                    for index in failure.next[i].indexes:
                        child.indexes.append(index)
                queue.append(child)
        return root

    class __TreeNode:
        def __init__(self):
            self.next, self.failure, self.indexes = [None for _ in range(26)], None, []
