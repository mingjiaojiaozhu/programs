#!/usr/bin/env python
# -*- coding:gbk -*-

import random
from typing import List

class InsideOut:
    def shuffle(self, nums: List[int]) -> List[int]:
        result = list(nums)
        for i in range(len(nums)):
            index = random.randrange(0, i + 1)
            result[i], result[index] = result[index], nums[i]
        return result
