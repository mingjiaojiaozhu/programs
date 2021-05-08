package graph.minimum_spanning_tree;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Boruvka {
    public int[] search(VertexNode[] graphs) {
        List<ConnectedNode> edgeLists = new ArrayList<>();
        for (int i = 0; i < graphs.length; ++i) {
            EdgeNode edge = graphs[i].next;
            while (null != edge) {
                edgeLists.add(new ConnectedNode(i, edge.index, edge.weight));
                edge = edge.next;
            }
        }

        UnionFind unionFind = new UnionFind(graphs.length);
        int[] result = new int[graphs.length];
        Arrays.fill(result, -1);
        while (true) {
            ConnectedNode[] minEdges = new ConnectedNode[graphs.length];
            Arrays.fill(minEdges, null);
            boolean flag = false;
            for (ConnectedNode edge : edgeLists) {
                int fromIndex = unionFind.values[edge.fromIndex];
                int toIndex = unionFind.values[edge.toIndex];
                if (fromIndex != toIndex && (null == minEdges[toIndex] || edge.weight < minEdges[toIndex].weight)) {
                    minEdges[toIndex] = edge;
                    flag = true;
                }
            }

            if (!flag) {
                break;
            }

            for (ConnectedNode edge : minEdges) {
                if (null != edge) {
                    int fromIndex = edge.fromIndex;
                    int toIndex = edge.toIndex;
                    if (unionFind.get(fromIndex) != unionFind.get(toIndex)) {
                        unionFind.add(fromIndex, toIndex);
                        result[toIndex] = fromIndex;
                    }
                }
            }
        }
        return result;
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

    private class UnionFind {
        public int[] values = null;
        public int[] weights = null;

        public UnionFind(int degree) {
            values = new int[degree];
            for (int i = 0; i < degree; ++i) {
                values[i] = i;
            }
            weights = new int[degree];
            Arrays.fill(weights, 1);
        }

        public void add(int num1, int num2) {
            int root1 = get(num1);
            int root2 = get(num2);
            if (root1 != root2) {
                if (weights[root1] < weights[root2]) {
                    values[root2] = root1;
                    weights[root1] += weights[root2];
                } else {
                    values[root1] = root2;
                    weights[root2] += weights[root1];
                }
            }
        }

        public int get(int num) {
            int root = num;
            while (root != values[root]) {
                root = values[root];
            }

            while (num != root) {
                int aux = values[num];
                values[num] = root;
                num = aux;
            }
            return root;
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
