#!/usr/bin/env python
# -*- coding:gbk -*-

import random
from typing import List

class KnuthDurstenfeld:
    def shuffle(self, nums: List[int]) -> None:
        for i in range(len(nums) - 1, 0, -1):
            index = random.randrange(0, i + 1)
            nums[index], nums[i] = nums[i], nums[index]
