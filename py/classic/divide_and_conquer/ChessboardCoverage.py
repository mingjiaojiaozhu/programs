#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class ChessboardCoverage:
    def solution(self, k: int, square: List[int]) -> List[List[int]]:
        size = pow(2, k)
        result = [[0 for _ in range(size)] for _ in range(size)]
        self.__cover(size, square[0], square[1], 0, 0, 1, result)
        return result

    def __cover(self, size: int, row: int, col: int, startRow: int, startCol: int, index: int, result: List[List[int]]) -> int:
        size >>= 1
        if not size:
            return index - 1

        value = index
        index += 1
        if row < startRow + size and col < startCol + size:
            index = self.__cover(size, row, col, startRow, startCol, index, result)
        else:
            result[startRow + size - 1][startCol + size - 1] = value
            index = self.__cover(size, startRow + size - 1, startCol + size - 1, startRow, startCol, index, result)

        index += 1
        if row < startRow + size and col >= startCol + size:
            index = self.__cover(size, row, col, startRow, startCol + size, index, result)
        else:
            result[startRow + size - 1][startCol + size] = value
            index = self.__cover(size, startRow + size - 1, startCol + size, startRow, startCol + size, index, result)

        index += 1
        if row >= startRow + size and col < startCol + size:
            index = self.__cover(size, row, col, startRow + size, startCol, index, result)
        else:
            result[startRow + size][startCol + size - 1] = value
            index = self.__cover(size, startRow + size, startCol + size - 1, startRow + size, startCol, index, result)

        index += 1
        if row >= startRow + size and col >= startCol + size:
            index = self.__cover(size, row, col, startRow + size, startCol + size, index, result)
        else:
            result[startRow + size][startCol + size] = value
            index = self.__cover(size, startRow + size, startCol + size, startRow + size, startCol + size, index, result)
        return index
