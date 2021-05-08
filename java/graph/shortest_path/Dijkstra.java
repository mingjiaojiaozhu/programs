package graph.shortest_path;

import java.util.Arrays;
import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Queue;

public class Dijkstra {
    public int[] search(VertexNode[] graphs, int start) {
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
