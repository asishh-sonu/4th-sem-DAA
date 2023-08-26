#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Struct to represent a weighted edge in the graph
struct Edge {
    char src, dest;
    int weight;
};

// Struct to represent the graph
struct Graph {
    int V, E;
    struct Edge* edges;
};

// Function to create a graph with V vertices and E edges
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (struct Edge*) malloc(E * sizeof(struct Edge));
    return graph;
}

// Function to relax an edge
void relax(struct Graph* graph, int u, int v, int w, int* dist) {
    if (dist[u] != INT_MAX && dist[v] > dist[u] + w) {
        dist[v] = dist[u] + w;
    }
}

// Function to implement the Bellman-Ford algorithm
void bellmanFord(struct Graph* graph, char src, int* dist) {
    // Initialize distance values
    for (int i = 0; i < graph->V; i++) {
        dist[i] = INT_MAX;
    }
    dist[src - 'a'] = 0;

    // Relax all edges |V| - 1 times
    for (int i = 1; i <= graph->V - 1; i++) {
        for (int j = 0; j < graph->E; j++) {
            char u = graph->edges[j].src;
            char v = graph->edges[j].dest;
            int w = graph->edges[j].weight;
            int uIndex = u - 'a', vIndex = v - 'a';
            relax(graph, uIndex, vIndex, w, dist);
        }
    }

    // Check for negative-weight cycles
    for (int i = 0; i < graph->E; i++) {
        char u = graph->edges[i].src;
        char v = graph->edges[i].dest;
        int w = graph->edges[i].weight;
        int uIndex = u - 'a', vIndex = v - 'a';
        if (dist[uIndex] != INT_MAX && dist[vIndex] > dist[uIndex] + w) {
            printf("Graph contains negative-weight cycle\n");
            return;
        }
    }

    // Print the shortest distances
    printf("Vertex Distance from Source\n");
    for (int i = 0; i < graph->V; i++) {
        printf("%c\t\t\t%d\n", i + 'a', dist[i]);
    }
}

int main() {
    int V, E;
    printf("Enter the number of vertices and edges in the graph: ");
    scanf("%d %d", &V, &E);

    // Create the graph
    struct Graph* graph = createGraph(V, E);

    // Get the edges of the graph
    for (int i = 0; i < E; i++) {
        char src, dest;
        int weight;
        printf("Enter the source, destination, and weight of edge %d: ", i + 1);
        scanf(" %c %c %d", &src, &dest, &weight);
        graph->edges[i].src = src;
        graph->edges[i].dest = dest;
        graph->edges[i].weight = weight;
    }

        // Get the source vertex
    char src;
    printf("Enter the source vertex: ");
    scanf(" %c", &src);

    // Run the Bellman-Ford algorithm
    int dist[V];
    bellmanFord(graph, src, dist);

    // Free the allocated memory
    free(graph->edges);
    free(graph);

    return 0;
}
