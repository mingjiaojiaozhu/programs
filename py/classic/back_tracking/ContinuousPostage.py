#!/usr/bin/env python
# -*- coding:gbk -*-

import sys
from typing import List

class ContinuousPostage:
    def solution(self, num: int, count: int) -> List[int]:
        result, aux = [0 for _ in range(num)], [0 for _ in range(num + 1)]
        aux[1] = 1
        ends = [sys.maxsize for _ in range((num * count) << 6)]
        ends[0] = 0
        self.__search(num, count, 1, 1, ends, 0, aux, result)
        return result

    def __search(self, num: int, count: int, start: int, index: int, ends: List[int], maxValue: int, aux: List[int], result: List[int]) -> int:
        for i in range(aux[start - 1] * (count - 1) + 1):
            if ends[i] < count:
                for j in range(1, count - ends[i] + 1):
                    if ends[i + aux[start] * j] > ends[i] + j:
                        ends[i + aux[start] * j] = ends[i] + j
        while ends[index] < sys.maxsize:
            index += 1

        if start == num:
            if maxValue < index - 1:
                result[ : ], maxValue = aux[1 : ], index - 1
            return maxValue

        pivot = list(ends)
        for i in range(aux[start] + 1, index + 1):
            if ends[index - i] < count:
                aux[start + 1] = i
                maxValue = self.__search(num, count, start + 1, index + 1, ends, maxValue, aux, result)
                ends = list(pivot)
        return maxValue
