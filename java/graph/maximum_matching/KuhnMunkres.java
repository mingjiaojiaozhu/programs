package graph.maximum_matching;

import java.util.Arrays;

public class KuhnMunkres {
    public int[] search(int[][] graphs) {
        int[][] weights = new int[3][graphs.length];
        Arrays.fill(weights[0], 0);
        for (int i = 0; i < graphs.length; ++i) {
            weights[1][i] = Arrays.stream(graphs[i]).max().getAsInt();
        }
        boolean[][] visited = new boolean[2][graphs.length];

        int[] result = new int[graphs.length];
        Arrays.fill(result, -1);
        for (int i = 0; i < graphs.length; ++i) {
            Arrays.fill(weights[2], Integer.MAX_VALUE);
            while (true) {
                Arrays.fill(visited[0], false);
                Arrays.fill(visited[1], false);
                if (search(graphs, i, result, visited, weights)) {
                    break;
                }

                int weight = Integer.MAX_VALUE;
                for (int j = 0; j < graphs.length; ++j) {
                    if (!visited[0][j] && weight > weights[2][j]) {
                        weight = weights[2][j];
                    }
                }

                for (int j = 0; j < graphs.length; ++j) {
                    if (visited[1][j]) {
                        weights[1][j] -= weight;
                    }

                    if (visited[0][j]) {
                        weights[0][j] += weight;
                    } else {
                        weights[2][j] -= weight;
                    }
                }
            }
        }
        return result;
    }

    private boolean search(int[][] graphs, int start, int[] result, boolean[][] visited, int[][] weights) {
        visited[1][start] = true;
        for (int i = 0; i < graphs.length; ++i) {
            if (visited[0][i]) {
                continue;
            }

            int weight = weights[1][start] + weights[0][i] - graphs[start][i];
            if (0 == weight) {
                visited[0][i] = true;
                if (0 == ~result[i] || search(graphs, result[i], result, visited, weights)) {
                    result[i] = start;
                    return true;
                }
            } else {
                if (weights[2][i] > weight) {
                    weights[2][i] = weight;
                }
            }
        }
        return false;
    }
}
