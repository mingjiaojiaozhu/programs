#!/usr/bin/env python
# -*- coding:gbk -*-

class LongestCommonSubsequence:
    def solution(self, text1: str, text2: str) -> int:
        result = [[0 for _ in range(len(text2) + 1)] for _ in range(len(text1) + 1)]
        for i in range(1, len(text1) + 1):
            for j in range(1, len(text2) + 1):
                result[i][j] = result[i - 1][j - 1] + 1 if text1[i - 1] == text2[j - 1] else max(result[i - 1][j], result[i][j - 1])
        return result[-1][-1]
