#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class QuickSort:
    def sort(self, texts: List[str]) -> None:
        self.__sort(texts, 0, len(texts) - 1, 0)

    def __sort(self, texts: List[str], start: int, end: int, digit: int) -> None:
        if start >= end:
            return

        pivot, left, right, index = self.__getChar(texts[start], digit), start, end, start + 1
        while index <= right:
            value = self.__getChar(texts[index], digit)
            if pivot == value:
                index += 1
                continue

            if value < pivot:
                texts[left], texts[index] = texts[index], texts[left]

                index += 1
                left += 1
            else:
                texts[index], texts[right] = texts[right], texts[index]
                right -= 1

        self.__sort(texts, start, left - 1, digit)
        if ~pivot:
            self.__sort(texts, left, right, digit + 1)
        self.__sort(texts, right + 1, end, digit)

    def __getChar(self, text: str, digit: int) -> int:
        if len(text) <= digit:
            return -1
        return ord(text[digit])
