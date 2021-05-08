#!/usr/bin/env python
# -*- coding:gbk -*-

class BruteForce:
    def search(self, text: str, pattern: str) -> int:
        index, patternIndex = 0, 0
        while index < len(text):
            if text[index] != pattern[patternIndex]:
                index += 1 - patternIndex
                patternIndex = 0
                continue

            if patternIndex == len(pattern) - 1:
                return index - patternIndex
            index += 1
            patternIndex += 1
        return -1
