#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class SelectionSort:
    def sort(self, nums: List[int]) -> None:
        start, end = 0, len(nums) - 1
        while start < end:
            maxIndex, minIndex = start, start
            for i, value in enumerate(nums[start : end + 1]):
                if nums[maxIndex] < value:
                    maxIndex = i + start
                elif nums[minIndex] > value:
                    minIndex = i + start

            nums[minIndex], nums[start] = nums[start], nums[minIndex]
            if maxIndex == start:
                maxIndex = minIndex
            nums[maxIndex], nums[end] = nums[end], nums[maxIndex]

            start += 1
            end -= 1
