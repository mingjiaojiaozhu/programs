#!/usr/bin/env python
# -*- coding:gbk -*-

class JosephusRing:
    def solution(self, num: int, interval: int) -> int:
        result = 0
        for i in range(1, num):
            result = (result + interval) % (i + 1)
        return result
