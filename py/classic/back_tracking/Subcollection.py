#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class Subcollection:
    def solution(self, nums: List[int]) -> List[List[int]]:
        result, aux = [], []
        self.__search(nums, 0, aux, result)
        return result

    def __search(self, nums: List[int], start: int, aux: List[int], result: List[List[int]]) -> None:
        result.append(list(aux))
        for i, value in enumerate(nums[start : ]):
            aux.append(value)
            self.__search(nums, start + i + 1, aux, result)
            aux.pop()
