#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100
#define MAX_EDGES 100

struct Edge {
    int source, destination, weight;
};

struct Graph {
    int numVertices, numEdges;
    struct Edge edges[MAX_EDGES];
};

void bellmanFord(struct Graph* graph, int source) {
    int numVertices = graph->numVertices;
    int numEdges = graph->numEdges;
    int distance[MAX_VERTICES];

    // Initialize distances from the source to all vertices as infinity
    for (int i = 0; i < numVertices; i++) {
        distance[i] = INT_MAX;
    }

    // Set the distance to the source vertex to 0
    distance[source] = 0;

    // Relax all edges repeatedly to find the shortest path
    for (int i = 0; i < numVertices - 1; i++) {
        for (int j = 0; j < numEdges; j++) {
            int u = graph->edges[j].source;
            int v = graph->edges[j].destination;
            int w = graph->edges[j].weight;

            if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
            }
        }
    }

    // Check for negative weight cycles
    for (int i = 0; i < numEdges; i++) {
        int u = graph->edges[i].source;
        int v = graph->edges[i].destination;
        int w = graph->edges[i].weight;

        if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
            printf("Graph contains a negative weight cycle\n");
            return;
        }
    }

    // Print the shortest distances
    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < numVertices; i++) {
        printf("%d\t%d\n", i, distance[i]);
    }
}

int main() {
    struct Graph graph;
    int numVertices, numEdges, source;

    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    graph.numVertices = numVertices;
    graph.numEdges = numEdges;

    printf("Enter the edges (source, destination, weight):\n");
    for (int i = 0; i < numEdges; i++) {
        scanf("%d %d %d", &graph.edges[i].source, &graph.edges[i].destination, &graph.edges[i].weight);
    }

    printf("Enter the source vertex: ");
    scanf("%d", &source);

    bellmanFord(&graph, source);

    return 0;
