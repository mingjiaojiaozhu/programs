package classic.divide_and_conquer;

import java.util.Arrays;

public class Strassen {
    public int[][] multiply(int[][] matrix1, int[][] matrix2) {
        int length = matrix1.length;
        if (1 == length) {
            return new int[][]{{matrix1[0][0] * matrix2[0][0]}};
        }

        int halfSize = (0 != (length & (length - 1))) ? (length >> 1) + 1 : length >> 1;
        int[][] matrix1TopLeft = new int[halfSize][halfSize];
        int[][] matrix1TopRight = new int[halfSize][halfSize];
        int[][] matrix1BottomLeft = new int[halfSize][halfSize];
        int[][] matrix1BottomRight = new int[halfSize][halfSize];
        split(matrix1, matrix1TopLeft, matrix1TopRight, matrix1BottomLeft, matrix1BottomRight, length, halfSize);
        int[][] matrix2TopLeft = new int[halfSize][halfSize];
        int[][] matrix2TopRight = new int[halfSize][halfSize];
        int[][] matrix2BottomLeft = new int[halfSize][halfSize];
        int[][] matrix2BottomRight = new int[halfSize][halfSize];
        split(matrix2, matrix2TopLeft, matrix2TopRight, matrix2BottomLeft, matrix2BottomRight, length, halfSize);

        int[][] aux1 = multiply(add(matrix1TopLeft, matrix1BottomRight, halfSize), add(matrix2TopLeft, matrix2BottomRight, halfSize));
        int[][] aux2 = multiply(add(matrix1BottomLeft, matrix1BottomRight, halfSize), matrix2TopLeft);
        int[][] aux3 = multiply(matrix1TopLeft, subtract(matrix2TopRight, matrix2BottomRight, halfSize));
        int[][] aux4 = multiply(matrix1BottomRight, subtract(matrix2BottomLeft, matrix2TopLeft, halfSize));
        int[][] aux5 = multiply(add(matrix1TopLeft, matrix1TopRight, halfSize), matrix2BottomRight);
        int[][] aux6 = multiply(subtract(matrix1BottomLeft, matrix1TopLeft, halfSize), add(matrix2TopLeft, matrix2TopRight, halfSize));
        int[][] aux7 = multiply(subtract(matrix1TopRight, matrix1BottomRight, halfSize), add(matrix2BottomLeft, matrix2BottomRight, halfSize));

        int[][] resultTopLeft = add(subtract(add(aux1, aux4, halfSize), aux5, halfSize), aux7, halfSize);
        int[][] resultTopRight = add(aux3, aux5, halfSize);
        int[][] resultBottomLeft = add(aux2, aux4, halfSize);
        int[][] resultBottomRight = add(add(subtract(aux1, aux2, halfSize), aux3, halfSize), aux6, halfSize);
        return merge(resultTopLeft, resultTopRight, resultBottomLeft, resultBottomRight, length, halfSize);
    }

    private int[][] add(int[][] matrix1, int[][] matrix2, int length) {
        int[][] result = new int[length][length];
        for (int i = 0; i < length; ++i) {
            System.arraycopy(matrix1[i], 0, result[i], 0, length);
            for (int j = 0; j < length; ++j) {
                result[i][j] += matrix2[i][j];
            }
        }
        return result;
    }

    private int[][] subtract(int[][] matrix1, int[][] matrix2, int length) {
        int[][] result = new int[length][length];
        for (int i = 0; i < length; ++i) {
            System.arraycopy(matrix1[i], 0, result[i], 0, length);
            for (int j = 0; j < length; ++j) {
                result[i][j] -= matrix2[i][j];
            }
        }
        return result;
    }

    private void split(int[][] matrix, int[][] matrixTopLeft, int[][] matrixTopRight, int[][] matrixBottomLeft, int[][] matrixBottomRight, int length, int halfSize) {
        for (int i = 0; i < halfSize - 1; ++i) {
            System.arraycopy(matrix[i], 0, matrixTopLeft[i], 0, halfSize);
            System.arraycopy(matrix[i], halfSize, matrixTopRight[i], 0, length - halfSize);
            System.arraycopy(matrix[halfSize + i], 0, matrixBottomLeft[i], 0, halfSize);
            System.arraycopy(matrix[halfSize + i], halfSize, matrixBottomRight[i], 0, length - halfSize);
            if (0 != (length & (length - 1))) {
                matrixTopRight[i][halfSize - 1] = 0;
                matrixBottomRight[i][halfSize - 1] = 0;
            }
        }

        System.arraycopy(matrix[halfSize - 1], 0, matrixTopLeft[halfSize - 1], 0, halfSize);
        System.arraycopy(matrix[halfSize - 1], halfSize, matrixTopRight[halfSize - 1], 0, length - halfSize);
        if (0 != (length & (length - 1))) {
            matrixTopRight[halfSize - 1][halfSize - 1] = 0;
            Arrays.fill(matrixBottomLeft[halfSize - 1], 0);
            Arrays.fill(matrixBottomRight[halfSize - 1], 0);
        } else {
            System.arraycopy(matrix[length - 1], 0, matrixBottomLeft[halfSize - 1], 0, halfSize);
            System.arraycopy(matrix[length - 1], halfSize, matrixBottomRight[halfSize - 1], 0, length - halfSize);
        }
    }

    private int[][] merge(int[][] matrixTopLeft, int[][] matrixTopRight, int[][] matrixBottomLeft, int[][] matrixBottomRight, int length, int halfSize) {
        int[][] result = new int[length][length];
        for (int i = 0; i < halfSize - 1; ++i) {
            System.arraycopy(matrixTopLeft[i], 0, result[i], 0, halfSize);
            System.arraycopy(matrixTopRight[i], 0, result[i], halfSize, length - halfSize);
            System.arraycopy(matrixBottomLeft[i], 0, result[halfSize + i], 0, halfSize);
            System.arraycopy(matrixBottomRight[i], 0, result[halfSize + i], halfSize, length - halfSize);
        }
        System.arraycopy(matrixTopLeft[halfSize - 1], 0, result[halfSize - 1], 0, halfSize);
        System.arraycopy(matrixTopRight[halfSize - 1], 0, result[halfSize - 1], halfSize, length - halfSize);
        if (0 == (length & (length - 1))) {
            System.arraycopy(matrixBottomLeft[halfSize - 1], 0, result[length - 1], 0, halfSize);
            System.arraycopy(matrixBottomRight[halfSize - 1], 0, result[length - 1], halfSize, length - halfSize);
        }
        return result;
    }
}
