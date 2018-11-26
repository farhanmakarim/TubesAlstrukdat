#ifndef GRAPH_H
#define GRAPH_H

#include "maplocation.h"

#define MAX_GRAPH_EDGES 32

typedef MapLocation GraphVertex;

typedef char Direction;

typedef struct GraphEdge {
    GraphVertex start;
    Direction direction;
    GraphVertex end;
}
GraphEdge;

typedef struct Graph {
    GraphEdge edges[MAX_GRAPH_EDGES];
    int edge_count;
}
Graph;

void GraphCreateEmpty(Graph *graph);
void GraphAddEdge(Graph *graph, GraphEdge edge);

#endif