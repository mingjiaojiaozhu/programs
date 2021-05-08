#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class HeapSelect {
public:
    vector<int> search(vector<int> &nums, int k) {
        priority_queue<int, vector<int>, cmp> queue;
        for (int value : nums) {
            if ((int) queue.size() < k) {
                queue.push(value);
                continue;
            }

            if (value < queue.top()) {
                queue.pop();
                queue.push(value);
            }
        }

        vector<int> result(0);
        while (!queue.empty()) {
            result.emplace_back(queue.top());
            queue.pop();
        }
        return result;
    }

private:
    struct cmp {
        bool operator() (const int p, const int q) {
            return p < q;
        }
    };
};
