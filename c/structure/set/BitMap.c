#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *values;
} HashNode;

void create(HashNode *hash) {
    hash->values = (char *) malloc(sizeof(char) * 65536);
    memset(hash->values, '\0', sizeof(char) * 65536);
}

int isEmpty(HashNode hash) {
    for (int i = 0; i < 65536; ++i) {
        if (hash.values[i]) {
            return 0;
        }
    }
    return 1;
}

void add(HashNode *hash, int value) {
    int index = value >> 3;
    if (index >=0 && index < 65536) {
        hash->values[index] |= 1 << (value & 7);
    }
}

void erase(HashNode *hash, int value) {
    int index = value >> 3;
    if (index >=0 && index < 65536) {
        hash->values[index] &= ~(1 << (value & 7));
    }
}

int contains(HashNode hash, int value) {
    int index = value >> 3;
    if (index >=0 && index < 65536) {
        return (0 != (hash.values[index] & (1 << (value & 7)))) ? 1 : 0;
    }
    return 0;
}

void clear(HashNode *hash) {
    memset(hash->values, '\0', sizeof(char) * 65536);
}
