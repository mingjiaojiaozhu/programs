#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    int value;
    struct node *prev;
    struct node *next;
} ListNode;

typedef struct hash {
    int key;
    ListNode *value;
    struct hash *next;
} HashNode;

typedef struct {
    ListNode *head;
    ListNode *tail;
    HashNode *hash;
    int length;
} CacheNode;

static HashNode *search(HashNode *hash, int key);
static void addHash(CacheNode *cache, int key, ListNode *value);
static void eraseHash(CacheNode *cache, int key);
static void addList(CacheNode *cache, ListNode *node);
static void eraseList(CacheNode *cache, ListNode *node);

void create(CacheNode *cache) {
    cache->hash = (HashNode *) malloc(sizeof(HashNode) * 64);
    for (int i = 0; i < 64; ++i) {
        cache->hash[i].key = 0;
        cache->hash[i].value = NULL;
        cache->hash[i].next = NULL;
    }
    cache->length = 0;

    cache->head = (ListNode *) malloc(sizeof(ListNode));
    cache->tail = (ListNode *) malloc(sizeof(ListNode));
    cache->head->key = 0;
    cache->tail->key = 0;
    cache->head->value = 0;
    cache->tail->value = 0;
    cache->head->prev = NULL;
    cache->tail->prev = cache->head;
    cache->head->next = cache->tail;
    cache->tail->next = NULL;
}

int isEmpty(CacheNode cache) {
    return !cache.length ? 1 : 0;
}

void set(CacheNode *cache, int key, int value) {
    HashNode *hash = search(cache->hash, key);
    if (hash) {
        eraseList(cache, hash->value);
        addHash(cache, key, hash->value);
        addList(cache, hash->value);
        return;
    }

    if (cache->length >= 64) {
        ListNode *node = cache->head->next;
        eraseList(cache, node);
        eraseHash(cache, node->key);
        --cache->length;
    }

    ListNode *node = (ListNode *) malloc(sizeof(ListNode));
    node->key = key;
    node->value = value;
    addHash(cache, key, node);
    addList(cache, node);
    ++cache->length;
}

int get(CacheNode *cache, int key) {
    HashNode *hash = search(cache->hash, key);
    if (hash) {
        ListNode *node = hash->value;
        eraseList(cache, node);
        addList(cache, node);
        return node->value;
    }
    return 1 << 31;
}

void clear(CacheNode *cache) {
    for (int i = 0; i < 64; ++i) {
        cache->hash[i].next = NULL;
    }
    cache->length = 0;
    cache->head->next = cache->tail;
    cache->tail->prev = cache->head;
}

static HashNode *search(HashNode *hash, int key) {
    HashNode *current = hash[key % 64].next;
    while (current) {
        if (key == current->key) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

static void addHash(CacheNode *cache, int key, ListNode *value) {
    HashNode *current = &cache->hash[key % 64];
    while (current->next) {
        current = current->next;
        if (key == current->key) {
            current->value = value;
            return;
        }
    }
    HashNode *node = (HashNode *) malloc(sizeof(HashNode));
    node->key = key;
    node->value = value;
    current->next = node;
}

static void eraseHash(CacheNode *cache, int key) {
    HashNode *current = &cache->hash[key % 64];
    while (current->next) {
        if (key == current->next->key) {
            current->next = current->next->next;
            return;
        }
        current = current->next;
    }
}

static void addList(CacheNode *cache, ListNode *node) {
    ListNode *prev = cache->tail->prev;
    node->prev = prev;
    node->next = cache->tail;
    prev->next = node;
    cache->tail->prev = node;
}

static void eraseList(CacheNode *cache, ListNode *node) {
    ListNode *prev = node->prev;
    ListNode *next = node->next;
    prev->next = next;
    next->prev = prev;
}
