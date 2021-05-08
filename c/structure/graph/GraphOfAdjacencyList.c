#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int index;
    int weight;
    struct node *next;
} EdgeNode;

typedef struct {
    int value;
    EdgeNode *next;
} VertexNode;

typedef VertexNode *pNode;

typedef struct {
    pNode *graphs;
    int length;
    int capacity;
} GraphNode;

void create(GraphNode *graph) {
    graph->graphs = (pNode *) malloc(sizeof(pNode) * 64);
    for (int i = 0; i < 64; ++i) {
        graph->graphs[i] = NULL;
    }
    graph->length = 0;
    graph->capacity = 64;
}

int isEmpty(GraphNode graph) {
    return !graph.length ? 1 : 0;
}

void addEdge(GraphNode *graph, int index, int edgeIndex, int weight) {
    if (index < 0 || index >= graph->length || edgeIndex < 0 || edgeIndex >= graph->length || index == edgeIndex) {
        return;
    }

    if (!graph->graphs[index]->next) {
        graph->graphs[index]->next = (EdgeNode *) malloc(sizeof(EdgeNode));
        graph->graphs[index]->next->index = edgeIndex;
        graph->graphs[index]->next->weight = weight;
        graph->graphs[index]->next->next = NULL;
        return;
    }

    EdgeNode *edge = graph->graphs[index]->next;
    while (edge->next) {
        if (edgeIndex == edge->index) {
            edge->weight = weight;
            return;
        }
        edge = edge->next;
    }
    if (edgeIndex == edge->index) {
        edge->weight = weight;
    } else {
        edge->next = (EdgeNode *) malloc(sizeof(EdgeNode));
        edge->next->index = edgeIndex;
        edge->next->weight = weight;
        edge->next->next = NULL;
    }
}

void addVertex(GraphNode *graph, int value) {
    if (graph->length >= graph->capacity) {
        graph->graphs = (pNode *) realloc(graph->graphs, sizeof(pNode) * (graph->capacity + 16));
        for (int i = graph->capacity; i < graph->capacity + 16; ++i) {
            graph->graphs[i] = NULL;
        }
        graph->capacity += 16;
    }

    graph->graphs[graph->length] = (pNode) malloc(sizeof(VertexNode));
    graph->graphs[graph->length]->value = value;
    graph->graphs[graph->length]->next = NULL;
    ++graph->length;
}

void eraseEdge(GraphNode *graph, int index, int edgeIndex) {
    if (index < 0 || index >= graph->length || edgeIndex < 0 || edgeIndex >= graph->length || index == edgeIndex) {
        return;
    }

    EdgeNode *edge = graph->graphs[index]->next;
    if (!edge) {
        return;
    }
    if (edgeIndex == edge->index) {
        graph->graphs[index]->next = edge->next;
        return;
    }

    while (edge->next) {
        if (edgeIndex == edge->next->index) {
            edge->next = edge->next->next;
            return;
        }
        edge = edge->next;
    }
}

void eraseVertex(GraphNode *graph, int index) {
    if (index < 0 || index >= graph->length) {
        return;
    }

    for (int i = 0; i < graph->length; ++i) {
        if (i != index) {
            eraseEdge(graph, i, index);
        }
    }

    for (int i = index + 1; i < graph->length; ++i) {
        graph->graphs[i - 1] = graph->graphs[i];
    }
    --graph->length;
    graph->graphs[graph->length] = NULL;
}

void setEdge(GraphNode *graph, int index, int edgeIndex, int weight) {
    if (index < 0 || index >= graph->length || edgeIndex < 0 || edgeIndex >= graph->length || index == edgeIndex) {
        return;
    }

    EdgeNode *edge = graph->graphs[index]->next;
    while (edge && edgeIndex != edge->index) {
        edge = edge->next;
    }

    if (edge) {
        edge->weight = weight;
    }
}

void setVertex(GraphNode *graph, int index, int value) {
    if (index >= 0 && index < graph->length) {
        graph->graphs[index]->value = value;
    }
}

int getEdge(GraphNode graph, int index, int edgeIndex) {
    if (index < 0 || index >= graph.length || edgeIndex < 0 || edgeIndex >= graph.length || index == edgeIndex) {
        return 1 << 31;
    }

    EdgeNode *edge = graph.graphs[index]->next;
    while (edge && edgeIndex != edge->index) {
        edge = edge->next;
    }

    if (edge) {
        return edge->weight;
    }
    return 1 << 31;
}

int getVertex(GraphNode graph, int index) {
    if (index >= 0 && index < graph.length) {
        return graph.graphs[index]->value;
    }
    return 1 << 31;
}

void clear(GraphNode *graph) {
    for (int i = 0; i < graph->capacity; ++i) {
        graph->graphs[i] = NULL;
    }
    graph->length = 0;
}
