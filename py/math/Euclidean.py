#!/usr/bin/env python
# -*- coding:gbk -*-

class Euclidean:
    def gcd(self, num1: int, num2: int) -> int:
        return num1 if not num2 else self.gcd(num2, num1 % num2)

    def lcm(self, num1: int, num2: int) -> int:
        return num1 // self.gcd(num1, num2) * num2
