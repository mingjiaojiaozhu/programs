#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <fstream>
#include <algorithm>
using namespace std;

class ExternalSort {
public:
    void sort(string inFile, string outFile) {
        int count = readFile(inFile);
        mergeTempFiles(inFile, outFile, count);
        for (int i = 0; i < count; ++i) {
            remove((inFile + "-" + to_string(i)).c_str());
        }
    }

private:
    typedef struct HeapNode {
        int value;
        fstream handle;

        HeapNode(string inFile, int index) {
            handle.open(inFile + "-" + to_string(index), ios::in);
            handle >> value;
        }
    } HeapNode, *pNode;

    struct cmp {
        bool operator() (const pNode node1, const pNode node2) {
            return node1->value > node2->value;
        }
    };

    int readFile(string inFile) {
        vector<int> values;
        int count = 0;

        fstream handle(inFile, ios::in);
        int value = 0;
        while (handle >> value) {
            values.emplace_back(value);
            if ((int) values.size() >= 65536) {
                writeTempFiles(values, inFile, count);
                ++count;
            }
        }
        handle.close();

        if (!values.empty()) {
            writeTempFiles(values, inFile, count);
            ++count;
        }
        return count;
    }

    void mergeTempFiles(string inFile, string outFile, int count) {
        priority_queue<pNode, vector<pNode>, cmp> queue;
        for (int i = 0; i < count; ++i) {
            queue.push(new HeapNode(inFile, i));
        }

        fstream handle(outFile, ios::out);
        while (!queue.empty()) {
            HeapNode *heap = queue.top();
            queue.pop();
            handle << heap->value << endl;

            int value = 0;
            if (!(heap->handle >> value)) {
                heap->handle.close();
            } else {
                heap->value = value;
                queue.push(heap);
            }
        }
        handle.close();
    }

    void writeTempFiles(vector<int> &values, string inFile, int index) {
        std::sort(values.begin(), values.end());

        fstream handle(inFile + "-" + to_string(index), ios::out);
        for (int value : values) {
            handle << value << endl;
        }
        handle.close();
        values.clear();
    }
};
