#!/usr/bin/env python
# -*- coding:gbk -*-

import functools
from typing import List

class IntervalCoverage:
    def solution(self, values: List[List[int]], target: List[int]) -> int:
        values.sort(key = functools.cmp_to_key(self.__cmp))

        start, end, index, result = target[0], target[1], 0, 0
        while start < end:
            border = start
            while index < len(values) and start >= values[index][0]:
                if border < values[index][1]:
                    border = values[index][1]
                index += 1

            if border == start:
                return -1

            result += 1
            start = border
        return result

    def __cmp(self, node1: List[int], node2: List[int]) -> int:
        return node1[0] - node2[0]
