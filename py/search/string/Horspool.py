#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class Horspool:
    def search(self, text: str, pattern: str) -> int:
        maxValue, minValue = ord(max(text)), ord(min(text))
        next = self.__getNext(pattern, maxValue - minValue + 1, minValue)

        index = 0
        while index <= len(text) - len(pattern):
            patternIndex = len(pattern) - 1
            while text[index + patternIndex] == pattern[patternIndex]:
                patternIndex -= 1
                if patternIndex < 0:
                    return index
            index += next[ord(text[index + len(pattern) - 1]) - minValue]
        return -1

    def __getNext(self, text: str, nextSize: int, minValue: int) -> List[int]:
        next = [len(text) for _ in range(nextSize)]
        for i, value in enumerate(text[ : -1]):
            index = ord(value) - minValue
            if index >= 0 and index < nextSize:
                next[index] = len(text) - i - 1
        return next
