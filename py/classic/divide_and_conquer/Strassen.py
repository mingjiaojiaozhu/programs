#!/usr/bin/env python
# -*- coding:gbk -*-

from typing import List

class Strassen:
    def multiply(self, matrix1: List[List[int]], matrix2: List[List[int]]) -> List[List[int]]:
        length = len(matrix1)
        if 1 == length:
            return [[matrix1[0][0] * matrix2[0][0]]]

        halfSize = (length >> 1) + 1 if length & (length - 1) else length >> 1
        matrix1TopLeft, matrix1TopRight, matrix1BottomLeft, matrix1BottomRight = [], [], [], []
        self.__split(matrix1, matrix1TopLeft, matrix1TopRight, matrix1BottomLeft, matrix1BottomRight, length, halfSize)
        matrix2TopLeft, matrix2TopRight, matrix2BottomLeft, matrix2BottomRight = [], [], [], []
        self.__split(matrix2, matrix2TopLeft, matrix2TopRight, matrix2BottomLeft, matrix2BottomRight, length, halfSize)

        aux1 = self.multiply(self.__add(matrix1TopLeft, matrix1BottomRight, halfSize), self.__add(matrix2TopLeft, matrix2BottomRight, halfSize))
        aux2 = self.multiply(self.__add(matrix1BottomLeft, matrix1BottomRight, halfSize), matrix2TopLeft)
        aux3 = self.multiply(matrix1TopLeft, self.__subtract(matrix2TopRight, matrix2BottomRight, halfSize))
        aux4 = self.multiply(matrix1BottomRight, self.__subtract(matrix2BottomLeft, matrix2TopLeft, halfSize))
        aux5 = self.multiply(self.__add(matrix1TopLeft, matrix1TopRight, halfSize), matrix2BottomRight)
        aux6 = self.multiply(self.__subtract(matrix1BottomLeft, matrix1TopLeft, halfSize), self.__add(matrix2TopLeft, matrix2TopRight, halfSize))
        aux7 = self.multiply(self.__subtract(matrix1TopRight, matrix1BottomRight, halfSize), self.__add(matrix2BottomLeft, matrix2BottomRight, halfSize))

        resultTopLeft = self.__add(self.__subtract(self.__add(aux1, aux4, halfSize), aux5, halfSize), aux7, halfSize)
        resultTopRight = self.__add(aux3, aux5, halfSize)
        resultBottomLeft = self.__add(aux2, aux4, halfSize)
        resultBottomRight = self.__add(self.__add(self.__subtract(aux1, aux2, halfSize), aux3, halfSize), aux6, halfSize)
        return self.__merge(resultTopLeft, resultTopRight, resultBottomLeft, resultBottomRight, length, halfSize)

    def __add(self, matrix1: List[List[int]], matrix2: List[List[int]], length: int) -> List[List[int]]:
        result = []
        for i in range(length):
            result.append(list(matrix1[i]))
            for j in range(length):
                result[i][j] += matrix2[i][j]
        return result

    def __subtract(self, matrix1: List[List[int]], matrix2: List[List[int]], length: int) -> List[List[int]]:
        result = []
        for i in range(length):
            result.append(list(matrix1[i]))
            for j in range(length):
                result[i][j] -= matrix2[i][j]
        return result

    def __split(self, matrix: List[List[int]], matrixTopLeft: List[List[int]], matrixTopRight: List[List[int]], matrixBottomLeft: List[List[int]], matrixBottomRight: List[List[int]], length: int, halfSize: int) -> None:
        for i in range(halfSize - 1):
            matrixTopLeft.append(list(matrix[i][ : halfSize]))
            matrixTopRight.append(list(matrix[i][halfSize : ]))
            matrixBottomLeft.append(list(matrix[halfSize + i][ : halfSize]))
            matrixBottomRight.append(list(matrix[halfSize + i][halfSize : ]))
            if length & (length - 1):
                matrixTopRight[i].append(0)
                matrixBottomRight[i].append(0)

        matrixTopLeft.append(list(matrix[halfSize - 1][ : halfSize]))
        matrixTopRight.append(list(matrix[halfSize - 1][halfSize : ]))
        if length & (length - 1):
            matrixTopRight[halfSize - 1].append(0)
            matrixBottomLeft.append([0 for _ in range(halfSize)])
            matrixBottomRight.append([0 for _ in range(halfSize)])
        else:
            matrixBottomLeft.append(list(matrix[length - 1][ : halfSize]))
            matrixBottomRight.append(list(matrix[length - 1][halfSize : ]))

    def __merge(self, matrixTopLeft: List[List[int]], matrixTopRight: List[List[int]], matrixBottomLeft: List[List[int]], matrixBottomRight: List[List[int]], length: int, halfSize: int) -> List[List[int]]:
        result = [[0 for _ in range(length)] for _ in range(length)]
        for i in range(halfSize - 1):
            result[i][ : halfSize] = matrixTopLeft[i][ : ]
            result[i][halfSize :] = matrixTopRight[i][ : length - halfSize]
            result[halfSize + i][ : halfSize] = matrixBottomLeft[i][ : ]
            result[halfSize + i][halfSize : ] = matrixBottomRight[i][ : length - halfSize]
        result[halfSize - 1][ : halfSize] = matrixTopLeft[halfSize - 1][ : ]
        result[halfSize - 1][halfSize : ] = matrixTopRight[halfSize - 1][: length - halfSize]
        if not (length & (length - 1)):
            result[length - 1][ : halfSize] = matrixBottomLeft[halfSize - 1][ : ]
            result[length - 1][halfSize : ] = matrixBottomRight[halfSize - 1][ : length - halfSize]
        return result
