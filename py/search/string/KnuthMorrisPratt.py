#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class KnuthMorrisPratt:
    def search(self, text: str, pattern: str) -> int:
        next = self.__getNext(pattern)

        index, patternIndex = 0, 0
        while index < len(text):
            if patternIndex > 0 and text[index] != pattern[patternIndex]:
                index += 1
                patternIndex = next[patternIndex - 1]
                continue

            if patternIndex == len(pattern) - 1:
                return index - patternIndex
            index += 1
            patternIndex += 1
        return -1

    def __getNext(self, text: str) -> List[int]:
        next = [0 for _ in range(len(text))]
        fast, slow = 1, 0
        while fast < len(text):
            if slow and text[fast] != text[slow]:
                slow = next[slow - 1]
                continue

            if text[fast] == text[slow]:
                slow += 1
            next[fast] = slow
            fast += 1
        return next
