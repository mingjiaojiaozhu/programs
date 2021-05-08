package graph.shortest_path;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Queue;

public class AStar {
    public int[][] search(int[][] graphs, int[] start, int[] end) {
        boolean[][] visited = new boolean[graphs.length][graphs[0].length];
        for (int i = 0; i < graphs.length; ++i) {
            Arrays.fill(visited[i], false);
        }
        visited[start[0]][start[1]] = true;

        Queue<HeapNode> queue = new PriorityQueue<>(cmp);
        queue.offer(new HeapNode(start[0], start[1], 0, getDistance(start[0], start[1], end[0], end[1]), null));
        while (!queue.isEmpty()) {
            HeapNode heap = queue.poll();
            if (heap.values[0] == end[0] && heap.values[1] == end[1]) {
                List<int[]> result = new ArrayList<>();
                while (null != heap) {
                    result.add(heap.values);
                    heap = heap.parent;
                }
                Collections.reverse(result);
                return result.toArray(new int[0][]);
            }

            search(graphs, queue, visited, heap, heap.values[0] + 1, heap.values[1], end);
            search(graphs, queue, visited, heap, heap.values[0], heap.values[1] + 1, end);
            search(graphs, queue, visited, heap, heap.values[0] - 1, heap.values[1], end);
            search(graphs, queue, visited, heap, heap.values[0], heap.values[1] - 1, end);
        }
        return new int[0][];
    }

    private void search(int[][] graphs, Queue<HeapNode> queue, boolean[][] visited, HeapNode parent, int row, int col, int[] end) {
        if (row >= 0 && row < graphs.length && col >= 0 && col < graphs[0].length && 0 != graphs[row][col] && !visited[row][col]) {
            queue.offer(new HeapNode(row, col, parent.index + 1, getDistance(row, col, end[0], end[1]), parent));
            visited[row][col] = true;
        }
    }

    private int getDistance(int row1, int col1, int row2, int col2) {
        return Math.abs(row2 - row1) + Math.abs(col2 - col1);
    }

    private class HeapNode {
        public int[] values = new int[2];
        public int index = 0;
        public int weight = 0;
        public HeapNode parent = null;

        public HeapNode(int row, int col, int index, int weight, HeapNode parent) {
            values[0] = row;
            values[1] = col;
            this.index = index;
            this.weight = weight;
            this.parent = parent;
        }
    }

    private static Comparator<HeapNode> cmp = new Comparator<HeapNode>() {
        @Override
        public int compare(HeapNode node1, HeapNode node2) {
            return node1.weight - node2.weight;
        }
    };
}
