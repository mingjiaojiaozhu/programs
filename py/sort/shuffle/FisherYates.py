#!/usr/bin/env python
# -*- coding:gbk -*-

import random
from typing import List

class FisherYates:
    def shuffle(self, nums: List[int]) -> List[int]:
        result = []
        while nums:
            index = random.randrange(0, len(nums))
            result.append(nums[index])
            nums.pop(index)
        return result
