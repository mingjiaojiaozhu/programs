#include <iostream>
#include <vector>
using namespace std;

class Strassen {
public:
    vector<vector<int>> multiply(vector<vector<int>> &matrix1, vector<vector<int>> &matrix2) {
        int length = matrix1.size();
        if (1 == length) {
            return vector<vector<int>>(1, vector<int>(1, matrix1[0][0] * matrix2[0][0]));
        }

        int halfSize = (length & (length - 1)) ? (length >> 1) + 1 : length >> 1;
        vector<vector<int>> matrix1TopLeft(0);
        vector<vector<int>> matrix1TopRight(0);
        vector<vector<int>> matrix1BottomLeft(0);
        vector<vector<int>> matrix1BottomRight(0);
        split(matrix1, matrix1TopLeft, matrix1TopRight, matrix1BottomLeft, matrix1BottomRight, length, halfSize);
        vector<vector<int>> matrix2TopLeft(0);
        vector<vector<int>> matrix2TopRight(0);
        vector<vector<int>> matrix2BottomLeft(0);
        vector<vector<int>> matrix2BottomRight(0);
        split(matrix2, matrix2TopLeft, matrix2TopRight, matrix2BottomLeft, matrix2BottomRight, length, halfSize);

        vector<vector<int>> aux1 = multiply(add(matrix1TopLeft, matrix1BottomRight, halfSize), add(matrix2TopLeft, matrix2BottomRight, halfSize));
        vector<vector<int>> aux2 = multiply(add(matrix1BottomLeft, matrix1BottomRight, halfSize), matrix2TopLeft);
        vector<vector<int>> aux3 = multiply(matrix1TopLeft, subtract(matrix2TopRight, matrix2BottomRight, halfSize));
        vector<vector<int>> aux4 = multiply(matrix1BottomRight, subtract(matrix2BottomLeft, matrix2TopLeft, halfSize));
        vector<vector<int>> aux5 = multiply(add(matrix1TopLeft, matrix1TopRight, halfSize), matrix2BottomRight);
        vector<vector<int>> aux6 = multiply(subtract(matrix1BottomLeft, matrix1TopLeft, halfSize), add(matrix2TopLeft, matrix2TopRight, halfSize));
        vector<vector<int>> aux7 = multiply(subtract(matrix1TopRight, matrix1BottomRight, halfSize), add(matrix2BottomLeft, matrix2BottomRight, halfSize));

        vector<vector<int>> resultTopLeft = add(subtract(add(aux1, aux4, halfSize), aux5, halfSize), aux7, halfSize);
        vector<vector<int>> resultTopRight = add(aux3, aux5, halfSize);
        vector<vector<int>> resultBottomLeft = add(aux2, aux4, halfSize);
        vector<vector<int>> resultBottomRight = add(add(subtract(aux1, aux2, halfSize), aux3, halfSize), aux6, halfSize);
        return merge(resultTopLeft, resultTopRight, resultBottomLeft, resultBottomRight, length, halfSize);
    }

private:
    vector<vector<int>> add(vector<vector<int>> &matrix1, vector<vector<int>> &matrix2, int length) {
        vector<vector<int>> result(0);
        for (int i = 0; i < length; ++i) {
            result.emplace_back(vector<int>(matrix1[i].begin(), matrix1[i].end()));
            for (int j = 0; j < length; ++j) {
                result[i][j] += matrix2[i][j];
            }
        }
        return result;
    }

    vector<vector<int>> subtract(vector<vector<int>> &matrix1, vector<vector<int>> &matrix2, int length) {
        vector<vector<int>> result(0);
        for (int i = 0; i < length; ++i) {
            result.emplace_back(vector<int>(matrix1[i].begin(), matrix1[i].end()));
            for (int j = 0; j < length; ++j) {
                result[i][j] -= matrix2[i][j];
            }
        }
        return result;
    }

    void split(vector<vector<int>> &matrix, vector<vector<int>> &matrixTopLeft, vector<vector<int>> &matrixTopRight, vector<vector<int>> &matrixBottomLeft, vector<vector<int>> &matrixBottomRight, int length, int halfSize) {
        for (int i = 0; i < halfSize - 1; ++i) {
            matrixTopLeft.emplace_back(vector<int>(matrix[i].begin(), matrix[i].begin() + halfSize));
            matrixTopRight.emplace_back(vector<int>(matrix[i].begin() + halfSize, matrix[i].end()));
            matrixBottomLeft.emplace_back(vector<int>(matrix[halfSize + i].begin(), matrix[halfSize + i].begin() + halfSize));
            matrixBottomRight.emplace_back(vector<int>(matrix[halfSize + i].begin() + halfSize, matrix[halfSize + i].end()));
            if (length & (length - 1)) {
                matrixTopRight[i].emplace_back(0);
                matrixBottomRight[i].emplace_back(0);
            }
        }

        matrixTopLeft.emplace_back(vector<int>(matrix[halfSize - 1].begin(), matrix[halfSize - 1].begin() + halfSize));
        matrixTopRight.emplace_back(vector<int>(matrix[halfSize - 1].begin() + halfSize, matrix[halfSize - 1].end()));
        if (length & (length - 1)) {
            matrixTopRight[halfSize - 1].emplace_back(0);
            matrixBottomLeft.emplace_back(vector<int>(halfSize, 0));
            matrixBottomRight.emplace_back(vector<int>(halfSize, 0));
        } else {
            matrixBottomLeft.emplace_back(vector<int>(matrix[length - 1].begin(), matrix[length - 1].begin() + halfSize));
            matrixBottomRight.emplace_back(vector<int>(matrix[length - 1].begin() + halfSize, matrix[length - 1].end()));
        }
    }

    vector<vector<int>> merge(vector<vector<int>> &matrixTopLeft, vector<vector<int>> &matrixTopRight, vector<vector<int>> &matrixBottomLeft, vector<vector<int>> &matrixBottomRight, int length, int halfSize) {
        vector<vector<int>> result(length, vector<int>(length, 0));
        for (int i = 0; i < halfSize - 1; ++i) {
            copy(matrixTopLeft[i].begin(), matrixTopLeft[i].end(), result[i].begin());
            copy(matrixTopRight[i].begin(), matrixTopRight[i].end(), result[i].begin() + halfSize);
            copy(matrixBottomLeft[i].begin(), matrixBottomLeft[i].end(), result[halfSize + i].begin());
            copy(matrixBottomRight[i].begin(), matrixBottomRight[i].end(), result[halfSize + i].begin() + halfSize);
        }
        copy(matrixTopLeft[halfSize - 1].begin(), matrixTopLeft[halfSize - 1].end(), result[halfSize - 1].begin());
        copy(matrixTopRight[halfSize - 1].begin(), matrixTopRight[halfSize - 1].end(), result[halfSize - 1].begin() + halfSize);
        if (!(length & (length - 1))) {
            copy(matrixBottomLeft[halfSize - 1].begin(), matrixBottomLeft[halfSize - 1].end(), result[length - 1].begin());
            copy(matrixBottomRight[halfSize - 1].begin(), matrixBottomRight[halfSize - 1].end(), result[length - 1].begin() + halfSize);
        }
        return result;
    }
};
