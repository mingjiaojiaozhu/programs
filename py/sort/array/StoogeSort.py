#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class StoogeSort:
    def sort(self, nums: List[int]) -> None:
        self.__sort(nums, 0, len(nums) - 1)

    def __sort(self, nums: List[int], start: int, end: int) -> None:
        if nums[start] > nums[end]:
            nums[start], nums[end] = nums[end], nums[start]

        if start + 1 < end:
            third = (end - start + 1) // 3
            self.__sort(nums, start, end - third)
            self.__sort(nums, start + third, end)
            self.__sort(nums, start, end - third)
