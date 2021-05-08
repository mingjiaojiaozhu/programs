#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class Combination:
    def solution(self, nums: List[int], k: int) -> List[List[int]]:
        result, aux = [], []
        self.__search(nums, k, 0, aux, result)
        return result

    def __search(self, nums: List[int], k: int, start: int, aux: List[int], result: List[List[int]]) -> None:
        if k == len(aux):
            result.append(list(aux))
            return

        for i, value in enumerate(nums[start : ]):
            aux.append(value)
            self.__search(nums, k, start + i + 1, aux, result)
            aux.pop()
