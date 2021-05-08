#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class EdgeNode:
    def __init__(self, index: int, weight: int):
        self.index, self.weight, self.next = index, weight, None

class VertexNode:
    def __init__(self, value: int):
        self.value, self.next = value, None

class KosarajuSharir:
    def search(self, graphs: List[VertexNode]) -> List[List[int]]:
        visited, stack = [False for _ in range(len(graphs))], []
        self.__search(graphs, 0, visited, stack)

        inverseGraphs = [VertexNode(_.value) for _ in graphs]
        for i in range(len(graphs) - 1, -1, -1):
            edge = graphs[i].next
            while edge:
                edgeIndex, edgeNode = edge.index, EdgeNode(i, edge.weight)
                edgeNode.next, inverseGraphs[edgeIndex].next, edge = inverseGraphs[edgeIndex].next, edgeNode, edge.next

        visited, result, aux = [False for _ in range(len(graphs))], [], []
        while stack:
            index = stack.pop()
            if not visited[index]:
                self.__reverseSearch(inverseGraphs, index, visited, aux)
                result.append(list(aux))
                aux.clear()
        return result

    def __search(self, graphs: List[VertexNode], start: int, visited: List[bool], stack: List[int]) -> None:
        visited[start], edge = True, graphs[start].next
        while edge:
            edgeIndex = edge.index
            if not visited[edgeIndex]:
                self.__search(graphs, edgeIndex, visited, stack)
            edge = edge.next
        stack.append(start)

    def __reverseSearch(self, graphs: List[VertexNode], start: int, visited: List[bool], aux: List[int]) -> None:
        visited[start] = True
        aux.append(start)

        edge = graphs[start].next
        while edge:
            edgeIndex = edge.index
            if not visited[edgeIndex]:
                self.__reverseSearch(graphs, edgeIndex, visited, aux)
            edge = edge.next
