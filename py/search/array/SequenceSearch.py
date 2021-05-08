#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class SequenceSearch:
    def search(self, nums: List[int], target: int) -> int:
        aux = list(nums)
        aux.append(target)

        index = 0
        while target != aux[index]:
            index += 1
        return index if index < len(nums) else -1
