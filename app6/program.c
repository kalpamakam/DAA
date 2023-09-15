#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_LOCATIONS 100

int numLocations;
int distances[MAX_LOCATIONS][MAX_LOCATIONS];
bool visited[MAX_LOCATIONS];
int parent[MAX_LOCATIONS];

void initialize() {
    for (int i = 0; i < numLocations; ++i) {
        visited[i] = false;
        parent[i] = -1;
    }
}

int findMinKey(int keys[]) {
    int minKey = INT_MAX;
    int minIndex = -1;

    for (int i = 0; i < numLocations; ++i) {
        if (!visited[i] && keys[i] < minKey) {
            minKey = keys[i];
            minIndex = i;
        }
    }

    return minIndex;
}

void primMST() {
    initialize();
    int keys[numLocations];

    for (int i = 0; i < numLocations; ++i) {
        keys[i] = INT_MAX;
    }

    keys[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < numLocations - 1; ++count) {
        int u = findMinKey(keys);
        visited[u] = true;

        for (int v = 0; v < numLocations; ++v) {
            if (distances[u][v] && !visited[v] && distances[u][v] < keys[v]) {
                parent[v] = u;
                keys[v] = distances[u][v];
            }
        }
    }
}

void printMST() {
    printf("Minimum Spanning Tree edges:\n");
    for (int i = 1; i < numLocations; ++i) {
        printf("Location %d - Location %d\n", parent[i], i);
    }
}

int main() {
    printf("Enter the number of locations: ");
    scanf("%d", &numLocations);

    printf("Enter the distances between locations:\n");
    for (int i = 0; i < numLocations; ++i) {
        for (int j = 0; j < numLocations; ++j) {
            scanf("%d", &distances[i][j]);
        }
    }

    primMST();
    printMST();

    return 0;
}