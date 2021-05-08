#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class EdgeNode:
    def __init__(self, index: int, weight: int):
        self.index, self.weight, self.next = index, weight, None

class VertexNode:
    def __init__(self, value: int):
        self.value, self.next = value, None

class Gabow:
    def search(self, graphs: List[VertexNode]) -> List[List[int]]:
        parent, visited, path, root = [-1 for _ in range(len(graphs))], [False for _ in range(len(graphs))], [], []
        result, aux = [], []
        for i in range(len(graphs)):
            if not ~parent[i]:
                self.__search(graphs, i, parent, visited, path, root, result, aux, 0)
        return result

    def __search(self, graphs: List[VertexNode], start: int, parent: List[int], visited: List[bool], path: List[int], root: List[int], result: List[List[int]], aux: List[int], count: int) -> int:
        parent[start] = count
        path.append(start)
        root.append(start)

        edge = graphs[start].next
        while edge:
            edgeIndex = edge.index
            if not ~parent[edgeIndex]:
                count = self.__search(graphs, edgeIndex, parent, visited, path, root, result, aux, count + 1)
            elif not visited[edgeIndex]:
                while parent[root[-1]] > parent[edgeIndex]:
                    root.pop()
            edge = edge.next

        if start != root[-1]:
            return count
        root.pop()

        index = path.pop()
        while index != start:
            aux.append(index)
            visited[index], index = True, path.pop()
        aux.append(start)
        visited[start] = True
        result.append(list(aux))
        aux.clear()
        return count
