#!/usr/bin/env python
# -*- coding:gbk -*-

import sys
from typing import List

class EdgeNode:
    def __init__(self, index: int, weight: int, price: int):
        self.index, self.weight, self.price, self.next = index, weight, price, None

class VertexNode:
    def __init__(self, value: int):
        self.value, self.next = value, None

class Dinic:
    def search(self, graphs: List[VertexNode], start: int, end: int) -> List[int]:
        weights = [[0 for _ in range(len(graphs))] for _ in range(len(graphs))]
        for i, value in enumerate(graphs):
            edge = value.next
            while edge:
                weights[i][edge.index] = edge.weight
                edge = edge.next

        minCost, visited, result = [], [False for _ in range(len(graphs))], [0 for _ in range(2)]
        while self.__searchOfBFS(graphs, start, end, weights, minCost):
            visited[end] = True
            while visited[end]:
                visited[ : ] = [False for _ in range(len(graphs))]
                self.__searchOfDFS(graphs, start, end, sys.maxsize, weights, minCost, visited, result)
        return result

    def __searchOfBFS(self, graphs: List[VertexNode], start: int, end: int, weights: List[List[int]], minCost: List[int]) -> bool:
        minCost[ : ] = [sys.maxsize for _ in range(len(graphs))]
        minCost[start] = 0

        visited, queue = [False for _ in range(len(graphs))], [start]
        visited[start] = True
        while queue:
            index = queue.pop(0)
            visited[index], edge = False, graphs[index].next
            while edge:
                edgeIndex = edge.index
                if weights[index][edgeIndex] and minCost[edgeIndex] > minCost[index] + edge.price:
                    minCost[edgeIndex] = minCost[index] + edge.price
                    if not visited[edgeIndex]:
                        visited[edgeIndex] = True
                        queue.append(edgeIndex)
                edge = edge.next
        return sys.maxsize != minCost[end]

    def __searchOfDFS(self, graphs: List[VertexNode], start: int, end: int, flow: int, weights: List[List[int]], minCost: List[int], visited: List[bool], result: List[int]) -> int:
        if start == end:
            visited[end] = True
            result[0] += flow
            return flow

        visited[start], edge, pivot = True, graphs[start].next, 0
        while edge:
            edgeIndex = edge.index
            if (not visited[edgeIndex] or edgeIndex == end) and weights[start][edgeIndex] and minCost[edgeIndex] == minCost[start] + edge.price:
                value = self.__searchOfDFS(graphs, edgeIndex, end, min(flow - pivot, weights[start][edgeIndex]), weights, minCost, visited, result)
                if value:
                    pivot += value
                    result[1] += value * edge.price
                    weights[start][edgeIndex] -= value
                    weights[edgeIndex][start] += value
                    if pivot == flow:
                        break
            edge = edge.next
        return pivot
