#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class BoyerMoore:
    def search(self, text: str, pattern: str) -> int:
        maxValue, minValue = ord(max(text)), ord(min(text))
        nextBadChar, nextGoodSuffix = self.__getNextBadChar(pattern, maxValue - minValue + 1, minValue), self.__getNextGoodSuffix(pattern)

        index = 0
        while index <= len(text) - len(pattern):
            patternIndex = len(pattern) - 1
            while text[index + patternIndex] == pattern[patternIndex]:
                patternIndex -= 1
                if patternIndex < 0:
                    return index
            index += max(patternIndex - nextBadChar[ord(text[index + patternIndex]) - minValue], nextGoodSuffix[patternIndex])
        return -1

    def __getNextBadChar(self, text: str, nextSize: int, minValue: int) -> List[int]:
        next = [0 for _ in range(nextSize)]
        for i, value in enumerate(text):
            index = ord(value) - minValue
            if index >= 0 and index < nextSize:
                next[index] = i
        return next

    def __getNextGoodSuffix(self, text: str) -> List[int]:
        aux = [0 for _ in range(len(text))]
        aux[-1] = len(text)

        start, end = 0, len(text) - 1
        for i in range(len(text) - 2, -1, -1):
            if i > end and aux[i - 1 - start] < i - end:
                aux[i] = aux[i - 1 - start]
                continue

            if i < end:
                end = i
            start = i
            while end >= 0 and text[end] == text[end - 1 - start]:
                end -= 1
                aux[i] = start - end

        next = [len(text) for _ in range(len(text))]
        for i in range(len(text) - 1, -1, -1):
            if aux[i] != i + 1:
                continue

            for j in range(len(text) - i):
                if next[j] == len(text):
                    next[j] = len(text) - i - 1

        for i in range(len(text) - 1):
            next[-1 - aux[i]] = len(text) - i - 1
        return next
