#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class BigInteger:
    def add(self, num1: str, num2: str) -> str:
        result, carry = '', 0
        for i in range(1, max(len(num1), len(num2)) + 1):
            value1, value2 = ord(num1[-1 * i]) - ord('0') if i <= len(num1) else 0, ord(num2[-1 * i]) - ord('0') if i <= len(num2) else 0
            value = value1 + value2 + carry
            carry = value // 10
            result += str(value % 10)
        if carry:
            result += str(carry)
        return result[ : : -1]

    def subtract(self, num1: str, num2: str) -> str:
        if not self.__greater(num1, num2):
            return '-' + self.subtract(num2, num1)

        result, borrow = '', 0
        for i in range(1, len(num1) + 1):
            value1, value2 = ord(num1[-1 * i]) - ord('0'), ord(num2[-1 * i]) - ord('0') if i <= len(num2) else 0
            value = value1 - value2 - borrow
            borrow = 0
            if value < 0:
                value += 10
                borrow = 1
            result += str(value)

        index = len(result) - 1
        while index > 0 and '0' == result[index]:
            index -= 1
        return result[index : : -1]

    def multiply(self, num1: str, num2: str) -> str:
        values = [0 for _ in range(len(num1) + len(num2))]
        for i, value1 in enumerate(num1[ : : -1]):
            for j, value2 in enumerate(num2[ : : -1]):
                value, index = (ord(value1) - ord('0')) * (ord(value2) - ord('0')), i + j
                self.__addValues(values, index, value % 10)
                self.__addValues(values, index + 1, value // 10)

        index = len(values) - 1
        while index > 0 and 0 == values[index]:
            index -= 1
        result = ''
        for value in values[index : : -1]:
            result += str(value)
        return result

    def divide(self, num1: str, num2: str) -> List[str]:
        result = ['0' for _ in range(2)]
        while self.__greater(num1, num2):
            diff = len(num1) - len(num2)
            aux1, aux2 = self.__fillTail(num2, diff), self.__fillTail('1', diff)
            if not self.__greater(num1, aux1):
                aux1, aux2 = aux1[ : -1], aux2[ : -1]
            while self.__greater(num1, aux1):
                num1, result[0] = self.subtract(num1, aux1), self.add(result[0], aux2)
        result[1] = num1
        return result

    def __addValues(self, values: List[int], index: int, value: int) -> None:
        values[index] += value
        if values[index] > 9:
            values[index] -= 10
            values[index + 1] += 1

    def __greater(self, num1: str, num2: str) -> bool:
        if len(num1) != len(num2):
            return len(num1) > len(num2)
        return num1 >= num2

    def __fillTail(self, num: str, length: int) -> str:
        return num + ('0' * length)
