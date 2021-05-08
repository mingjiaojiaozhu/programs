#!/usr/bin/env python
# -*- coding:gbk -*-

class LongestPalindromicSubstring:
    def solution(self, text: str) -> str:
        aux = [[False for _ in range(len(text))] for _ in range(len(text))]
        for i in range(len(text)):
            aux[i][i] = True

        start, size = 0, 1
        for i in range(1, len(text)):
            for j in range(len(text) - i):
                index = i + j
                aux[j][index] = text[j] == text[index] if 1 == i else text[j] == text[index] and aux[j + 1][index - 1]
                if aux[j][index] and size < i + 1:
                    start, size = j, i + 1
        return text[start : start + size]
