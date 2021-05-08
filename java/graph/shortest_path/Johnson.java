package graph.shortest_path;

import java.util.Arrays;
import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Queue;

public class Johnson {
    public int[][] search(VertexNode[] graphs) {
        VertexNode[] aux = new VertexNode[graphs.length + 1];
        System.arraycopy(graphs, 0, aux, 0, graphs.length);
        aux[graphs.length] = new VertexNode(0);
        for (int i = graphs.length - 1; i >= 0; --i) {
            EdgeNode edge = new EdgeNode(i, 0);
            edge.next = aux[graphs.length].next;
            aux[graphs.length].next = edge;
        }

        int[] reWeight = bellmanFord(aux, graphs.length);
        if (0 == reWeight.length) {
            return new int[0][];
        }

        for (int i = 0; i < graphs.length; ++i) {
            EdgeNode edge = graphs[i].next;
            while (null != edge) {
                edge.weight += reWeight[i] - reWeight[edge.index];
                edge = edge.next;
            }
        }

        int[][] result = new int[graphs.length][];
        for (int i = 0; i < graphs.length; ++i) {
            result[i] = dijkstra(graphs, i);
            for (int j = 0; j < graphs.length; ++j) {
                if (Integer.MAX_VALUE != result[i][j]) {
                    result[i][j] += reWeight[j] - reWeight[i];
                }
            }
        }
        return result;
    }

    private int[] bellmanFord(VertexNode[] graphs, int start) {
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

    public int[] dijkstra(VertexNode[] graphs, int start) {
        boolean[] visited = new boolean[graphs.length];
        Arrays.fill(visited, false);
        Queue<HeapNode> queue = new PriorityQueue<>(cmp);
        queue.offer(new HeapNode(start, 0));

        int[] result = new int[graphs.length];
        Arrays.fill(result, Integer.MAX_VALUE);
        while (!queue.isEmpty()) {
            HeapNode heap = queue.poll();
            int index = heap.index;
            int weight = heap.weight;
            if (visited[index]) {
                continue;
            }

            result[index] = weight;
            visited[index] = true;

            EdgeNode edge = graphs[index].next;
            while (null != edge) {
                int edgeIndex = edge.index;
                int edgeWeight = weight + edge.weight;
                if (!visited[edgeIndex]) {
                    queue.offer(new HeapNode(edgeIndex, edgeWeight));
                }
                edge = edge.next;
            }
        }
        return result;
    }

    private class HeapNode {
        public int index = 0;
        public int weight = 0;

        public HeapNode(int index, int weight) {
            this.index = index;
            this.weight = weight;
        }
    }

    private static Comparator<HeapNode> cmp = new Comparator<HeapNode>() {
        @Override
        public int compare(HeapNode node1, HeapNode node2) {
            return node1.weight - node2.weight;
        }
    };

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
