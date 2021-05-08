#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class LSDRadixSort:
    def sort(self, texts: List[str]) -> None:
        aux = ['' for _ in range(len(texts))]
        for i in range(len(texts[0]) - 1, -1, -1):
            maxValue, minValue = ord(texts[0][i]), ord(texts[0][i])
            for text in texts[1 : ]:
                value = ord(text[i])
                if not ~value:
                    continue

                if maxValue < value:
                    maxValue = value
                if not ~minValue or minValue > value:
                    minValue = value

            size = maxValue - minValue + 1
            buckets = [0 for _ in range(size)]
            for text in texts:
                buckets[ord(text[i]) - minValue] += 1
            for j in range(1, size):
                buckets[j] += buckets[j - 1]

            for text in texts[ : : -1]:
                index = ord(text[i]) - minValue
                aux[buckets[index] - 1] = text
                buckets[index] -= 1
            texts[ : ] = aux[ : ]
