package graph.minimum_spanning_tree;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class Kruskal {
    public int[] search(VertexNode[] graphs) {
        List<ConnectedNode> edgeLists = new ArrayList<>();
        for (int i = 0; i < graphs.length; ++i) {
            EdgeNode edge = graphs[i].next;
            while (null != edge) {
                edgeLists.add(new ConnectedNode(i, edge.index, edge.weight));
                edge = edge.next;
            }
        }

        Collections.sort(edgeLists, new Comparator<ConnectedNode>() {
            @Override
            public int compare(ConnectedNode node1, ConnectedNode node2) {
                return node1.weight - node2.weight;
            }
        });

        int[] roots = new int[graphs.length];
        Arrays.fill(roots, -1);
        boolean[] visited = new boolean[graphs.length];
        Arrays.fill(visited, false);

        int[] result = new int[graphs.length];
        Arrays.fill(result, -1);
        for (ConnectedNode edge : edgeLists) {
            int fromIndex = edge.fromIndex;
            int toIndex = edge.toIndex;
            if (!visited[toIndex] && getRoot(roots, fromIndex) != getRoot(roots, toIndex)) {
                result[toIndex] = fromIndex;
                roots[fromIndex] = toIndex;
                visited[toIndex] = true;
            }
        }
        return result;
    }

    private int getRoot(int[] roots, int index) {
        while (0 != ~roots[index]) {
            index = roots[index];
        }
        return index;
    }

    private class ConnectedNode {
        public int fromIndex = 0;
        public int toIndex = 0;
        public int weight = 0;

        public ConnectedNode(int fromIndex, int toIndex, int weight) {
            this.fromIndex = fromIndex;
            this.toIndex = toIndex;
            this.weight = weight;
        }
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
