#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class Hanoi:
    def solution(self, values1: List[int], values2: List[int], values3: List[int]) -> None:
        self.__move(len(values1), values1, values2, values3)

    def __move(self, size: int, values1: List[int], values2: List[int], values3: List[int]) -> None:
        size -= 1
        if not size:
            values3.append(values1[-1])
            values1.pop()
            return

        self.__move(size, values1, values3, values2)
        values3.append(values1[-1])
        values1.pop()
        self.__move(size, values2, values1, values3)
