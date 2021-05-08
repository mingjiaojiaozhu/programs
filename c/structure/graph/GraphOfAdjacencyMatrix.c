#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *vertexes;
    int **edges;
    int length;
    int capacity;
} GraphNode;

void create(GraphNode *graph) {
    graph->vertexes = (int *) malloc(sizeof(int) * 64);
    memset(graph->vertexes, 0, sizeof(int) * 64);
    graph->edges = (int **) malloc(sizeof(int *) * 64);
    for (int i = 0; i < 64; ++i) {
        graph->edges[i] = (int *) malloc(sizeof(int) * 64);
        memset(graph->edges[i], 0, sizeof(int) * 64);
    }
    graph->length = 0;
    graph->capacity = 64;
}

int isEmpty(GraphNode graph) {
    return !graph.length ? 1 : 0;
}

void addEdge(GraphNode *graph, int index, int edgeIndex, int weight) {
    if (index >= 0 && index < graph->length && edgeIndex >= 0 && edgeIndex < graph->length && index != edgeIndex) {
        graph->edges[index][edgeIndex] = weight;
    }
}

void addVertex(GraphNode *graph, int value) {
    if (graph->length >= graph->capacity) {
        graph->vertexes = (int *) realloc(graph->vertexes, sizeof(int) * (graph->capacity + 16));
        memset(graph->vertexes + graph->capacity, 0, sizeof(int) * 16);
        for (int i = 0; i < graph->capacity; ++i) {
            graph->edges[i] = (int *) realloc(graph->edges[i], sizeof(int) * (graph->capacity + 16));
            memset(graph->edges[i] + graph->capacity, 0, sizeof(int) * 16);
        }
        graph->edges = (int **) realloc(graph->edges, sizeof(int *) * (graph->capacity + 16));
        for (int i = graph->capacity; i < graph->capacity + 16; ++i) {
            graph->edges[i] = (int *) malloc(sizeof(int) * (graph->capacity + 16));
            memset(graph->edges[i], 0, sizeof(int) * (graph->capacity + 16));
        }
        graph->capacity += 16;
    }

    graph->vertexes[graph->length] = value;
    ++graph->length;
}

void eraseEdge(GraphNode *graph, int index, int edgeIndex) {
    if (index >= 0 && index < graph->length && edgeIndex >= 0 && edgeIndex < graph->length && index != edgeIndex) {
        graph->edges[index][edgeIndex] = 0;
    }
}

void eraseVertex(GraphNode *graph, int index) {
    if (index < 0 || index >= graph->length) {
        return;
    }

    for (int i = 0; i < index; ++i) {
        for (int j = index + 1; j < graph->length; ++j) {
            graph->edges[i][j - 1] = graph->edges[i][j];
        }
    }
    for (int i = index + 1; i < graph->length; ++i) {
        for (int j = 0; j < index; ++j) {
            graph->edges[i - 1][j] = graph->edges[i][j];
        }
        for (int j = index + 1; j < graph->length; ++j) {
            graph->edges[i - 1][j - 1] = graph->edges[i][j];
        }
    }

    for (int i = index + 1; i < graph->length; ++i) {
        graph->vertexes[i - 1] = graph->vertexes[i];
    }
    --graph->length;
}

void setEdge(GraphNode *graph, int index, int edgeIndex, int weight) {
    if (index >= 0 && index < graph->length && edgeIndex >= 0 && edgeIndex < graph->length && index != edgeIndex && graph->edges[index][edgeIndex]) {
        graph->edges[index][edgeIndex] = weight;
    }
}

void setVertex(GraphNode *graph, int index, int value) {
    if (index >= 0 && index < graph->length) {
        graph->vertexes[index] = value;
    }
}

int getEdge(GraphNode graph, int index, int edgeIndex) {
    if (index >= 0 && index < graph.length && edgeIndex >= 0 && edgeIndex < graph.length && index != edgeIndex && graph.edges[index][edgeIndex]) {
        return graph.edges[index][edgeIndex];
    }
    return 1 << 31;
}

int getVertex(GraphNode graph, int index) {
    if (index >= 0 && index < graph.length) {
        return graph.vertexes[index];
    }
    return 1 << 31;
}

void clear(GraphNode *graph) {
    memset(graph->vertexes, 0, sizeof(int) * graph->capacity);
    for (int i = 0; i < graph->capacity; ++i) {
        (graph->edges[i], 0, sizeof(int) * graph->capacity);
    }
    graph->length = 0;
}
