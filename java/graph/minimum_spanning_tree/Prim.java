package graph.minimum_spanning_tree;

import java.util.Arrays;
import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Queue;

public class Prim {
    public int[] search(VertexNode[] graphs, int start) {
        boolean[] visited = new boolean[graphs.length];
        Arrays.fill(visited, false);
        Queue<HeapNode> queue = new PriorityQueue<>(cmp);
        queue.offer(new HeapNode(-1, start, 0));

        int[] result = new int[graphs.length];
        Arrays.fill(result, -1);
        while (!queue.isEmpty()) {
            HeapNode heap = queue.poll();
            int fromIndex = heap.fromIndex;
            int toIndex = heap.toIndex;
            if (visited[toIndex]) {
                continue;
            }

            result[toIndex] = fromIndex;
            visited[toIndex] = true;

            EdgeNode edge = graphs[toIndex].next;
            while (null != edge) {
                int edgeIndex = edge.index;
                int edgeWeight = edge.weight;
                if (!visited[edgeIndex]) {
                    queue.offer(new HeapNode(toIndex, edgeIndex, edgeWeight));
                }
                edge = edge.next;
            }
        }
        return result;
    }

    private class HeapNode {
        public int fromIndex = 0;
        public int toIndex = 0;
        public int weight = 0;

        public HeapNode(int fromIndex, int toIndex, int weight) {
            this.fromIndex = fromIndex;
            this.toIndex = toIndex;
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
