#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

struct Node {
    int value;
    struct Node* next;
};

struct Graph {
    int numNodes;
    struct Node* adjacencyList[MAX_NODES];
    int inDegree[MAX_NODES];
};

struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void addEdge(struct Graph* graph, int from, int to) {
    struct Node* newNode = createNode(to);
    newNode->next = graph->adjacencyList[from];
    graph->adjacencyList[from] = newNode;
    graph->inDegree[to]++;
}

void topologicalSort(struct Graph* graph, int startVertex) {
    int queue[MAX_NODES];
    int front = 0, rear = -1;
    int result[MAX_NODES];
    int resultIndex = 0;

    for (int i = 0; i < graph->numNodes; i++) {
        if (graph->inDegree[i] == 0) {
            queue[++rear] = i;
        }
    }

    while (front <= rear) {
        int node = queue[front++];
        result[resultIndex++] = node;

        struct Node* current = graph->adjacencyList[node];
        while (current != NULL) {
            graph->inDegree[current->value]--;
            if (graph->inDegree[current->value] == 0) {
                queue[++rear] = current->value;
            }
            current = current->next;
        }
    }

    printf("Topological Order starting from vertex %d: ", startVertex);
    for (int i = 0; i < resultIndex; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
}

int main() {
    struct Graph graph;
    printf("Enter the number of nodes in the graph: ");
    scanf("%d", &graph.numNodes);

    for (int i = 0; i < MAX_NODES; i++) {
        graph.adjacencyList[i] = NULL;
        graph.inDegree[i] = 0;
    }

    printf("Enter the adjacency matrix (0 or 1):\n");
    for (int i = 0; i < graph.numNodes; i++) {
        for (int j = 0; j < graph.numNodes; j++) {
            int value;
            scanf("%d", &value);
            if (value == 1) {
                addEdge(&graph, i, j);
            }
        }
    }

    int startVertex;
    printf("Enter the starting vertex: ");
    scanf("%d", &startVertex);

    topologicalSort(&graph, startVertex);

    return 0;
}