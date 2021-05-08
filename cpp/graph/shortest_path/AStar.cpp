#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class AStar {
public:
    vector<vector<int>> search(vector<vector<int>> &graphs, vector<int> &start, vector<int> &end) {
        vector<vector<bool>> visited(graphs.size(), vector<bool>(graphs[0].size(), false));
        visited[start[0]][start[1]] = true;

        priority_queue<pNode, vector<pNode>, cmp> queue;
        queue.push(new HeapNode(start[0], start[1], 0, getDistance(start[0], start[1], end[0], end[1]), nullptr));
        while (!queue.empty()) {
            HeapNode *heap = queue.top();
            queue.pop();
            if (heap->values[0] == end[0] && heap->values[1] == end[1]) {
                vector<vector<int>> result(0);
                while (heap) {
                    result.emplace_back(heap->values);
                    heap = heap->parent;
                }
                reverse(result.begin(), result.end());
                return result;
            }

            search(graphs, queue, visited, heap, heap->values[0] + 1, heap->values[1], end);
            search(graphs, queue, visited, heap, heap->values[0], heap->values[1] + 1, end);
            search(graphs, queue, visited, heap, heap->values[0] - 1, heap->values[1], end);
            search(graphs, queue, visited, heap, heap->values[0], heap->values[1] - 1, end);
        }
        return vector<vector<int>>(0);
    }

private:
    typedef struct HeapNode {
        vector<int> values;
        int index;
        int weight;
        HeapNode *parent;

        HeapNode(int row, int col, int index, int distance, HeapNode *parent): index(index), weight(index + distance), parent(parent) {
            values.emplace_back(row);
            values.emplace_back(col);
        }
    } HeapNode, *pNode;

    struct cmp {
        bool operator() (const pNode node1, const pNode node2) {
            return node1->weight > node2->weight;
        }
    };

    void search(vector<vector<int>> &graphs, priority_queue<pNode, vector<pNode>, cmp> &queue, vector<vector<bool>> &visited, HeapNode *parent, int row, int col, vector<int> &end) {
        if (row >= 0 && row < (int) graphs.size() && col >= 0 && col < (int) graphs[0].size() && graphs[row][col] && !visited[row][col]) {
            queue.push(new HeapNode(row, col, parent->index + 1, getDistance(row, col, end[0], end[1]), parent));
            visited[row][col] = true;
        }
    }

    int getDistance(int row1, int col1, int row2, int col2) {
        return abs(row2 - row1) + abs(col2 - col1);
    }
};
