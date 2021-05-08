#!/usr/bin/env python
# -*- coding:gbk -*-

import functools
from typing import List

class KnapsackOfFractional:
    def solution(self, weights: List[int], values: List[int], target: int) -> int:
        goods = []
        for weight, value in zip(weights, values):
            goods.append(self.__GoodNode(weight, value))

        goods.sort(key = functools.cmp_to_key(self.__cmp))

        result = 0
        for good in goods:
            if target < good.weight:
                return result + target * good.value // good.weight

            target -= good.weight
            result += good.value
        return result

    def __cmp(self, node1: '__GoodNode', node2: '__GoodNode') -> int:
        return 1 if node1.rate < node2.rate else -1

    class __GoodNode:
        def __init__(self, weight: int, value: int):
            self.weight, self.value, self.rate = weight, value, value / weight
