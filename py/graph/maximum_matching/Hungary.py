#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class Hungary:
    def search(self, graphs: List[List[int]]) -> List[int]:
        result = [-1 for _ in range(len(graphs))]
        for i in range(len(graphs)):
            visited = [False for _ in range(len(graphs))]
            if not self.__search(graphs, i, result, visited):
                return []
        return result

    def __search(self, graphs: List[List[int]], start: int, result: List[int], visited: List[bool]) -> bool:
        for i in range(len(graphs)):
            if graphs[i][start] and not visited[i]:
                visited[i] = True
                if not ~result[i] or self.__search(graphs, result[i], result, visited):
                    result[i] = start
                    return True
        return False
