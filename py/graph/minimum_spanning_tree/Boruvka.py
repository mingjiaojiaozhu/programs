#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class EdgeNode:
    def __init__(self, index: int, weight: int):
        self.index, self.weight, self.next = index, weight, None

class VertexNode:
    def __init__(self, value: int):
        self.value, self.next = value, None

class Boruvka:
    def search(self, graphs: List[VertexNode]) -> List[int]:
        edgeLists = []
        for i, value in enumerate(graphs):
            edge = value.next
            while edge:
                edgeLists.append(self.__ConnectedNode(i, edge.index, edge.weight))
                edge = edge.next

        unionFind, result = self.__UnionFind(len(graphs)), [-1 for _ in range(len(graphs))]
        while True:
            minEdges, flag = [None for _ in range(len(graphs))], False
            for edge in edgeLists:
                fromIndex, toIndex = unionFind.values[edge.fromIndex], unionFind.values[edge.toIndex]
                if fromIndex != toIndex and (not minEdges[toIndex] or edge.weight < minEdges[toIndex].weight):
                    minEdges[toIndex], flag = edge, True

            if not flag:
                break

            for edge in minEdges:
                if edge:
                    fromIndex, toIndex = edge.fromIndex, edge.toIndex
                    if unionFind.get(fromIndex) != unionFind.get(toIndex):
                        unionFind.add(fromIndex, toIndex)
                        result[toIndex] = fromIndex
        return result

    class __ConnectedNode:
        def __init__(self, fromIndex: int, toIndex: int, weight: int):
            self.fromIndex, self.toIndex, self.weight = fromIndex, toIndex, weight

    class __UnionFind:
        def __init__(self, degree: int):
            self.values, self.weights = [_ for _ in range(degree)], [1 for _ in range(degree)]

        def add(self, num1: int, num2: int) -> None:
            root1, root2 = self.get(num1), self.get(num2)
            if root1 != root2:
                if self.weights[root1] < self.weights[root2]:
                    self.values[root2] = root1
                    self.weights[root1] += self.weights[root2]
                else:
                    self.values[root1] = root2
                    self.weights[root2] += self.weights[root1]

        def get(self, num: int) -> int:
            root = num
            while root != self.values[root]:
                root = self.values[root]

            while num != root:
                self.values[num], num = root, self.values[num]
            return root
