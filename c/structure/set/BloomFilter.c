#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *values;
} HashNode;

static const int seeds[3] = {2, 3, 5};

static int getHashCode(char *text, int seed);

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

void add(HashNode *hash, char *text) {
    for (int i = 0; i < 3; ++i) {
        int value = getHashCode(text, seeds[i]);
        int index = value >> 3;
        if (index >= 0 && index < 65536) {
            hash->values[index] |= 1 << (value & 7);
        }
    }
}

int contains(HashNode hash, char *text) {
    for (int i = 0; i < 3; ++i) {
        int value = getHashCode(text, seeds[i]);
        int index = value >> 3;
        if (index < 0 || index >= 65536 || !(hash.values[index] & (1 << (value & 7)))) {
            return 0;
        }
    }
    return 1;
}

void clear(HashNode *hash) {
    memset(hash->values, '\0', sizeof(char) * 65536);
}

static int getHashCode(char *text, int seed) {
    int code = 0;
    for (char *p = text; '\0' != *p; ++p) {
        code = seed * code + (*p) - 'a';
    }
    return code;
}
