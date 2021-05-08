package graph;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Stack;

public class CriticalPath {
    public int[] search(VertexNode[] graphs) {
        Stack<Integer> stack = new Stack<>();
        int[] vertexEnd = topologicalSort(graphs, stack);
        if (0 == vertexEnd.length) {
            return new int[0];
        }
        int[] vertexLatest = reverseTopologicalSort(graphs, vertexEnd, stack);

        List<Integer> result = new ArrayList<>();
        for (int i = 0; i < graphs.length; ++i) {
            if (vertexEnd[i] == vertexLatest[i]) {
                result.add(i);
            }
        }
        return result.stream().mapToInt(Integer::valueOf).toArray();
    }

    private int[] topologicalSort(VertexNode[] graphs, Stack<Integer> stack) {
        int[] inDegrees = new int[graphs.length];
        Arrays.fill(inDegrees, 0);
        for (VertexNode graph : graphs) {
            EdgeNode edge = graph.next;
            while (null != edge) {
                ++inDegrees[edge.index];
                edge = edge.next;
            }
        }

        Queue<Integer> queue = new LinkedList<>();
        for (int i = 0; i < graphs.length; ++i) {
            if (0 == inDegrees[i]) {
                queue.offer(i);
            }
        }

        int[] vertexEnd = new int[graphs.length];
        Arrays.fill(vertexEnd, 0);
        int count = 0;
        while (!queue.isEmpty()) {
            int index = queue.poll();
            stack.push(index);
            ++count;

            EdgeNode edge = graphs[index].next;
            int pivot = vertexEnd[index];
            while (null != edge) {
                int edgeIndex = edge.index;
                int edgeWeight = edge.weight;
                --inDegrees[edgeIndex];
                if (0 == inDegrees[edgeIndex]) {
                    queue.offer(edgeIndex);
                    if (vertexEnd[edgeIndex] < pivot + edgeWeight) {
                        vertexEnd[edgeIndex] = pivot + edgeWeight;
                    }
                }
                edge = edge.next;
            }
        }
        return (count == graphs.length) ? vertexEnd : new int[0];
    }

    private int[] reverseTopologicalSort(VertexNode[] graphs, int[] vertexEnd, Stack<Integer> stack) {
        int maxValue = vertexEnd[stack.pop()];
        int[] vertexLatest = new int[graphs.length];
        Arrays.fill(vertexLatest, maxValue);
        while (!stack.isEmpty()) {
            int index = stack.pop();
            EdgeNode edge = graphs[index].next;
            while (null != edge) {
                int edgeIndex = edge.index;
                int edgeWeight = edge.weight;
                if (vertexLatest[index] > vertexLatest[edgeIndex] - edgeWeight) {
                    vertexLatest[index] = vertexLatest[edgeIndex] - edgeWeight;
                }
                edge = edge.next;
            }
        }
        return vertexLatest;
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
