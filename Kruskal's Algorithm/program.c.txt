#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define MAX_EDGES 100

// Structure to represent an edge in the graph
struct Edge {
    int source, destination, weight;
};

// Structure to represent a graph
struct Graph {
    int numVertices, numEdges;
    struct Edge edges[MAX_EDGES];
};

// Function to compare edges by weight (used for sorting)
int compareEdges(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

int parent[MAX_VERTICES];

// Function to find the parent of a vertex (uses path compression)
int find(int vertex) {
    if (parent[vertex] == -1)
        return vertex;
    return find(parent[vertex]);
}

// Function to perform union of two subsets (uses rank to determine which tree to attach)
void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    parent[rootX] = rootY;
}

void kruskalMST(struct Graph* graph) {
    int numVertices = graph->numVertices;
    struct Edge resultMST[MAX_VERTICES];
    int numEdgesInMST = 0;

    // Sort the edges in non-decreasing order of their weights
    qsort(graph->edges, graph->numEdges, sizeof(struct Edge), compareEdges);

    // Initialize parent array for disjoint-set union-find
    for (int i = 0; i < numVertices; i++) {
        parent[i] = -1;
    }

    // Iterate through all sorted edges and add them to the MST if they don't create a cycle
    for (int i = 0; i < graph->numEdges; i++) {
        struct Edge currentEdge = graph->edges[i];

        int rootSource = find(currentEdge.source);
        int rootDestination = find(currentEdge.destination);

        if (rootSource != rootDestination) {
            resultMST[numEdgesInMST++] = currentEdge;
            unionSets(rootSource, rootDestination);
        }
    }

    // Print the MST
    printf("Edges in Minimum Spanning Tree (MST):\n");
    for (int i = 0; i < numEdgesInMST; i++) {
        printf("%d - %d : %d\n", resultMST[i].source, resultMST[i].destination, resultMST[i].weight);
    }
}

int main() {
    struct Graph graph;
    int numVertices, numEdges;

    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    graph.numVertices = numVertices;

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    graph.numEdges = numEdges;

    printf("Enter the edges (source, destination, weight):\n");
    for (int i = 0; i < numEdges; i++) {
        scanf("%d %d %d", &graph.edges[i].source, &graph.edges[i].destination, &graph.edges[i].weight);
    }

    kruskalMST(&graph);

    return 0;
}
