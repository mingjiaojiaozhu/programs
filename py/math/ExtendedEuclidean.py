#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class ExtendedEuclidean:
    def gcd(self, num1: int, num2: int) -> List[int]:
        if not num2:
            return [num1, 1, 0]

        result = self.gcd(num2, num1 % num2)
        result[1], result[2] = result[2], result[1] - result[2] * (num1 // num2)
        return result
