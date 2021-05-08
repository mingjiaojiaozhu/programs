#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    int length;
} ArrayNode;

typedef struct {
    FILE *handle;
    int value;
} HeapNode;

typedef struct {
    HeapNode *values;
    int length;
} QueueNode;

static int readFile(char *inFile, char *tempFile);
static void mergeTempFiles(char *inFile, char *outFile, int count, char *tempFile);
static void writeTempFiles(ArrayNode *values, char *inFile, int index, char *tempFile);
static void enqueue(QueueNode *queue, FILE *handle, int value);
static HeapNode dequeue(QueueNode *queue);
static int cmp(const void *p, const void *q);

void externalSort(char *inFile, char *outFile) {
    char *tempFile = (char *) malloc(sizeof(char) * 128);
    int count = readFile(inFile, tempFile);
    mergeTempFiles(inFile, outFile, count, tempFile);
    for (int i = 0; i < count; ++i) {
        memset(tempFile, '\0', sizeof(char) * 128);
        sprintf(tempFile, "%s-%d", inFile, i);
        remove(tempFile);
    }
}

static int readFile(char *inFile, char *tempFile) {
    ArrayNode *values = (ArrayNode *) malloc(sizeof(ArrayNode));
    values->values = (int *) malloc(sizeof(int) * 65536);
    memset(values->values, 0, sizeof(int) * 65536);
    values->length = 0;
    int count = 0;

    FILE *handle = fopen(inFile, "r");
    int value = 0;
    while (~fscanf(handle, "%d", &value)) {
        values->values[values->length] = value;
        ++values->length;
        if (values->length >= 65536) {
            writeTempFiles(values, inFile, count, tempFile);
            ++count;
        }
    }
    fclose(handle);

    if (values->length) {
        writeTempFiles(values, inFile, count, tempFile);
        ++count;
    }
    return count;
}

static void mergeTempFiles(char *inFile, char *outFile, int count, char *tempFile) {
    QueueNode *queue = (QueueNode *) malloc(sizeof(QueueNode));
    queue->values = (HeapNode *) malloc(sizeof(HeapNode) * count);
    queue->length = 0;
    for (int i = 0; i < count; ++i) {
        memset(tempFile, '\0', sizeof(char) * 128);
        sprintf(tempFile, "%s-%d", inFile, i);
        FILE *handle = fopen(tempFile, "r");
        int value = 0;
        fscanf(handle, "%d", &value);
        enqueue(queue, handle, value);
    }

    FILE *handle = fopen(outFile, "w");
    while (queue->length) {
        HeapNode heap = dequeue(queue);
        fprintf(handle, "%d\n", heap.value);

        int value = 0;
        if (!(~fscanf(heap.handle, "%d", &value))) {
            fclose(heap.handle);
        } else {
            enqueue(queue, heap.handle, value);
        }
    }
    fclose(handle);
}

static void writeTempFiles(ArrayNode *values, char *inFile, int index, char *tempFile) {
    qsort(values->values, values->length, sizeof(int), cmp);

    memset(tempFile, '\0', sizeof(char) * 128);
    sprintf(tempFile, "%s-%d", inFile, index);
    FILE *handle = fopen(tempFile, "w");
    for (int i = 0; i < values->length; ++i) {
        fprintf(handle, "%d\n", values->values[i]);
    }
    fclose(handle);
    memset(values->values, 0, sizeof(int) * values->length);
    values->length = 0;
}

static void enqueue(QueueNode *queue, FILE *handle, int value) {
    int child = queue->length;
    while (child > 0) {
        int parent = (child - 1) >> 1;
        if (queue->values[parent].value <= value) {
            break;
        }
        queue->values[child] = queue->values[parent];
        child = parent;
    }
    queue->values[child].handle = handle;
    queue->values[child].value = value;
    ++queue->length;
}

static HeapNode dequeue(QueueNode *queue) {
    --queue->length;
    HeapNode value = queue->values[0];
    HeapNode pivot = queue->values[queue->length];
    int parent = 0;
    while (1) {
        int child = (parent << 1) + 1;
        if (child >= queue->length) {
            break;
        }

        if (child < queue->length - 1 && queue->values[child].value > queue->values[child + 1].value) {
            ++child;
        }
        if (queue->values[child].value >= pivot.value) {
            break;
        }
        queue->values[parent] = queue->values[child];
        parent = child;
    }
    queue->values[parent] = pivot;
    return value;
}

static int cmp(const void *p, const void *q) {
    return *((int *) p) - *((int *) q);
}
