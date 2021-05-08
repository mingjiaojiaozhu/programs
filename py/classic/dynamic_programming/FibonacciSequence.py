#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class FibonacciSequence:
    def solution(self, num: int) -> List[int]:
        result = [1, 1]
        for _ in range(2, num):
            result.append(result[-1] + result[-2])
        return result
