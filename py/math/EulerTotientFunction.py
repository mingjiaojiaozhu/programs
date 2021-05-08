#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class EulerTotientFunction:
    def solution(self, num: int) -> List[int]:
        isPrime, primes = [True for _ in range(num)], []
        result = [0 for _ in range(num)]
        for i in range(2, num + 1):
            if isPrime[i - 1]:
                primes.append(i)
                result[i - 1] = i - 1

            for value in primes:
                if value > num // i:
                    break

                isPrime[i * value - 1] = False
                if not (i % value):
                    result[i * value - 1] = result[i - 1] * value
                    break
                else:
                    result[i * value - 1] = result[i - 1] * (value - 1)
        return result
