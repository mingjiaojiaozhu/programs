#!/usr/bin/env python
# -*- coding:gbk -*-

import sys

class QueueOfArray:
    def __init__(self):
        self.__values, self.__head, self.__tail, self.__capacity = [0 for _ in range(64)], 0, 0, 64

    def isEmpty(self) -> bool:
        return self.__head == self.__tail

    def enqueue(self, value: int) -> None:
        if (self.__tail + 1) % self.__capacity == self.__head:
            aux = [0 for _ in range(self.__capacity + 16)]
            if self.__head < self.__tail:
                aux[ : self.__tail - self.__head] = self.__values[self.__head : self.__tail]
            else:
                aux[ : self.__capacity - self.__head] = self.__values[self.__head : self.__capacity]
                aux[self.__capacity - self.__head : self.__capacity - self.__head + self.__tail] = self.__values[ : self.__tail]
            self.__values, self.__head, self.__tail = aux, 0, self.__capacity - 1
            self.__capacity += 16

        self.__values[self.__tail] = value
        self.__tail = (self.__tail + 1) % self.__capacity

    def dequeue(self) -> int:
        if self.__head != self.__tail:
            value = self.__values[self.__head]
            self.__head = (self.__head + 1) % self.__capacity
            return value
        return -sys.maxsize

    def clear(self) -> None:
        self.__values, self.__head, self.__tail = [0 for _ in range(self.__capacity)], 0, 0
