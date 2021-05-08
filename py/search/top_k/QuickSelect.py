#!/usr/bin/env python
# -*- coding:gbk -*-

import random
from typing import List

class QuickSelect:
    def search(self, nums: List[int], k: int) -> List[int]:
        self.__search(nums, 0, len(nums) - 1, k)
        return nums[ : k]

    def __search(self, nums: List[int], start: int, end: int, k: int) ->None:
        partition = self.__getPartition(nums, start, end)
        if k == partition - start + 1:
            return

        if k < partition - start + 1:
            self.__search(nums, start, partition - 1, k)
        else:
            self.__search(nums, partition + 1, end, k - (partition - start + 1))

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
