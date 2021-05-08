#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class LongestIncreasingSubsequence:
    def solution(self, values: List[int]) -> int:
        result = [0 for _ in range(len(values))]
        result[0] = 1
        for i in range(len(values)):
            result[i] = 1
            for j in range(i):
                if values[i] > values[j] and result[i] < result[j] + 1:
                    result[i] = result[j] + 1
        return max(result)
