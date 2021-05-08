#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class MergeInPlaceSort:
    def sort(self, nums: List[int]) -> None:
        self.__sort(nums, 0, len(nums) - 1)

    def __sort(self, nums: List[int], start: int, end: int) -> None:
        if start >= end:
            return

        middle = start + ((end - start) >> 1)
        self.__sort(nums, start, middle)
        self.__sort(nums, middle + 1, end)

        if nums[middle] > nums[middle + 1]:
            self.__merge(nums, start, middle, end)

    def __merge(self, nums: List[int], start: int, middle: int, end: int) -> None:
        left, right = start, middle + 1
        while left < right and right <= end:
            while left < right and nums[left] <= nums[right]:
                left += 1

            index = right
            while right <= end and nums[right] < nums[left]:
                right += 1

            nums[left: index] = reversed(nums[left: index])
            nums[index: right] = reversed(nums[index: right])
            nums[left: right] = reversed(nums[left: right])

            left += right - index
