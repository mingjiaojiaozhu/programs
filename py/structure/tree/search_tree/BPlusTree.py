#!/usr/bin/env python
# -*- coding:gbk -*-

import sys

class BPlusTree:
    def __init__(self, degree: int):
        self.__root, self.__degree = None, degree

    def isEmpty(self) -> bool:
        return not self.__root

    def add(self, key: int, value: int) -> None:
        if not self.__root:
            self.__root = self.__TreeNode(self.__degree, True)
            self.__root.keys[0], self.__root.values[0] = key, value
            return

        if self.__root.count != (self.__degree << 1):
            self.__addNode(self.__root, key, value)
            return

        node = self.__TreeNode(self.__degree, False)
        node.children[0] = self.__root
        self.__splitChild(node, self.__root, 0)

        if key > node.keys[node.count - 1]:
            node.keys[node.count - 1] = key

        index = 1 if node.keys[0] < key else 0
        self.__addNode(node.children[index], key, value)
        self.__root = node

    def erase(self, key: int) -> None:
        if not self.__root:
            return

        self.__eraseNode(self.__root, key)
        if not self.__root.count:
            self.__root = None
        elif self.__root.count <= 1 and not self.__root.leaf:
            self.__root = self.__root.children[0]

    def set(self, key: int, value: int) -> None:
        current = self.__root
        while current:
            start, end = 0, current.count - 1
            while start <= end:
                middle = start + ((end - start) >> 1)
                if key > current.keys[middle]:
                    start = middle + 1
                else:
                    end = middle - 1

            if current.leaf:
                if start < current.count and key == current.keys[start]:
                    current.values[start] = value
                return

            if start >= current.count:
                return
            current = current.children[start]

    def get(self, key: int) -> int:
        current = self.__root
        while current:
            start, end = 0, current.count - 1
            while start <= end:
                middle = start + ((end - start) >> 1)
                if key > current.keys[middle]:
                    start = middle + 1
                else:
                    end = middle - 1

            if current.leaf:
                if start < current.count and key == current.keys[start]:
                    return current.values[start]
                return -sys.maxsize

            if start >= current.count:
                return -sys.maxsize
            current = current.children[start]
        return -sys.maxsize

    def clear(self) -> None:
        self.__root = None

    def __addNode(self, parent: '__TreeNode', key: int, value: int) -> None:
        start, end = 0, parent.count - 1
        while start <= end:
            middle = start + ((end - start) >> 1)
            if key > parent.keys[middle]:
                start = middle + 1
            else:
                end = middle - 1

        if parent.leaf:
            if start < parent.count and key == parent.keys[start]:
                parent.values[start] = value
                return

            for i in range(parent.count - 1, start - 1, -1):
                parent.keys[i + 1], parent.values[i + 1] = parent.keys[i], parent.values[i]
            parent.keys[start], parent.values[start] = key, value
            parent.count += 1
            return

        if start >= parent.count:
            start = parent.count - 1

        if parent.children[start].count == (self.__degree << 1):
            self.__splitChild(parent, parent.children[start], start)
            if parent.keys[start] < key:
                start += 1

        if key > parent.keys[parent.count - 1]:
            parent.keys[parent.count - 1] = key
        self.__addNode(parent.children[start], key, value)

    def __eraseNode(self, parent: '__TreeNode', key: int) -> None:
        start, end = 0, parent.count - 1
        while start <= end:
            middle = start + ((end - start) >> 1)
            if key > parent.keys[middle]:
                start = middle + 1
            else:
                end = middle - 1

        if parent.leaf:
            if key != parent.keys[start]:
                return

            for i in range(start + 1, parent.count):
                parent.keys[i - 1], parent.values[i - 1] = parent.keys[i], parent.values[i]
            parent.count -= 1
            return

        flag = (start == parent.count - 1)
        if parent.children[start].count <= self.__degree:
            self.__fillChild(parent, start)

        if flag and start > parent.count - 1:
            self.__eraseNode(parent.children[start - 1], key)
        else:
            self.__eraseNode(parent.children[start], key)

        if key == parent.keys[parent.count - 1]:
            parent.keys[parent.count - 1] = parent.children[parent.count - 1].keys[parent.children[parent.count - 1].count - 1]

    def __splitChild(self, parent: '__TreeNode', child: '__TreeNode', index: int) -> None:
        node = self.__TreeNode(self.__degree, child.leaf)
        node.keys[ : child.count - self.__degree] = child.keys[self.__degree : child.count]
        if child.leaf:
            node.values[ : child.count - self.__degree] = child.values[self.__degree : child.count]
            node.next, child.next = child.next, node
        else:
            node.children[ : child.count - self.__degree] = child.children[self.__degree: child.count]

        for i in range(parent.count - 1, index, -1):
            parent.keys[i + 1], parent.children[i + 1] = parent.keys[i], parent.children[i]
        parent.keys[index], parent.keys[index + 1], parent.children[index + 1] = child.keys[self.__degree - 1], node.keys[self.__degree - 1], node

        node.count, child.count = self.__degree, self.__degree
        parent.count += 1

    def __fillChild(self, parent: '__TreeNode', index: int) -> None:
        if index and parent.children[index - 1].count > self.__degree:
            self.__borrowFromPrev(parent, index)
            return

        if index != parent.count - 1 and parent.children[index + 1].count > self.__degree:
            self.__borrowFromNext(parent, index)
            return

        if index != parent.count - 1:
            self.__mergeChild(parent, index)
        else:
            self.__mergeChild(parent, index - 1)

    def __mergeChild(self, parent: '__TreeNode', index: int) -> None:
        child, node = parent.children[index], parent.children[index + 1]
        child.keys[self.__degree : self.__degree + node.count] = node.keys[ : node.count]
        if child.leaf:
            child.values[self.__degree: self.__degree + node.count], child.next = node.values[ : node.count], node.next
        else:
            child.children[self.__degree: node.count + self.__degree] = node.children[ : node.count]

        parent.keys[index] = node.keys[node.count - 1]
        for i in range(index + 2, parent.count):
            parent.keys[i - 1], parent.children[i - 1] = parent.keys[i], parent.children[i]

        child.count += node.count
        parent.count -= 1

    def __borrowFromPrev(self, parent: '__TreeNode', index: int) -> None:
        child, node = parent.children[index], parent.children[index - 1]

        for i in range(child.count - 1, -1, -1):
            child.keys[i + 1] = child.keys[i]
        child.keys[0] = node.keys[node.count - 1]
        if child.leaf:
            for i in range(child.count - 1, -1, -1):
                child.values[i + 1] = child.values[i]
            child.values[0] = node.values[node.count - 1]
        else:
            for i in range(child.count - 1, -1, -1):
                child.children[i + 1] = child.children[i]
            child.children[0] = node.children[node.count - 1]

        parent.keys[index - 1] = node.keys[node.count - 2]

        child.count += 1
        node.count -= 1

    def __borrowFromNext(self, parent: '__TreeNode', index: int) -> None:
        child, node = parent.children[index], parent.children[index + 1]

        child.keys[child.count] = node.keys[0]
        if child.leaf:
            child.values[child.count] = node.values[0]
        else:
            child.children[child.count] = node.children[0]

        for i in range(1, node.count):
            node.keys[i - 1] = node.keys[i]
        if node.leaf:
            for i in range(1, node.count):
                node.values[i - 1] = node.values[i]
        else:
            for i in range(1, node.count):
                node.children[i - 1] = node.children[i]

        parent.keys[index] = child.keys[child.count]

        child.count += 1
        node.count -= 1

    class __TreeNode:
        def __init__(self, degree: int, leaf: bool):
            self.keys, self.count, self.leaf, self.next = [0 for _ in range(degree << 1)], 1, leaf, None
            if leaf:
                self.values = [0 for _ in range(degree << 1)]
            else:
                self.children = [None for _ in range(degree << 1)]
