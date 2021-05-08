#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class OptimalLoading {
public:
    vector<int> solution(vector<int> &weights, int target) {
        vector<int> aux(weights.size(), 0);
        for (int i = weights.size() - 1; i > 0; --i) {
            aux[i - 1] = aux[i] + weights[i];
        }

        priority_queue<pNode, vector<pNode>, cmp> queue;
        int weight = 0;
        int level = 0;
        HeapNode *current = nullptr;
        while (level != weights.size()) {
            if (weight + weights[level] <= target) {
                queue.push(new HeapNode(weight + weights[level] + aux[level], level + 1, current, true));
            }
            queue.push(new HeapNode(weight + aux[level], level + 1, current, false));

            current = queue.top();
            queue.pop();
            level = current->level;
            weight = current->weight - aux[level - 1];
        }

        vector<int> result(0);
        for (int i = weights.size() - 1; i >= 0; --i) {
            if (current->marked) {
                result.emplace_back(weights[i]);
            }
            current = current->parent;
        }
        reverse(result.begin(), result.end());
        return result;
    }

private:
    typedef struct HeapNode {
        int weight;
        int level;
        HeapNode *parent;
        bool marked;

        HeapNode(int weight, int level, HeapNode *parent, bool marked): weight(weight), level(level), parent(parent), marked(marked) {}
    } HeapNode, *pNode;

    struct cmp {
        bool operator() (const pNode node1, const pNode node2) {
            return node1->weight < node2->weight;
        }
    };
};
