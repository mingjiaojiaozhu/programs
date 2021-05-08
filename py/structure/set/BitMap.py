#!/usr/bin/env python
# -*- coding:gbk -*-

class BitMap:
    def __init__(self):
        self.__hash = [0x00 for _ in range(65536)]

    def isEmpty(self) -> bool:
        for value in self.__hash:
            if value:
                return False
        return True

    def add(self, value: int) -> None:
        index = value >> 3
        if index >= 0 and index < 65536:
            self.__hash[index] |= 1 << (value & 7)

    def erase(self, value: int) -> None:
        index = value >> 3
        if index >= 0 and index < 65536:
            self.__hash[index] &= ~(1 << (value & 7))

    def contains(self, value: int) -> bool:
        index = value >> 3
        if index >= 0 and index < 65536:
            return bool(self.__hash[index] & (1 << (value & 7)))
        return False

    def clear(self) -> None:
        self.__hash = [0x00 for _ in range(65536)]
