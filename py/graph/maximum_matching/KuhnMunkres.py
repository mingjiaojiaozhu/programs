#!/usr/bin/env python
# -*- coding:gbk -*-

import sys
from typing import List

class KuhnMunkres:
    def search(self, graphs: List[List[int]]) -> List[int]:
        weights = [[0 for _ in range(len(graphs))], [max(_) for _ in graphs], [sys.maxsize for _ in range(len(graphs))]]
        result = [-1 for _ in range(len(graphs))]
        for i in range(len(graphs)):
            weights[2] = [sys.maxsize for _ in range(len(graphs))]
            while True:
                visited = [[False for _ in range(len(graphs))] for _ in range(2)]
                if self.__search(graphs, i, result, visited, weights):
                    break

                weight = sys.maxsize
                for j, value in enumerate(weights[2]):
                    if not visited[0][j] and weight > value:
                        weight = value

                for j in range(len(graphs)):
                    if visited[1][j]:
                        weights[1][j] -= weight

                    if visited[0][j]:
                        weights[0][j] += weight
                    else:
                        weights[2][j] -= weight
        return result

    def __search(self, graphs: List[List[int]], start: int, result: List[int], visited: List[List[bool]], weights: List[List[int]]) -> bool:
        visited[1][start] = True
        for i in range(len(graphs)):
            if visited[0][i]:
                continue

            weight = weights[1][start] + weights[0][i] - graphs[start][i]
            if not weight:
                visited[0][i] = True
                if not ~result[i] or self.__search(graphs, result[i], result, visited, weights):
                    result[i] = start
                    return True
            else:
                if weights[2][i] > weight:
                    weights[2][i] = weight
        return False
