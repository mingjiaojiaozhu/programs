#!/usr/bin/env python
# -*- coding:gbk -*-

import sys
from typing import List

class SegmentTree:
    def __init__(self, nums: List[int]):
        self.__nodes, self.__length = [self.__TreeNode() for _ in range((len(nums) << 2))], len(nums)
        self.__createNode(nums, 0, len(nums) - 1, 0)

    def set(self, index: int, value: int) -> None:
        if index >= 0 and index < self.__length:
            self.__setNode(index, value, 0)

    def setInterval(self, start: int, end: int, value: int) -> None:
        if start >= 0 and start < self.__length and end >= 0 and end < self.__length:
            self.__setNodes(start, end, value, 0)

    def get(self, index: int) -> int:
        if index >= 0 and index < self.__length:
            return self.__getNodes(index, index, 0)
        return -sys.maxsize

    def getInterval(self, start: int, end: int) -> int:
        if start >= 0 and start < self.__length and end >= 0 and end < self.__length:
            return self.__getNodes(start, end, 0)
        return -sys.maxsize

    def __createNode(self, nums: List[int], start: int, end: int, parent: int) -> None:
        self.__nodes[parent].start, self.__nodes[parent].end = start, end
        if start == end:
            self.__nodes[parent].value = nums[start]
            return

        middle, child = start + ((end - start) >> 1), (parent << 1) + 1
        self.__createNode(nums, start, middle, child)
        self.__createNode(nums, middle + 1, end, child + 1)
        self.__nodes[parent].value = self.__nodes[child].value + self.__nodes[child + 1].value

    def __setNode(self, index: int, value: int, parent: int) -> int:
        if self.__nodes[parent].start == self.__nodes[parent].end:
            self.__nodes[parent].value = value
            return

        middle, child = self.__nodes[parent].start + ((self.__nodes[parent].end - self.__nodes[parent].start) >> 1), (parent << 1) + 1
        if index <= middle:
            self.__setNode(index, value, child)
        else:
            self.__setNode(index, value, child + 1)
        self.__nodes[parent].value = self.__nodes[child].value + self.__nodes[child + 1].value

    def __setNodes(self, start: int, end: int, value: int, parent: int) -> int:
        if start == self.__nodes[parent].start and end == self.__nodes[parent].end:
            self.__nodes[parent].value += (end - start + 1) * value
            self.__nodes[parent].covered += value
            return

        middle, child = self.__nodes[parent].start + ((self.__nodes[parent].end - self.__nodes[parent].start) >> 1), (parent << 1) + 1
        if end <= middle:
            self.__setNodes(start, end, value, child)
        elif start > middle:
            self.__setNodes(start, end, value, child + 1)
        else:
            self.__setNodes(start, middle, value, child)
            self.__setNodes(middle + 1, end, value, child + 1)
        self.__nodes[parent].value = self.__nodes[child].value + self.__nodes[child + 1].value

    def __getNodes(self, start: int, end: int, parent: int) -> int:
        if self.__nodes[parent].covered:
            if self.__nodes[parent].start != self.__nodes[parent].end:
                child, covered = (parent << 1) + 1, self.__nodes[parent].covered
                self.__nodes[child].covered += covered
                self.__nodes[child + 1].covered += covered
                if covered:
                    self.__nodes[child].value += (self.__nodes[child].end - self.__nodes[child].start + 1) * covered
                    self.__nodes[child + 1].value += (self.__nodes[child + 1].end - self.__nodes[child + 1].start + 1) * covered
            self.__nodes[parent].covered = 0

        if start == self.__nodes[parent].start and end == self.__nodes[parent].end:
            return self.__nodes[parent].value

        middle, child = self.__nodes[parent].start + ((self.__nodes[parent].end - self.__nodes[parent].start) >> 1), (parent << 1) + 1
        if end <= middle:
            return self.__getNodes(start, end, child)
        if start > middle:
            return self.__getNodes(start, end, child + 1)
        return self.__getNodes(start, middle, child) + self.__getNodes(middle + 1, end, child + 1)

    class __TreeNode:
        def __init__(self):
            self.start, self.end, self.value, self.covered = 0, 0, 0, 0
