#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class KnapsackOfFractional {
public:
    int solution(vector<int> &weights, vector<int> &values, int target) {
        vector<GoodNode *> goods(0);
        for (int i = 0; i < (int) weights.size(); ++i) {
            goods.emplace_back(new GoodNode(weights[i], values[i]));
        }

        sort(goods.begin(), goods.end(), cmp);

        int result = 0;
        for (GoodNode *good : goods) {
            if (target < good->weight) {
                return result + target * good->value / good->weight;
            }

            target -= good->weight;
            result += good->value;
        }
        return result;
    }

private:
    typedef struct GoodNode {
        int weight;
        int value;
        double rate;

        GoodNode(int weight, int value) : weight(weight), value(value), rate((double) value / weight) {}
    } GoodNode, *pNode;

    static bool cmp(const pNode &node1, const pNode &node2) {
        return node1->rate > node2->rate;
    }
};
