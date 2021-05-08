#!/usr/bin/env python
# -*- coding:gbk -*-

class LongestCommonSubstring:
    def solution(self, text1: str, text2: str) -> int:
        result, maxValue = [[0 for _ in range(len(text2) + 1)] for _ in range(len(text1) + 1)], 0
        for i in range(1, len(text1) + 1):
            for j in range(1, len(text2) + 1):
                result[i][j] = result[i - 1][j - 1] + 1 if text1[i - 1] == text2[j - 1] else 0
                if maxValue < result[i][j]:
                    maxValue = result[i][j]
        return maxValue
