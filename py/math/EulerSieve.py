#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class EulerSieve:
    def sieve(self, num: int) -> List[int]:
        isPrime, result = [True for _ in range(num)], []
        for i in range(2, num + 1):
            if isPrime[i - 1]:
                result.append(i)

            for value in result:
                if value > num // i:
                    break

                isPrime[i * value - 1] = False
                if not (i % value):
                    break
        return result
