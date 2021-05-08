#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int value;
    ListNode *next;

    ListNode(int value) : value(value), next(nullptr) {}
};

class RadixSort {
public:
    void sort(ListNode *head) {
        int maxValue = head->next->value;
        int minValue = head->next->value;
        ListNode *current = head->next->next;
        while (current) {
            if (maxValue < current->value) {
                maxValue = current->value;
            }
            if (minValue > current->value) {
                minValue = current->value;
            }
            current = current->next;
        }

        vector<ListNode *> buckets(0);
        for (int i = 0; i < 10; ++i) {
            buckets.emplace_back(new ListNode(0));
        }

        int diff = maxValue - minValue;
        for (int gap = 1; gap <= diff; gap *= 10) {
            for (ListNode *bucket : buckets) {
                bucket->next = nullptr;
            }

            current = head->next;
            while (current) {
                ListNode *bucket = buckets[((current->value - minValue) / gap) % 10];
                while (bucket->next) {
                    bucket = bucket->next;
                }
                bucket->next = current;
                current = current->next;
                bucket->next->next = nullptr;
            }

            current = head;
            for (ListNode *bucket : buckets) {
                current->next = bucket->next;
                while (current->next) {
                    current = current->next;
                }
            }
            current->next = nullptr;
        }
    }
};
