#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class EightQueens:
    def solution(self, num: int) -> List[List[str]]:
        result, aux = [], [-1 for _ in range(num)]
        self.__search(num, 0, 0, 0, 0, aux, result)
        return result

    def __search(self, num: int, row: int, col: int, left: int, right: int, aux: List[int], result: List[List[str]]) -> None:
        if row == num:
            lines = []
            for value in aux:
                line = ['0' for _ in range(num)]
                line[value] = '1'
                lines.append(''.join(line))
            result.append(lines)
            return

        mask = ((1 << num) - 1) & (~(col | left | right))
        while mask:
            pos = mask & (~mask + 1)
            mask &= mask - 1
            aux[row] = self.__getBits(pos - 1)
            self.__search(num, row + 1, col | pos, (left | pos) << 1, (right | pos) >> 1, aux, result)
            aux[row] = -1

    def __getBits(self, value: int) -> int:
        result = 0
        while value:
            result += 1
            value &= value - 1
        return result
