#!/usr/bin/env python
# -*- coding:gbk -*-

class RabinMiller:
    def __init__(self):
        self.__primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29]

    def isPrime(self, num: int) -> bool:
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
