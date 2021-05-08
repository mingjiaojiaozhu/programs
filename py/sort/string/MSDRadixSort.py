#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class MSDRadixSort:
    def sort(self, texts: List[str]) -> None:
        aux = ['' for _ in range(len(texts))]
        self.__sort(texts, aux, 0, len(texts) - 1, 0)

    def __sort(self, texts: List[str], aux: List[str], start: int, end: int, digit: int) -> None:
        if start >= end:
            return

        maxValue, minValue = self.__getChar(texts[start], digit), self.__getChar(texts[start], digit)
        for text in texts[start + 1 : end + 1]:
            value = self.__getChar(text, digit)
            if not ~value:
                continue

            if maxValue < value:
                maxValue = value
            if not ~minValue or minValue > value:
                minValue = value

        size = maxValue - minValue + 1
        buckets = [0 for _ in range(size + 2)]
        for text in texts[start : end + 1]:
            value = self.__getChar(text, digit)
            buckets[1 if not ~value else value - minValue + 2] += 1
        for i in range(1, size + 2):
            buckets[i] += buckets[i - 1]

        for text in texts[start : end + 1]:
            value = self.__getChar(text, digit)
            index = 0 if not ~value else value - minValue + 1
            aux[buckets[index]] = text
            buckets[index] += 1
        texts[start : end + 1] = aux[ : end - start + 1]

        for i in range(size):
            self.__sort(texts, aux, start + buckets[i], start + buckets[i + 1] - 1, digit + 1)

    def __getChar(self, text: str, digit: int) -> int:
        if len(text) <= digit:
            return -1
        return ord(text[digit])
