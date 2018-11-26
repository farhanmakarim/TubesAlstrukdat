#include "graph.h"

void GraphCreateEmpty(Graph *graph) {
    graph->edge_count = 0;
}

void GraphAddEdge(Graph *graph, GraphEdge edge) {
    graph->edges[graph->edge_count] = edge;
    ++graph->edge_count;
}