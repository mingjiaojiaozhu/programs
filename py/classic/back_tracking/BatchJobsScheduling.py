#!/usr/bin/env python
# -*- coding:gbk -*-

import sys
from typing import List

class BatchJobsScheduling:
    def solution(self, values: List[List[int]]) -> List[int]:
        result, aux, ends = [], [i for i in range(len(values))], [0 for _ in range(3)]
        self.__search(values, 0, ends, sys.maxsize, aux, result)
        return result

    def __search(self, values: List[List[int]], start: int, ends: List[int], minValue: int, aux: List[int], result: List[int]) -> int:
        if start == len(values):
            result[ : ] = aux[ : ]
            return ends[2]

        for i in range(start, len(values)):
            ends[0] += values[aux[i]][0]
            pivot, ends[1] = ends[1], max(ends[0], ends[1]) + values[aux[i]][1]
            ends[2] += ends[1]
            if ends[2] < minValue:
                aux[start], aux[i] = aux[i], aux[start]
                minValue = self.__search(values, start + 1, ends, minValue, aux, result)
                aux[start], aux[i] = aux[i], aux[start]
            ends[0] -= values[aux[i]][0]
            ends[2] -= ends[1]
            ends[1] = pivot
        return minValue
