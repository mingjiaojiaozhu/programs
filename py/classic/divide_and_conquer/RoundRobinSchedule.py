#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class RoundRobinSchedule:
    def solution(self, k: int) -> List[List[int]]:
        size, result = pow(2, k), []
        for i in range(size):
            result.append([i for _ in range(size)])
        self.__schedule(size, 0, 0, result)
        return result

    def __schedule(self, size: int, startRow: int, startCol: int, result: List[List[int]]) -> None:
        size >>= 1
        if size > 1:
            self.__schedule(size, startRow, startCol, result)
            self.__schedule(size, startRow + size, startCol, result)

        for i in range(size):
            for j in range(size):
                result[startRow + size + i][startCol + size + j] = result[startRow + i][startCol + j]
                result[startRow + i][startCol + size + j] = result[startRow + size + i][startCol + j]
