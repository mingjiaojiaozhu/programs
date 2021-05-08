#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int weight;
    int value;
    double rate;
} GoodNode;

static int cmp(const void *p, const void *q);

int knapsackOfFractional(int *weights, int *values, int length, int target) {
    GoodNode **goods = (GoodNode **) malloc(sizeof(GoodNode *) * length);
    for (int i = 0; i < length; ++i) {
        goods[i] = (GoodNode *) malloc(sizeof(GoodNode));
        goods[i]->weight = weights[i];
        goods[i]->value = values[i];
        goods[i]->rate = (double) values[i] / weights[i];
    }

    qsort(goods, length, sizeof(GoodNode *), cmp);

    int result = 0;
    for (int i = 0; i < length; ++i) {
        if (target < goods[i]->weight) {
            return result + target * goods[i]->value / goods[i]->weight;
        }

        target -= goods[i]->weight;
        result += goods[i]->value;
    }
    return result;
}

static int cmp(const void *p, const void *q) {
    return ((*((GoodNode **) p))->rate < (*((GoodNode **) q))->rate) ? 1 : -1;
}
