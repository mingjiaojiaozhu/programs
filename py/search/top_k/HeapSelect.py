#!/usr/bin/env python
# -*- coding:gbk -*-

import heapq
from typing import List

class HeapSelect:
    def search(self, nums: List[int], k: int) -> List[int]:
        queue = []
        for value in nums:
            if len(queue) < k:
                heapq.heappush(queue, self.__HeapNode(value))
                continue

            if value < queue[0].value:
                heapq.heappop(queue)
                heapq.heappush(queue, self.__HeapNode(value))
        return [_.value for _ in queue]

    class __HeapNode:
        def __init__(self, value: int):
            self.value = value

        def __lt__(self, other: '__HeapNode'):
            return self.value > other.value
