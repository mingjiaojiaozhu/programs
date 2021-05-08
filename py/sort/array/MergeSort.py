#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class MergeSort:
    def sort(self, nums: List[int]) -> None:
        aux = list(nums)
        self.__sort(nums, aux, 0, len(nums) - 1)

    def __sort(self, nums: List[int], aux: List[int], start: int, end: int) -> None:
        if start >= end:
            return

        middle = start + ((end - start) >> 1)
        self.__sort(aux, nums, start, middle)
        self.__sort(aux, nums, middle + 1, end)

        if aux[middle] > aux[middle + 1]:
            self.__merge(nums, aux, start, middle, end)
        else:
            nums[start : end + 1] = aux[start : end + 1]

    def __merge(self, nums: List[int], aux: List[int], start: int, middle: int, end: int) -> None:
        index, left, right = start, start, middle + 1
        while left <= middle and right <= end:
            if aux[left] > aux[right]:
                nums[index] = aux[right]
                right += 1
            else:
                nums[index] = aux[left]
                left += 1
            index += 1

        if left <= middle:
            nums[index : end + 1] = aux[left : middle + 1]
        if right <= end:
            nums[index : end + 1] = aux[right : end + 1]
