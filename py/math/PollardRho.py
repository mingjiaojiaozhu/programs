#!/usr/bin/env python
# -*- coding:gbk -*-

import random
from typing import List

class PollardRho:
    def __init__(self):
        self.__primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29]

    def solution(self, num: int) -> List[int]:
        result = []
        if num > 1:
            self.__factorization(num, 256, result)
        result.sort()
        return result

    def __factorization(self, num: int, aux: int, result: List[int]) -> None:
        if self.__isPrime(num):
            result.append(num)
            return

        factor = num
        while factor >= num:
            factor = self.__getFactor(factor, aux - 1)
            aux -= 1
        self.__factorization(factor, aux, result)
        self.__factorization(num // factor, aux, result)

    def __isPrime(self, num: int) -> bool:
        if num in self.__primes:
            return True
        if num < 2 or not num & 1:
            return False

        base, index = num - 1, 0
        while not base & 1:
            base >>= 1
            index += 1

        for value in self.__primes:
            if self.__check(value, num, base, index):
                return False
        return True

    def __getFactor(self, num: int, aux: int) -> int:
        pivot = random.randrange(1, num - 1)
        value, index, base = (self.__multiplyMod(pivot, pivot, num) + aux) % num, 1, 2
        while value != pivot:
            factor = self.__gcd(pivot - value, num)
            if factor > 1 and factor < num:
                return factor

            index += 1
            if index == base:
                pivot = value
                base <<= 1
            value = (self.__multiplyMod(value, value, num) + aux) % num
        return num

    def __check(self, factor: int, num: int, base: int, index: int) -> bool:
        pivot = self.__powerMod(factor, base, num)
        if 1 == pivot:
            return False

        while index:
            value = self.__multiplyMod(pivot, pivot, num)
            if 1 == value and 1 != pivot and pivot != num - 1:
                return True
            pivot = value
            index -= 1
        return 1 != pivot

    def __powerMod(self, base: int, index: int, mod: int) -> int:
        base %= mod
        if 1 == index:
            return base

        aux, result = base, 1
        while index:
            if index & 1:
                result = self.__multiplyMod(result, aux, mod)
            aux = self.__multiplyMod(aux, aux, mod)
            index >>= 1
        return result

    def __multiplyMod(self, i: int, j: int, mod: int) -> int:
        i %= mod
        j %= mod
        result = 0
        while j:
            if j & 1:
                result = (result + i) % mod
            i <<= 1
            if i >= mod:
                i %= mod
            j >>= 1
        return result

    def __gcd(self, num1: int, num2: int) -> int:
        return num1 if not num2 else self.__gcd(num2, num1 % num2)
