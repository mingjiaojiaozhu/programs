#!/usr/bin/env python
# -*- coding:gbk -*-

import sys, time

class SnowFlake:
    def __init__(self, dataCenterId: int, workerId: int):
        self.__startTimeStamp = 1356019200000
        self.__timeStamp, self.__dataCenterId, self.__workerId, self.__sequence = 0, dataCenterId, workerId, 0

    def uuid(self) -> int:
        tick = int(time.time() * 1000)
        if tick < self.__timeStamp:
            return -sys.maxsize

        if tick == self.__timeStamp:
            self.__sequence = (self.__sequence + 1) & (~(-1 << 12))
            if not self.__sequence:
                while tick == self.__timeStamp:
                    tick = int(time.time() * 1000)
        else:
            self.__sequence = 0
        self.__timeStamp = tick
        return ((tick - self.__startTimeStamp) << 22) | (self.__dataCenterId << 17) | (self.__workerId << 12) | self.__sequence
