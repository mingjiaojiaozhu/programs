package graph.maximum_flow;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

public class EdmondsKarp {
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

        int[] parent = new int[graphs.length];
        int[] maxFlow = new int[graphs.length];
        Arrays.fill(maxFlow, Integer.MAX_VALUE);
        int result = 0;
        while (true) {
            int value = search(graphs, start, end, weights, parent, maxFlow);
            if (0 == ~value) {
                break;
            }

            int index = end;
            while (index != start) {
                weights[parent[index]][index] -= value;
                weights[index][parent[index]] += value;
                index = parent[index];
            }
            result += value;
        }
        return result;
    }

    private int search(VertexNode[] graphs, int start, int end, int[][] weights, int[] parent, int[] maxFlow) {
        Arrays.fill(parent, -1);
        Queue<Integer> queue = new LinkedList<>();
        queue.offer(start);
        while (!queue.isEmpty()) {
            int index = queue.poll();
            EdgeNode edge = graphs[index].next;
            while (null != edge) {
                int edgeIndex = edge.index;
                if (0 != weights[index][edgeIndex] && 0 == ~parent[edgeIndex]) {
                    parent[edgeIndex] = index;
                    maxFlow[edgeIndex] = Math.min(weights[index][edgeIndex], maxFlow[index]);
                    queue.offer(edgeIndex);
                }
                edge = edge.next;
            }
        }
        return (0 != ~parent[end]) ? maxFlow[end] : -1;
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
