#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class BFPRTSelect:
    def search(self, nums: List[int], k: int) -> List[int]:
        self.__search(nums, 0, len(nums) - 1, k)
        return nums[ : k]

    def __search(self, nums: List[int], start: int, end: int, k: int) -> int:
        median = self.__getMedian(nums, start, end)
        partition = self.__getPartition(nums, median, end)
        if k == partition - start + 1:
            return partition

        if k < partition - start + 1:
            return self.__search(nums, start, partition - 1, k)
        return self.__search(nums, partition + 1, end, k - (partition - start + 1))

    def __getMedian(self, nums: List[int], start: int, end: int) -> int:
        if end - start < 5:
            nums[start : end + 1] = sorted(nums[start : end + 1])
            return start + ((end - start) >> 1)

        index, left, right = start, start, end - 4
        while left <= right:
            nums[left : left + 5] = sorted(nums[left : left + 5])
            nums[index], nums[left + 2] = nums[left + 2], nums[index]

            left += 5
            index += 1
        return self.__search(nums, start, index - 1, ((index - start) >> 1) + 1)

    def __getPartition(self, nums: List[int], start: int, end: int) -> int:
        pivot, left, right = nums[start], start, end
        while left < right:
            while left < right and nums[right] > pivot:
                right -= 1
            while left < right and nums[left] <= pivot:
                left += 1

            if left < right:
                nums[left], nums[right] = nums[right], nums[left]
        nums[start], nums[left] = nums[left], nums[start]
        return left
