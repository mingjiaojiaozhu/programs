#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class Sudoku:
    def solution(self, nums: List[List[int]]) -> None:
        lines, columns, blocks = [0 for _ in range(len(nums))], [0 for _ in range(len(nums))], [[0 for _ in range(len(nums) // 3)] for _ in range(len(nums) // 3)]
        for i in range(len(nums)):
            for j in range(len(nums)):
                if nums[i][j]:
                    self.__fill(lines, columns, blocks, i, j, nums[i][j] - 1)

        while True:
            flag = False
            for i in range(len(nums)):
                for j in range(len(nums)):
                    if not nums[i][j]:
                        mask = ~(lines[i] | columns[j] | blocks[i // 3][j // 3]) & 0x1ff
                        if not (mask & (mask - 1)):
                            digit = self.__getBits(mask - 1)
                            self.__fill(lines, columns, blocks, i, j, digit)
                            nums[i][j], flag = digit + 1, True
            if not flag:
                break

        spaces = []
        for i in range(len(nums)):
            for j in range(len(nums)):
                if not nums[i][j]:
                    spaces.append([i, j])
        self.__search(nums, lines, columns, blocks, spaces, 0, False)

    def __search(self, nums: List[List[int]], lines: List[int], columns: List[int], blocks: List[List[int]], spaces: List[List[int]], index: int, flag: bool) -> bool:
        if index == len(spaces):
            return True

        row, col = spaces[index][0], spaces[index][1]
        mask = ~(lines[row] | columns[col] | blocks[row // 3][col // 3]) & 0x1ff
        while mask and not flag:
            pos = mask & (~mask + 1)
            mask &= (mask - 1)
            digit = self.__getBits(pos - 1)
            self.__fill(lines, columns, blocks, row, col, digit)
            nums[row][col] = digit + 1
            flag = self.__search(nums, lines, columns, blocks, spaces, index + 1, flag)
            self.__fill(lines, columns, blocks, row, col, digit)
        return flag

    def __fill(self, lines: List[int], columns: List[int], blocks: List[List[int]], row: int, col: int, digit: int) -> None:
        lines[row] ^= (1 << digit)
        columns[col] ^= (1 << digit)
        blocks[row // 3][col // 3] ^= (1 << digit)

    def __getBits(self, value: int) -> int:
        result = 0
        while value:
            result += 1
            value &= value - 1
        return result
