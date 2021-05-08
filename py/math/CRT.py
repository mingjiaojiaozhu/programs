#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class CRT:
    def solution(self, values: List[List[int]]) -> int:
        total = 1
        for value in values:
            total *= value[0]

        result = 0
        for value in values:
            lcm = total // value[0]
            result = (result + lcm // self.__gcd(lcm, value[0])[0] * value[1]) % total
        return (result + total) % total

    def __gcd(self, num1: int, num2: int) -> List[int]:
        if not num2:
            return [1, 0]

        result = self.__gcd(num2, num1 % num2)
        result[0], result[1] = result[1], result[0] - result[1] * (num1 // num2)
        return result
