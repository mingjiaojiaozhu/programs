#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class Arrangement:
    def solution(self, nums: List[int], k: int) -> List[List[int]]:
        result = []
        self.__search(nums, k, 0, result)
        return result

    def __search(self, nums: List[int], k: int, start: int, result: List[List[int]]) -> None:
        if k == start:
            result.append(list(nums[ : k]))
            return

        self.__search(nums, k, start + 1, result)
        for i in range(start + 1, len(nums)):
            nums[start], nums[i] = nums[i], nums[start]
            self.__search(nums, k, start + 1, result)
            nums[start], nums[i] = nums[i], nums[start]
