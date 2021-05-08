#!/usr/bin/env python
# -*- coding:gbk -*-

import sys
from typing import List

class CoinChange:
    def solution(self, values: List[int], target: int) -> int:
        result = [sys.maxsize for _ in range(target + 1)]
        result[0] = 0
        for i in range(target + 1):
            for value in values:
                if i >= value:
                    pivot = result[i - value] + 1
                    if result[i] > pivot:
                        result[i] = pivot
        return result[-1] if result[-1] <= target else -1
