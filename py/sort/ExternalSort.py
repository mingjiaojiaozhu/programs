#!/usr/bin/env python
# -*- coding:gbk -*-

import heapq, os
from typing import List

class ExternalSort:
    def sort(self, inFile: str, outFile: str) -> None:
        count = self.__readFile(inFile)
        self.__mergeTempFiles(inFile, outFile, count)
        for i in range(count):
            os.remove(inFile + '-' + str(i))

    def __readFile(self, inFile: str) -> int:
        values, count = [], 0
        with open(inFile, 'r') as handle:
            for line in handle:
                values.append(int(line))
                if len(values) >= 65536:
                    self.__writeTempFiles(values, inFile, count)
                    count += 1

        if values:
            self.__writeTempFiles(values, inFile, count)
            count += 1
        return count

    def __mergeTempFiles(self, inFile: str, outFile: str, count: int) ->None:
        queue = []
        for i in range(count):
            heapq.heappush(queue, self.__HeapNode(inFile, i))

        with open(outFile, 'w') as handle:
            while queue:
                heap = heapq.heappop(queue)
                handle.write(str(heap.value) + '\n')

                line = heap.handle.readline()
                if not line:
                    heap.handle.close()
                else:
                    heap.value = int(line)
                    heapq.heappush(queue, heap)

    def __writeTempFiles(self, values: List[int], inFile: str, index: int) -> None:
        values.sort()

        with open(inFile + '-' + str(index), 'w') as handle:
            for value in values:
                handle.write(str(value) + '\n')
        values.clear()

    class __HeapNode:
        def __init__(self, inFile: str, index: int):
            self.handle = open(inFile + '-' + str(index), 'r')
            self.value = int(self.handle.readline())

        def __lt__(self, other: '__HeapNode'):
            return self.value < other.value
