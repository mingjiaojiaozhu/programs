#!/usr/bin/env python
# -*- coding:gbk -*-

import math
from typing import List

class JumpSearch:
    def search(self, nums: List[int], target: int) -> int:
        step = int(math.sqrt(len(nums)))
        border = step
        while border < len(nums) and target > nums[border]:
            border += step

        for i, value in enumerate(nums[border - step : min(border + 1, len(nums))]):
            if target == value:
                return border - step + i
        return -1
