#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class FibonacciSearch:
    def search(self, nums: List[int], target: int) -> int:
        fibonacci, index = [1, 1], 1
        while len(nums) > fibonacci[index] - 1:
            index += 1
            fibonacci.append(fibonacci[index - 1] + fibonacci[index - 2])

        aux = list(nums)
        aux.extend([nums[-1]] * (fibonacci[index] - len(nums)))

        start, end = 0, len(nums) - 1
        while start <= end:
            middle = start + fibonacci[index - 1] - 1
            if target == aux[middle]:
                return len(nums) - 1 if middle >= len(nums) else middle

            if target < aux[middle]:
                end = middle - 1
                index -= 1
            else:
                start = middle + 1
                index -= 2
        return -1
