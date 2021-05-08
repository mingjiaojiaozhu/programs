#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class InsertionSort:
    def sort(self, nums: List[int]) -> None:
        for i in range(1, len(nums)):
            pivot = nums[i]
            if pivot >= nums[i - 1]:
                continue

            start, end = 0, i - 1
            while start <= end:
                middle = start + ((end - start) >> 1)
                if pivot < nums[middle]:
                    end = middle - 1
                else:
                    start = middle + 1

            for j in range(i - 1, start - 1, -1):
                nums[j + 1] = nums[j]
            nums[start] = pivot
