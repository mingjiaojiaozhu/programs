#!/usr/bin/env python
# -*- coding:gbk -*-

import functools
from typing import List

class ActivitySelection:
    def solution(self, values: List[List[int]]) -> int:
        values.sort(key = functools.cmp_to_key(self.__cmp))

        end, result = values[0][1], 1
        for value in values[1 : ]:
            if end <= value[0]:
                end = value[1]
                result += 1
        return result

    def __cmp(self, node1: List[int], node2: List[int]) -> int:
        return node1[1] - node2[1]
