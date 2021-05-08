#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class RPN:
    def converse(self, values: List[str]) -> List[str]:
        stack, result = [], []
        for value in values:
            if '(' == value:
                stack.append(value)
                continue

            if ')' == value:
                while stack:
                    sign = stack.pop()
                    if '(' == sign:
                        break
                    result.append(sign)
                continue

            if '+' != value and '-' != value and '*' != value and '/' != value:
                result.append(value)
                continue

            while stack:
                sign = stack[-1]
                if '(' == sign or (('*' == value or '/' == value) and ('+' == sign or '-' == sign)):
                    break
                result.append(sign)
                stack.pop()
            stack.append(value)

        while stack:
            result.append(stack.pop())
        return result

    def evaluate(self, values: List[str]) -> int:
        stack = []
        for value in values:
            if '+' != value and '-' != value and '*' != value and '/' != value:
                stack.append(int(value))
                continue

            num1, num2 = stack.pop(), stack.pop()
            if '+' == value:
                stack.append(num2 + num1)
            elif '-' == value:
                stack.append(num2 - num1)
            elif '*' == value:
                stack.append(num2 * num1)
            else:
                stack.append(num2 // num1)
        return stack[0]
