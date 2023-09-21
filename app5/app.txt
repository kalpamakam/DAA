#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define V 6 

int min(int a, int b) {
    return a < b ? a : b;
}

bool bfs(int rGraph[V][V], int s, int t, int parent[]) {
    bool visited[V];
    for (int i = 0; i < V; i++) {
        visited[i] = false;
    }

    int queue[V];
    int front = 0, rear = 0;
    queue[rear++] = s;
    visited[s] = true;
    parent[s] = -1;

    while (front != rear) {
        int u = queue[front++];
        for (int v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                queue[rear++] = v;
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return visited[t];
}

int fordFulkerson(int graph[V][V], int s, int t) {
    int rGraph[V][V]; 
    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            rGraph[u][v] = graph[u][v];
        }
    }

    int parent[V]; 

    int maxFlow = 0; 

    while (bfs(rGraph, s, t, parent)) {
        int pathFlow = INT_MAX;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, rGraph[u][v]);
        }

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= pathFlow;
            rGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main() {
    int graph[V][V] = {
        {0, 16, 13, 0, 0, 0},
        {0, 0, 10, 12, 0, 0},
        {0, 4, 0, 0, 14, 0},
        {0, 0, 9, 0, 0, 20},
        {0, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 0, 0}
    };

    int source = 0;
    int sink = 5;

    int maxFlow = fordFulkerson(graph, source, sink);

    printf("Maximum flow from source to sink is %d\n", maxFlow);

    return 0;
}
