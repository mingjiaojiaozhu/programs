#!/usr/bin/env python
# -*- coding:gbk -*-

import functools, sys
from typing import List

class ClosestPairOfPoints:
    def solution(self, points: List[List[int]]) -> List[List[int]]:
        result = [[] for _ in range(2)]
        self.__match(points, result)
        return result

    def __match(self, points: List[List[int]], result: List[List[int]]) -> int:
        length = len(points)
        if length < 2:
            return sys.maxsize
        if 2 == length:
            result[0], result[1] = points[0], points[1]
            return self.__getDistance(points[0], points[1])

        points.sort(key = functools.cmp_to_key(self.__cmpOfX))

        halfSize = length >> 1
        left, aux1 = points[ : halfSize], [[] for _ in range(2)]
        distance1 = self.__match(left, aux1)

        right, aux2 = points[halfSize : ], [[] for _ in range(2)]
        distance2 = self.__match(right, aux2)

        minDistance = min(distance1, distance2)
        if distance1 < distance2:
            result[0], result[1] = aux1[0], aux1[1]
        else:
            result[0], result[1] = aux2[0], aux2[1]

        border1, border2 = self.__getBorder(left, 0, points[halfSize][0] - minDistance), self.__getBorder(right, 0, points[halfSize][0] + minDistance)
        if border1 == len(left) or not border2:
            return minDistance

        aux = right[ : border2]
        aux.sort(key = functools.cmp_to_key(self.__cmpOfY))

        for point1 in left[border1 : ]:
            start, end = self.__getBorder(aux, 1, point1[1] - minDistance), self.__getBorder(aux, 1, point1[1] + minDistance)
            for point2 in aux[start : end]:
                distance = self.__getDistance(point1, point2)
                if minDistance > distance:
                    result[0], result[1], minDistance = point1, point2, distance
        return minDistance

    def __getBorder(self, points: List[List[int]], index: int, target: int) -> int:
        start, end = 0, len(points) - 1
        while start <= end:
            middle = start + ((end - start) >> 1)
            if target < points[middle][index]:
                end = middle - 1
            else:
                start = middle + 1
        return start

    def __getDistance(self, point1: List[int], point2: List[int]) -> int:
        return abs(point2[0] - point1[0]) + abs(point2[1] - point1[1])

    def __cmpOfX(self, node1: List[int], node2: List[int]) -> int:
        return node1[0] - node2[0]

    def __cmpOfY(self, node1: List[int], node2: List[int]) -> int:
        return node1[1] - node2[1]
