#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class Sunday:
    def search(self, text: str, pattern: str) -> int:
        maxValue, minValue = ord(max(text)), ord(min(text))
        next = self.__getNext(pattern, maxValue - minValue + 1, minValue)

        index = 0
        while index <= len(text) - len(pattern):
            patternIndex = 0
            while text[index + patternIndex] == pattern[patternIndex]:
                patternIndex += 1
                if patternIndex == len(pattern):
                    return index

            if index == len(text) - len(pattern):
                return -1
            index += next[ord(text[index + len(pattern)]) - minValue]
        return -1

    def __getNext(self, text: str, nextSize: int, minValue: int) -> List[int]:
        next = [len(text) + 1 for _ in range(nextSize)]
        for i, value in enumerate(text):
            index = ord(value) - minValue
            if index >= 0 and index < nextSize:
                next[index] = len(text) - i
        return next
