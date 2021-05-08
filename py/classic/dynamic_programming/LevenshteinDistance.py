#!/usr/bin/env python
# -*- coding:gbk -*-

class LevenshteinDistance:
    def solution(self, text1: str, text2: str) -> int:
        result = [[0 for _ in range(len(text2) + 1)] for _ in range(len(text1) + 1)]
        result[0][1], result[1][0] = 1, 1
        for i in range(len(text1) + 1):
            for j in range(len(text2) + 1):
                value = 0 if text1[i - 1] == text2[j - 1] else 1
                result[i][j] = min(result[i - 1][j] + 1, result[i][j - 1] + 1, result[i - 1][j - 1] + value)
        return result[-1][-1]
