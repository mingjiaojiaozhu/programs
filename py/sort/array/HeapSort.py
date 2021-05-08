#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class HeapSort:
    def sort(self, nums: List[int]) -> None:
        for i in range((len(nums) >> 1) - 1, -1, -1):
            self.__adjustHeap(nums, i, len(nums))

        for i in range(len(nums) - 1, 0, -1):
            nums[0], nums[i] = nums[i], nums[0]
            self.__adjustHeap(nums, 0, i)

    def __adjustHeap(self, nums: List[int], parent: int, length: int) -> None:
        pivot = nums[parent]
        while True:
            child = (parent << 1) + 1
            if child >= length:
                break

            if child < length - 1 and nums[child] < nums[child + 1]:
                child += 1
            if nums[child] <= pivot:
                break
            nums[parent], parent = nums[child], child
        nums[parent] = pivot
