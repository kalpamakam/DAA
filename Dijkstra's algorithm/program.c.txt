#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 100

// Structure to represent a weighted edge in the graph
struct Edge {
    int destination, weight;
};

// Structure to represent a graph
struct Graph {
    int numVertices;
    struct Edge edges[MAX_VERTICES][MAX_VERTICES];
};

void dijkstra(struct Graph* graph, int source) {
    int numVertices = graph->numVertices;
    int distance[MAX_VERTICES];   // Array to store the shortest distance from source to each vertex
    bool visited[MAX_VERTICES];   // Array to track whether a vertex has been visited

    // Initialize distance array and visited array
    for (int i = 0; i < numVertices; i++) {
        distance[i] = INT_MAX;
        visited[i] = false;
    }

    // Distance from source to itself is always 0
    distance[source] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < numVertices - 1; count++) {
        // Find the vertex with the minimum distance value among unvisited vertices
        int minDistance = INT_MAX, minIndex = -1;
        for (int v = 0; v < numVertices; v++) {
            if (!visited[v] && distance[v] < minDistance) {
                minDistance = distance[v];
                minIndex = v;
            }
        }

        // Mark the selected vertex as visited
        visited[minIndex] = true;

        // Update the distance values of adjacent vertices
        for (int v = 0; v < numVertices; v++) {
            if (!visited[v] && graph->edges[minIndex][v].weight > 0 &&
                distance[minIndex] != INT_MAX && distance[minIndex] + graph->edges[minIndex][v].weight < distance[v]) {
                distance[v] = distance[minIndex] + graph->edges[minIndex][v].weight;
            }
        }
    }

    // Print the shortest distances from the source
    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < numVertices; i++) {
        printf("%d\t%d\n", i, distance[i]);
    }
}

int main() {
    struct Graph graph;
    int numVertices, source;

    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    graph.numVertices = numVertices;

    printf("Enter the adjacency matrix (weight of edges, 0 for no edge):\n");
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            scanf("%d", &graph.edges[i][j].weight);
        }
    }

    printf("Enter the source vertex: ");
    scanf("%d", &source);

    dijkstra(&graph, source);

    return 0;
}
