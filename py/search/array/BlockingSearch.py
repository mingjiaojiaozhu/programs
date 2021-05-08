#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class BlockingSearch:
    def search(self, nums: List[int], blocks: List[List[int]], target: int) -> int:
        start, end = 0, len(blocks) - 1
        while start <= end:
            middle = start + ((end - start) >> 1)
            if target <= blocks[middle][2]:
                end = middle - 1
            else:
                start = middle + 1

        if start >= len(blocks):
            return -1

        for i, value in enumerate(nums[blocks[start][0] : blocks[start][1] + 1]):
            if target == value:
                return blocks[start][0] + i
        return -1
