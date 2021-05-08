package graph.shortest_path;

import java.util.Arrays;

public class BellmanFord {
    public int[] search(VertexNode[] graphs, int start) {
        int[] result = new int[graphs.length];
        Arrays.fill(result, Integer.MAX_VALUE);
        result[start] = 0;

        int index = start;
        for (VertexNode _ : graphs) {
            EdgeNode edge = graphs[index].next;
            while (null != edge) {
                int pivot = result[index] + edge.weight;
                int edgeIndex = edge.index;
                if (Integer.MAX_VALUE != result[index] && pivot < result[edgeIndex]) {
                    result[edgeIndex] = pivot;
                }
                edge = edge.next;
            }

            ++index;
            if (index >= graphs.length) {
                index = 0;
            }
        }

        index = start;
        for (VertexNode _ : graphs) {
            EdgeNode edge = graphs[index].next;
            while (null != edge) {
                int pivot = result[index] + edge.weight;
                int edgeIndex = edge.index;
                if (Integer.MAX_VALUE != result[index] && pivot < result[edgeIndex]) {
                    return new int[0];
                }
                edge = edge.next;
            }

            ++index;
            if (index >= graphs.length) {
                index = 0;
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
