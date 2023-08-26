#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100

int minKey(int key[], int mstSet[], int V) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; ++v)
        if (mstSet[v] == 0 && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

void printMST(int parent[], int graph[][MAX_VERTICES], int V) {
    printf("Edges in the MST:\n");
    int total_cost = 0;
    for (int i = 1; i < V; ++i) {
        printf("%d -- %d == %d\n", parent[i], i, graph[i][parent[i]]);
        total_cost += graph[i][parent[i]];
    }
    printf("Total cost of MST: %d\n", total_cost);
}

void primMST(int graph[][MAX_VERTICES], int V) {
    int parent[V];
    int key[V];
    int mstSet[V];
    for (int i = 0; i < V; ++i)
        key[i] = INT_MAX, mstSet[i] = 0;
    key[0] = 0;
    parent[0] = -1;
    for (int count = 0; count < V - 1; ++count) {
        int u = minKey(key, mstSet, V);
        mstSet[u] = 1;
        for (int v = 0; v < V; ++v)
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }
    printMST(parent, graph, V);
}

int main() {
    int V, E, src, dest, weight;
    int graph[MAX_VERTICES][MAX_VERTICES];
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &V);
    printf("Enter the number of edges in the graph: ");
    scanf("%d", &E);
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            graph[i][j] = 0;
    printf("Enter the edges with their weights (src dest weight):\n");
    for (int i = 0; i < E; ++i) {
        scanf("%d %d %d", &src, &dest, &weight);
        graph[src][dest] = graph[dest][src] = weight;
    }
    primMST(graph, V);
    return 0;
}
