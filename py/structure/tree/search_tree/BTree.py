#!/usr/bin/env python
# -*- coding:gbk -*-

import sys

class BTree:
    def __init__(self, degree: int):
        self.__root, self.__degree = None, degree

    def isEmpty(self) -> bool:
        return not self.__root

    def add(self, key: int, value: int) -> None:
        if not self.__root:
            self.__root = self.__TreeNode(self.__degree, True)
            self.__root.keys[0], self.__root.values[0] = key, value
            self.__root.count += 1
            return

        if self.__root.count != (self.__degree << 1) - 1:
            self.__addNode(self.__root, key, value)
            return

        node = self.__TreeNode(self.__degree, False)
        node.children[0] = self.__root
        self.__splitChild(node, self.__root, 0)

        index = 1 if node.keys[0] < key else 0
        self.__addNode(node.children[index], key, value)
        self.__root = node

    def erase(self, key: int) -> None:
        if not self.__root:
            return

        self.__eraseNode(self.__root, key)
        if not self.__root.count:
            self.__root = None if self.__root.leaf else self.__root.children[0]

    def set(self, key: int, value: int) -> None:
        current = self.__root
        while current:
            start, end = 0, current.count - 1
            while start <= end:
                middle = start + ((end - start) >> 1)
                if key == current.keys[middle]:
                    current.values[middle] = value
                    return

                if key < current.keys[middle]:
                    end = middle - 1
                else:
                    start = middle + 1

            if current.leaf:
                return
            current = current.children[start]

    def get(self, key: int) -> int:
        current = self.__root
        while current:
            start, end = 0, current.count - 1
            while start <= end:
                middle = start + ((end - start) >> 1)
                if key == current.keys[middle]:
                    return current.values[middle]

                if key < current.keys[middle]:
                    end = middle - 1
                else:
                    start = middle + 1

            if current.leaf:
                return -sys.maxsize
            current = current.children[start]
        return -sys.maxsize

    def clear(self) -> None:
        self.__root = None

    def __addNode(self, parent: '__TreeNode', key: int, value: int) -> None:
        start, end = 0, parent.count - 1
        while start <= end:
            middle = start + ((end - start) >> 1)
            if key == parent.keys[middle]:
                parent.values[middle] = value
                return

            if key < parent.keys[middle]:
                end = middle - 1
            else:
                start = middle + 1

        if parent.leaf:
            for i in range(parent.count - 1, end, -1):
                parent.keys[i + 1], parent.values[i + 1] = parent.keys[i], parent.values[i]
            parent.keys[end + 1], parent.values[end + 1] = key, value
            parent.count += 1
            return

        if parent.children[end + 1].count == (self.__degree << 1) - 1:
            self.__splitChild(parent, parent.children[end + 1], end + 1)
            if parent.keys[end + 1] < key:
                end += 1
        self.__addNode(parent.children[end + 1], key, value)

    def __eraseNode(self, parent: '__TreeNode', key: int) -> None:
        start, end, exists = 0, parent.count - 1, False
        while start <= end:
            middle = start + ((end - start) >> 1)
            if key == parent.keys[middle]:
                exists = True
                break

            if key < parent.keys[middle]:
                end = middle - 1
            else:
                start = middle + 1

        if not exists:
            if parent.leaf:
                return

            flag = (start == parent.count)
            if parent.children[start].count < self.__degree:
                self.__fillChild(parent, start)

            if flag and start > parent.count:
                self.__eraseNode(parent.children[start - 1], key)
            else:
                self.__eraseNode(parent.children[start], key)
            return

        if parent.leaf:
            for i in range(start + 1, parent.count):
                parent.keys[i - 1], parent.values[i - 1] = parent.keys[i], parent.values[i]
            parent.count -= 1
            return

        if parent.children[start].count >= self.__degree:
            current = parent.children[start]
            while not current.leaf:
                current = current.children[current.count]

            parent.keys[start], parent.values[start] = current.keys[current.count - 1], current.values[current.count - 1]
            self.__eraseNode(parent.children[start], current.keys[current.count - 1])
            return

        if parent.children[start + 1].count >= self.__degree:
            current = parent.children[start + 1]
            while not current.leaf:
                current = current.children[0]

            parent.keys[start], parent.values[start] = current.keys[0], parent.values[0]
            self.__eraseNode(parent.children[start + 1], current.keys[0])
            return

        self.__mergeChild(parent, start)
        self.__eraseNode(parent.children[start], key)

    def __splitChild(self, parent: '__TreeNode', child: '__TreeNode', index: int) -> None:
        node = self.__TreeNode(self.__degree, child.leaf)
        node.keys[ : child.count - self.__degree], node.values[ : child.count - self.__degree] = child.keys[self.__degree : child.count], child.values[self.__degree : child.count]
        if not child.leaf:
            node.children[ : child.count - self.__degree + 1] = child.children[self.__degree : child.count + 1]

        for i in range(parent.count - 1, index - 1, -1):
            parent.keys[i + 1], parent.values[i + 1] = parent.keys[i], parent.values[i]
        for i in range(parent.count, index, -1):
            parent.children[i + 1] = parent.children[i]
        parent.keys[index], parent.values[index] = child.keys[self.__degree - 1], child.values[self.__degree - 1]
        parent.children[index + 1] = node

        node.count = self.__degree - 1
        child.count = self.__degree - 1
        parent.count += 1

    def __fillChild(self, parent: '__TreeNode', index: int) -> None:
        if index and parent.children[index - 1].count >= self.__degree:
            self.__borrowFromPrev(parent, index)
            return

        if index != parent.count and parent.children[index + 1].count >= self.__degree:
            self.__borrowFromNext(parent, index)
            return

        if index != parent.count:
            self.__mergeChild(parent, index)
        else:
            self.__mergeChild(parent, index - 1)

    def __mergeChild(self, parent: '__TreeNode', index: int) -> None:
        child, node = parent.children[index], parent.children[index + 1]

        child.keys[self.__degree - 1], child.values[self.__degree - 1] = parent.keys[index], parent.values[index]
        child.keys[self.__degree : self.__degree + node.count], child.values[self.__degree : self.__degree + node.count] = node.keys[ : node.count], node.values[ : node.count]
        if not child.leaf:
            child.children[self.__degree : node.count + self.__degree + 1] = node.children[ : node.count + 1]

        for i in range(index + 1, parent.count):
            parent.keys[i - 1], parent.values[i - 1] = parent.keys[i], parent.values[i]
        for i in range(index + 2, parent.count + 1):
            parent.children[i - 1] = parent.children[i]

        child.count += node.count + 1
        parent.count -= 1

    def __borrowFromPrev(self, parent: '__TreeNode', index: int) -> None:
        child, node = parent.children[index], parent.children[index - 1]

        for i in range(child.count - 1, -1, -1):
            child.keys[i + 1], child.values[i + 1] = child.keys[i], child.values[i]
        child.keys[0], child.values[0] = parent.keys[index - 1], parent.values[index - 1]
        if not child.leaf:
            for i in range(child.count, -1, -1):
                child.children[i + 1] = child.children[i]
            child.children[0] = node.children[node.count]

        parent.keys[index - 1], parent.values[index - 1] = node.keys[node.count - 1], node.values[node.count - 1]

        child.count += 1
        node.count -= 1

    def __borrowFromNext(self, parent: '__TreeNode', index: int) -> None:
        child, node = parent.children[index], parent.children[index + 1]

        child.keys[child.count], child.values[child.count] = parent.keys[index], parent.values[index]
        if not child.leaf:
            child.children[child.count + 1] = node.children[0]

        parent.keys[index], parent.values[index] = node.keys[0], node.values[0]

        for i in range(1, node.count):
            node.keys[i - 1], node.values[i - 1] = node.keys[i], node.values[i]
        if not node.leaf:
            for i in range(1, node.count + 1):
                node.children[i - 1] = node.children[i]

        child.count += 1
        node.count -= 1

    class __TreeNode:
        def __init__(self, degree: int, leaf: bool):
            self.keys, self.values, self.count, self.leaf = [0 for _ in range((degree << 1) - 1)], [0 for _ in range(
                (degree << 1) - 1)], 0, leaf
            if not leaf:
                self.children = [None for _ in range(degree << 1)]
