#!/usr/bin/env python
# -*- coding:gbk -*-

class BloomFilter:
    def __init__(self):
        self.__seeds, self.__hash = [2, 3, 5], [0x00 for _ in range(65536)]

    def isEmpty(self) -> bool:
        for value in self.__hash:
            if value:
                return False
        return True

    def add(self, text: str) -> None:
        for seed in self.__seeds:
            value = self.__getHashCode(text, seed)
            index = value >> 3
            if index >= 0 and index < 65536:
                self.__hash[index] |= 1 << (value & 7)

    def contains(self, text: str) -> bool:
        for seed in self.__seeds:
            value = self.__getHashCode(text, seed)
            index = value >> 3
            if index < 0 or index >= 65536 or not (self.__hash[index] & (1 << (value & 7))):
                return False
        return True

    def clear(self) -> None:
        self.__hash = [0x00 for _ in range(65536)]

    def __getHashCode(self, text: str, seed: int) -> int:
        code = 0
        for value in text:
            code = code * seed + ord(value) - ord('a')
        return code
