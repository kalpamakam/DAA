#include <stdio.h>

#define MAX_NODES 100

int visited[MAX_NODES];
int adjacencyMatrix[MAX_NODES][MAX_NODES];
int numNodes;

// Depth-First Search function
void DFS(int node) {
    visited[node] = 1;
    printf("%d ", node);

    for (int i = 0; i < numNodes; ++i) {
        if (adjacencyMatrix[node][i] && !visited[i]) {
            DFS(i);
        }
    }
}

// Function to find and display connected components
void findConnectedComponents() {
    for (int i = 0; i < numNodes; ++i) {
        if (!visited[i]) {
            printf("Connected Component: ");
            DFS(i);
            printf("\n");
        }
    }
}

int main() {
    printf("Enter the number of nodes: ");
    scanf("%d", &numNodes);

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < numNodes; ++i) {
        for (int j = 0; j < numNodes; ++j) {
            scanf("%d", &adjacencyMatrix[i][j]);
        }
    }

    // Initialize visited array
    for (int i = 0; i < numNodes; ++i) {
        visited[i] = 0;
    }

    printf("Connected Components:\n");
    findConnectedComponents();

    return 0;
}
