package classic.divide_and_conquer;

import java.util.Arrays;
import java.util.Comparator;

public class ClosestPairOfPoints {
    public int[][] solution(int[][] points) {
        int[][] result = new int[2][];
        match(points, result);
        return result;
    }

    private int match(int[][] points, int[][] result) {
        int length = points.length;
        if (length < 2) {
            return Integer.MAX_VALUE;
        }
        if (2 == length) {
            result[0] = points[0];
            result[1] = points[1];
            return getDistance(points[0], points[1]);
        }

        Arrays.sort(points, new Comparator<int[]>() {
            @Override
            public int compare(int[] node1, int[] node2) {
                return node1[0] - node2[0];
            }
        });

        int halfSize = length >> 1;
        int[][] left = Arrays.copyOf(points, halfSize);
        int[][] aux1 = new int[2][];
        int distance1 = match(left, aux1);

        int[][] right = Arrays.copyOfRange(points, halfSize, points.length);
        int[][] aux2 = new int[2][];
        int distance2 = match(right, aux2);

        int minDistance = Math.min(distance1, distance2);
        if (distance1 < distance2) {
            result[0] = aux1[0];
            result[1] = aux1[1];
        } else {
            result[0] = aux2[0];
            result[1] = aux2[1];
        }

        int border1 = getBorder(left, 0, points[halfSize][0] - minDistance);
        int border2 = getBorder(right, 0, points[halfSize][0] + minDistance);
        if (border1 == left.length || 0 == border2) {
            return minDistance;
        }

        int[][] aux = Arrays.copyOf(right, border2);
        Arrays.sort(aux, new Comparator<int[]>() {
            @Override
            public int compare(int[] node1, int[] node2) {
                return node1[1] - node2[1];
            }
        });

        for (int i = border1; i < left.length; ++i) {
            int start = getBorder(aux, 1, left[i][1] - minDistance);
            int end = getBorder(aux, 1, left[i][1] + minDistance);
            for (int j = start; j < end; ++j) {
                int distance = getDistance(left[i], aux[j]);
                if (minDistance > distance) {
                    result[0] = left[i];
                    result[1] = aux[j];
                    minDistance = distance;
                }
            }
        }
        return minDistance;
    }

    private int getBorder(int[][] points, int index, int target) {
        int start = 0;
        int end = points.length - 1;
        while (start <= end) {
            int middle = start + ((end - start) >> 1);
            if (target < points[middle][index]) {
                end = middle - 1;
            } else {
                start = middle + 1;
            }
        }
        return start;
    }

    private int getDistance(int[] point1, int[] point2) {
        return Math.abs(point2[0] - point1[0]) + Math.abs(point2[1] - point1[1]);
    }
}
