#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class TimSort:
    def sort(self, nums: List[int]) -> None:
        if len(nums) < 16:
            runLength = self.__getRunLength(nums, 0, len(nums))
            self.__insertSort(nums, 0, len(nums), runLength)
            return

        aux, runBase, runSize = list(nums), [], []
        start, end = 0, len(nums)
        while end > 0:
            runLength = self.__getRunLength(nums, start, len(nums))
            if runLength < 16:
                size = min(end, 16)
                self.__insertSort(nums, start, start + size, start + runLength)
                runLength = size

            runBase.append(start)
            runSize.append(runLength)
            self.__mergeRuns(nums, aux, runBase, runSize)

            start += runLength
            end -= runLength

        while len(runBase) > 1:
            self.__merge(nums, aux, len(runBase) - 2, runBase, runSize)

    def __getRunLength(self, nums: List[int], start: int, end: int) -> int:
        if start + 1 == end:
            return 1

        index = start + 1
        if nums[start] > nums[index]:
            while index < end - 1 and nums[index] > nums[index + 1]:
                index += 1
            nums[start: index + 1] = reversed(nums[start: index + 1])
        else:
            while index < end - 1 and nums[index] <= nums[index + 1]:
                index += 1
        return index - start + 1

    def __insertSort(self, nums: List[int], start: int, end: int, index: int) -> None:
        for i in range(index, end):
            pivot = nums[i]
            if pivot >= nums[i - 1]:
                continue

            left, right = start, i - 1
            while left <= right:
                middle = left + ((right - left) >> 1)
                if pivot < nums[middle]:
                    right = middle - 1
                else:
                    left = middle + 1

            for j in range(i - 1, left - 1, -1):
                nums[j + 1] = nums[j]
            nums[left] = pivot

    def __mergeRuns(self, nums: List[int], aux: List[int], runBase: List[int], runSize: List[int]) -> None:
        while len(runBase) > 1:
            index = len(runBase) - 2
            if index > 0 and runSize[index - 1] <= runSize[index] + runSize[index + 1]:
                if runSize[index - 1] < runSize[index + 1]:
                    index -= 1
                self.__merge(nums, aux, index, runBase, runSize)
            elif runSize[index] <= runSize[index + 1]:
                self.__merge(nums, aux, index, runBase, runSize)
            else:
                return

    def __merge(self, nums: List[int], aux: List[int], runIndex: int, runBase: List[int], runSize: List[int]) -> None:
        base1, size1, base2, size2 = runBase[runIndex], runSize[runIndex], runBase[runIndex + 1], runSize[runIndex + 1]
        runSize[runIndex] = size1 + size2
        if runIndex == len(runSize) - 3:
            runBase[runIndex + 1], runSize[runIndex + 1] = runBase[runIndex + 2], runSize[runIndex + 2]
        runBase.pop()
        runSize.pop()

        start = self.__gallopLeft(nums, base1, size1, nums[base2])
        if start >= base1 + size1:
            return
        end = self.__gallopRight(nums, base2, size2, nums[base1 + size1 - 1])
        if end < base2:
            return
        aux[start : end + 1] = nums[start : end + 1]

        index, left1, right1, left2, right2 = start, start, base1 + size1 - 1, base2, end
        while left1 <= right1 and left2 <= right2:
            if aux[left1] > aux[left2]:
                nums[index] = aux[left2]
                left2 += 1
            else:
                nums[index] = aux[left1]
                left1 += 1
            index += 1

        if left1 <= right1:
            nums[index : index + right1 - left1 + 1] = aux[left1 : right1 + 1]
        if left2 <= right2:
            nums[index : index + right2 - left2 + 1] = aux[left2 : right2 + 1]

    def __gallopLeft(self, nums: List[int], base: int, size: int, pivot: int) -> int:
        start, end = base, base + size - 1
        while start <= end:
            middle = start + ((end - start) >> 1)
            if pivot <= nums[middle]:
                end = middle - 1
            else:
                start = middle + 1
        return end + 1

    def __gallopRight(self, nums: List[int], base: int, size: int, pivot: int) -> int:
        start, end = base, base + size - 1
        while start <= end:
            middle = start + ((end - start) >> 1)
            if pivot >= nums[middle]:
                start = middle + 1
            else:
                end = middle - 1
        return start - 1
