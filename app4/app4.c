#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF 99999
#define MAX_CITIES 100

// Structure to represent a directed edge
struct Edge {
    int source, destination, weight;
};

// Function to perform the Bellman-Ford algorithm
void bellmanFord(int numCities, int numEdges, struct Edge edges[], int source) {
    int distances[MAX_CITIES];
    
    // Initialize distances
    for (int i = 0; i < numCities; ++i) {
        distances[i] = INF;
    }
    distances[source] = 0;

    // Relaxation step
    for (int i = 1; i <= numCities - 1; ++i) {
        for (int j = 0; j < numEdges; ++j) {
            int u = edges[j].source;
            int v = edges[j].destination;
            int weight = edges[j].weight;
            
            if (distances[u] != INF && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
            }
        }
    }

    // Check for negative weight cycles
    for (int j = 0; j < numEdges; ++j) {
        int u = edges[j].source;
        int v = edges[j].destination;
        int weight = edges[j].weight;
        
        if (distances[u] != INF && distances[u] + weight < distances[v]) {
            printf("Graph contains negative weight cycle!\n");
            return;
        }
    }

    // Print shortest distances
    printf("Shortest distances from source %d:\n", source);
    for (int i = 0; i < numCities; ++i) {
        printf("City %d: %d\n", i, distances[i]);
    }
}

int main() {
    int numCities, numEdges, source;
    struct Edge edges[MAX_CITIES];
    
    printf("Enter the number of cities: ");
    scanf("%d", &numCities);
    
    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    printf("Enter the source city: ");
    scanf("%d", &source);

    printf("Enter the edges (source destination weight):\n");
    for (int i = 0; i < numEdges; ++i) {
        scanf("%d %d %d", &edges[i].source, &edges[i].destination, &edges[i].weight);
    }
    
    bellmanFord(numCities, numEdges, edges, source);

    return 0;
}
