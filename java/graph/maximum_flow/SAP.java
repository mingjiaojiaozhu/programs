package graph.maximum_flow;

import java.util.Arrays;

public class SAP {
    public int search(VertexNode[] graphs, int start, int end) {
        int[][] weights = new int[graphs.length][graphs.length];
        for (int i = 0; i < graphs.length; ++i) {
            Arrays.fill(weights[i], 0);
            EdgeNode edge = graphs[i].next;
            while (null != edge) {
                weights[i][edge.index] = edge.weight;
                edge = edge.next;
            }
        }

        int[] gap = new int[graphs.length + 1];
        Arrays.fill(gap, 0);
        gap[0] = graphs.length;
        int[] degrees = new int[graphs.length];
        Arrays.fill(degrees, 0);
        int result = 0;
        while (degrees[start] != graphs.length) {
            result += search(graphs, start, end, start, Integer.MAX_VALUE, weights, gap, degrees);
        }
        return result;
    }

    private int search(VertexNode[] graphs, int start, int end, int index, int flow, int[][] weights, int[] gap, int[] degrees) {
        if (index == end) {
            return flow;
        }

        EdgeNode edge = graphs[index].next;
        int pivot = flow;
        int border = graphs.length - 1;
        while (null != edge) {
            int edgeIndex = edge.index;
            if (0 != weights[index][edgeIndex]) {
                if (degrees[index] == degrees[edgeIndex] + 1) {
                    int value = search(graphs, start, end, edgeIndex, Math.min(pivot, weights[index][edgeIndex]), weights, gap, degrees);
                    weights[index][edgeIndex] -= value;
                    weights[edgeIndex][index] += value;
                    pivot -= value;
                    if (degrees[start] == graphs.length || 0 == pivot) {
                        return flow - pivot;
                    }
                }
                if (border > degrees[edgeIndex]) {
                    border = degrees[edgeIndex];
                }
            }
            edge = edge.next;
        }

        --gap[degrees[index]];
        if (0 == ~gap[degrees[index]]) {
            degrees[start] = graphs.length;
        } else {
            degrees[index] = border + 1;
            ++gap[degrees[index]];
        }
        return flow - pivot;
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
