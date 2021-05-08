#!/usr/bin/env python
# -*- coding:gbk -*-

import heapq
from typing import List

class HuffmanCoding:
    def solution(self, text: str) -> str:
        maxValue, minValue = ord(max(text)), ord(min(text))
        arrays = [None for _ in range(maxValue - minValue + 1)]

        current, stack = self.__getRoot(text, maxValue - minValue + 1, minValue, arrays), []
        while current or stack:
            while current:
                code = current.code
                stack.append(current)

                current = current.left
                if current:
                    current.code = code + '0'

            current = stack.pop()
            code = current.code

            current = current.right
            if current:
                current.code = code + '1'

        result = ''
        for value in text:
            result += arrays[ord(value) - minValue].code
        return result

    def __getRoot(self, text: str, size: int, minValue: int, arrays: List[int]) -> '__TreeNode':
        buckets = [0 for _ in range(size)]
        for value in text:
            buckets[ord(value) - minValue] += 1

        queue = []
        for i, value in enumerate(buckets):
            node = self.__TreeNode(value, None, None)
            heapq.heappush(queue, node)
            arrays[i] = node

        while len(queue) > 1:
            left, right = heapq.heappop(queue), heapq.heappop(queue)
            heapq.heappush(queue, self.__TreeNode(left.weight + right.weight, left, right))
        return queue.pop()

    class __TreeNode:
        def __init__(self, weight: int, left: '__TreeNode', right: '__TreeNode'):
            self.weight, self.left, self.right, self.code = weight, left, right, ''

        def __lt__(self, other: '__TreeNode'):
            return self.weight < other.weight
