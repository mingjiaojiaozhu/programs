package graph.maximum_matching;

import java.util.Arrays;

public class Hungary {
    public int[] search(int[][] graphs) {
        boolean[] visited = new boolean[graphs.length];
        int[] result = new int[graphs.length];
        Arrays.fill(result, -1);
        for (int i = 0; i < graphs.length; ++i) {
            Arrays.fill(visited, false);
            if (!search(graphs, i, result, visited)) {
                return new int[0];
            }
        }
        return result;
    }

    private boolean search(int[][] graphs, int start, int[] result, boolean[] visited) {
        for (int i = 0; i < graphs.length; ++i) {
            if (0 != graphs[i][start] && !visited[i]) {
                visited[i] = true;
                if (0 == ~result[i] || search(graphs, result[i], result, visited)) {
                    result[i] = start;
                    return true;
                }
            }
        }
        return false;
    }
}
