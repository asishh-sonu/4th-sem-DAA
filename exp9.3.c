#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_VERTICES 100

typedef struct {
    char name[20];
    int weight;
} Edge;

typedef struct {
    int count;
    int capacity;
    char **vertices;
    Edge **edges;
} Graph;

Graph *createGraph(int V) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->count = 0;
    graph->capacity = V;
    graph->vertices = (char **)malloc(V * sizeof(char *));
    graph->edges = (Edge **)malloc(V * sizeof(Edge *));
    for (int i = 0; i < V; i++) {
        graph->vertices[i] = NULL;
        graph->edges[i] = NULL;
    }
    return graph;
}

int findVertexIndex(Graph *graph, char *vertex) {
    for (int i = 0; i < graph->count; i++) {
        if (strcmp(graph->vertices[i], vertex) == 0) {
            return i;
        }
    }
    return -1;
}

void addVertex(Graph *graph, char *vertex) {
    if (graph->count == graph->capacity) {
        printf("Graph has reached maximum capacity.\n");
        return;
    }
    graph->vertices[graph->count] = (char *)malloc((strlen(vertex) + 1) * sizeof(char));
    strcpy(graph->vertices[graph->count], vertex);
    graph->edges[graph->count] = NULL;
    graph->count++;
}

void addEdge(Graph *graph, char *src, char *dest, int weight) {
    int srcIndex = findVertexIndex(graph, src);
    int destIndex = findVertexIndex(graph, dest);
    if (srcIndex == -1 || destIndex == -1) {
        printf("One or both vertices not found.\n");
        return;
    }
    Edge *edge = (Edge *)malloc(sizeof(Edge));
    edge->weight = weight;
    strcpy(edge->name, dest);
    graph->edges[srcIndex] = (Edge *)realloc(graph->edges[srcIndex], (graph->count + 1) * sizeof(Edge));
    graph->edges[srcIndex][graph->count - 1] = *edge;
}

void dijkstra(Graph *graph, char *src, int *dist) {
    int visited[MAX_VERTICES] = { 0 };
    for (int i = 0; i < graph->count; i++) {
        dist[i] = INT_MAX;
    }
    int srcIndex = findVertexIndex(graph, src);
    dist[srcIndex] = 0;
    for (int i = 0; i < graph->count - 1; i++) {
        int minDist = INT_MAX, minIndex = -1;
        for (int j = 0; j < graph->count; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                minIndex = j;
            }
        }
        visited[minIndex] = 1;
        for (int j = 0; j < graph->count; j++) {
            if (!visited[j] && graph->edges[minIndex] != NULL) {
                for (int k = 0; k < graph->count; k++) {
                    if (strcmp(graph->vertices[j], graph->edges[minIndex][k].name) == 0) {
                                            int alt = dist[minIndex] + graph->edges[minIndex][k].weight;
                    if (alt < dist[j]) {
                        dist[j] = alt;
                    }
                }
            }
        }
    }
}
}
int main() {
Graph *graph = createGraph(MAX_VERTICES);
int n;
char src[20], dest[20];
int weight;
printf("Enter the number of edges: ");
scanf("%d", &n);
printf("Enter the edges and their weights:\n");
for (int i = 0; i < n; i++) {
scanf("%s %s %d", src, dest, &weight);
if (findVertexIndex(graph, src) == -1) {
addVertex(graph, src);
}
if (findVertexIndex(graph, dest) == -1) {
addVertex(graph, dest);
}
addEdge(graph, src, dest, weight);
}
char start[20];
printf("Enter the starting vertex: ");
scanf("%s", start);
int dist[MAX_VERTICES];
dijkstra(graph, start, dist);
for (int i = 0; i < graph->count; i++) {
printf("Distance from %s to %s: %d\n", start, graph->vertices[i], dist[i]);
}
return 0;
}
