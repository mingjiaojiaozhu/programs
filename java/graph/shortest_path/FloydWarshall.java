package graph.shortest_path;

import java.util.Arrays;

public class FloydWarshall {
    public int[][] search(VertexNode[] graphs) {
        int[][] result = new int[graphs.length][graphs.length];
        for (int i = 0; i < graphs.length; ++i) {
            Arrays.fill(result[i], Integer.MAX_VALUE);
            EdgeNode edge = graphs[i].next;
            while (null != edge) {
                result[i][edge.index] = edge.weight;
                edge = edge.next;
            }
            result[i][i] = 0;
        }

        for (int i = 0; i < graphs.length; ++i) {
            for (int j = 0; j < graphs.length; ++j) {
                for (int k = 0; k < graphs.length; ++k) {
                    if (Integer.MAX_VALUE == result[j][i] || Integer.MAX_VALUE == result[i][k]) {
                        continue;
                    }

                    int pivot = result[j][i] + result[i][k];
                    if (pivot < result[j][k]) {
                        result[j][k] = pivot;
                    }
                }
            }
        }
        return result;
    }

    public class EdgeNode {
        public int index = 0;
        public int weight = 0;
        public EdgeNode next = null;

        public EdgeNode(int index, int weight) {
            this.index = index;
            this.weight = weight;
        }
    }

    public class VertexNode {
        public int value = 0;
        public EdgeNode next = null;

        public VertexNode(int value) {
            this.value = value;
        }
    }
}
