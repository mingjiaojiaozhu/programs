#!/usr/bin/env python
# -*- coding:gbk -*-

import random
from typing import List

class QuickSort:
    def sort(self, nums: List[int]) -> None:
        self.__sort(nums, 0, len(nums) - 1)

    def __sort(self, nums: List[int], start: int, end: int) -> None:
        if start < end:
            partition = self.__getPartition(nums, start, end)
            self.__sort(nums, start, partition - 1)
            self.__sort(nums, partition + 1, end)

    def __getPartition(self, nums: List[int], start: int, end: int) -> int:
        index = random.randrange(start, end + 1)
        nums[index], nums[end] = nums[end], nums[index]
        pivot = nums[end]

        left, right = start, end
        while left < right:
            while left < right and nums[left] < pivot:
                left += 1
            while left < right and nums[right] >= pivot:
                right -= 1

            if left < right:
                nums[left], nums[right] = nums[right], nums[left]
        nums[left], nums[end] = nums[end], nums[left]
        return left
