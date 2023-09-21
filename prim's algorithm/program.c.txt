#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 100

// Structure to represent an edge in the graph
struct Edge {
    int source, destination, weight;
};

// Structure to represent a graph
struct Graph {
    int numVertices, numEdges;
    struct Edge edges[MAX_VERTICES];
};

void primMST(struct Graph* graph) {
    int numVertices = graph->numVertices;
    int parent[MAX_VERTICES]; // Array to store the parent of each vertex in the MST
    int key[MAX_VERTICES];    // Array to store the key values of vertices
    bool inMST[MAX_VERTICES]; // Array to track whether a vertex is in the MST

    // Initialize key values and inMST flags
    for (int i = 0; i < numVertices; i++) {
        key[i] = INT_MAX;
        inMST[i] = false;
    }

    // Start with the first vertex as the root
    key[0] = 0;
    parent[0] = -1;

    // Construct the MST with (V-1) edges
    for (int count = 0; count < numVertices - 1; count++) {
        // Find the vertex with the minimum key value that is not in the MST
        int minKey = INT_MAX, minIndex = -1;
        for (int v = 0; v < numVertices; v++) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                minIndex = v;
            }
        }

        // Add the selected vertex to the MST
        inMST[minIndex] = true;

        // Update key values and parent pointers for adjacent vertices
        for (int e = 0; e < graph->numEdges; e++) {
            if (graph->edges[e].source == minIndex && !inMST[graph->edges[e].destination] && graph->edges[e].weight < key[graph->edges[e].destination]) {
                parent[graph->edges[e].destination] = minIndex;
                key[graph->edges[e].destination] = graph->edges[e].weight;
            }
        }
    }

    // Print the MST
    printf("Edge\tWeight\n");
    for (int i = 1; i < numVertices; i++) {
        printf("%d - %d\t%d\n", parent[i], i, key[i]);
    }
}

int main() {
    struct Graph graph;
    int numVertices, numEdges;

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

    primMST(&graph);

    return 0;
}
