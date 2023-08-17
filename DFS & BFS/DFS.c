#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct {
    int vertices[MAX_VERTICES];
    int top;
} Stack;

void push(Stack *stack, int vertex) {
    stack->vertices[++stack->top] = vertex;
}

int pop(Stack *stack) {
    return stack->vertices[stack->top--];
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

void DFS(int adjacencyMatrix[][MAX_VERTICES], int numVertices, int startVertex) {
    int visited[MAX_VERTICES] = {0};
    Stack stack;
    stack.top = -1;
    push(&stack, startVertex);
    visited[startVertex] = 1;

    printf("DFS traversal starting from vertex %d: ", startVertex);

    while (!isEmpty(&stack)) {
        int currentVertex = pop(&stack);
        printf("%d ", currentVertex);

        for (int i = 0; i < numVertices; i++) {
            if (adjacencyMatrix[currentVertex][i] == 1 && !visited[i]) {
                push(&stack, i);
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}

int main() {
    int numVertices, startVertex;
    
    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);
    
    int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
    printf("Enter the adjacency matrix (1 if edge exists, 0 otherwise):\n");
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            scanf("%d", &adjacencyMatrix[i][j]);
        }
    }
    
    printf("Enter the start vertex: ");
    scanf("%d", &startVertex);
    
    DFS(adjacencyMatrix, numVertices, startVertex);
    
    return 0;
}