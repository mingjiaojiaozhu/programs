#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class Karatsuba:
    def multiply(self, num1: str, num2: str) -> str:
        length = max(len(num1), len(num2))
        if length <= 4:
            return str(int(num1) * int(num2))

        if length > len(num1):
            num1 = self.__fillHead(num1, length - len(num1))
        if length > len(num2):
            num2 = self.__fillHead(num2, length - len(num2))

        halfSize = length >> 1
        num1Head, num1Tail, num2Head, num2Tail = num1[ : halfSize], num1[halfSize : ], num2[ : halfSize], num2[halfSize : ]
        aux1, aux2 = self.multiply(num1Head, num2Head), self.multiply(num1Tail, num2Tail)
        return self.__add(self.__add(self.__fillTail(aux1, (length - halfSize) << 1), self.__fillTail(self.__subtract(self.multiply(self.__add(num1Head, num1Tail), self.__add(num2Head, num2Tail)), self.__add(aux1, aux2)), length - halfSize)), aux2)

    def __add(self, num1: str, num2: str) -> str:
        values1, values2 = self.__stringToArrays(num1), self.__stringToArrays(num2)

        result = [0 for _ in range(max(len(values1), len(values2)) + 1)]
        result[ : len(values1)] = values1[ : ]
        for i, value in enumerate(values2):
            result[i] += value
            if result[i] >= 10:
                result[i] -= 10
                result[i + 1] += 1

        index = len(values2)
        while index < len(values1) - 1 and result[index] >= 10:
            result[index] -= 10
            result[index + 1] += 1
            index += 1
        return self.__arraysToString(result)

    def __subtract(self, num1: str, num2: str) -> str:
        values1, values2 = self.__stringToArrays(num1), self.__stringToArrays(num2)
        for i, value in enumerate(values2):
            values1[i] -= value
            if values1[i] < 0:
                values1[i] += 10
                values1[i + 1] -= 1

        index = len(values2)
        while index < len(values1) - 1 and values1[index] < 0:
            values1[index] += 10
            values1[index + 1] -= 1
            index += 1
        return self.__arraysToString(values1)

    def __fillHead(self, num: str, length: int) -> str:
        return ('0' * length) + num

    def __fillTail(self, num: str, length: int) -> str:
        return num + ('0' * length)

    def __stringToArrays(self, num: str) -> List[int]:
        result = []
        for value in num:
            result.append(int(value))
        result.reverse()
        return result

    def __arraysToString(self, values: List[int]) -> str:
        values.reverse()
        index = 0
        while index < len(values) - 1 and not values[index]:
            index += 1

        result = ''
        for value in values[index : ]:
            result += str(value)
        return result
