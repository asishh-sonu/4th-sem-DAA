#include <stdio.h>
#include <string.h>
#define INF 99999
#define MAX_SIZE 100

void dijkstra(int n, int graph[][n], char *src) {
    int dist[n];
    int visited[n];
    int i, j, min_idx;

    // Initialize the distance array and visited array
    for (i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }

    // Find the index of the source vertex
    int src_idx = -1;
    for (i = 0; i < n; i++) {
        if (strcmp(src,vertex_names[i]) == 0) {
            src_idx = i;
            break;
        }
    }

    // Set the distance to the source vertex as 0
    dist[src_idx] = 0;

    // Apply Dijkstra's algorithm
    for (i = 0; i < n-1; i++) {
        // Find the vertex with minimum distance among the unvisited vertices
        min_idx = -1;
        for (j = 0; j < n; j++) {
            if (!visited[j] && (min_idx == -1 || dist[j] < dist[min_idx])) {
                min_idx = j;
            }
        }

        // Mark the minimum distance vertex as visited
        visited[min_idx] = 1;

        // Update the distances of the adjacent vertices of the minimum distance vertex
        for (j = 0; j < n; j++) {
            if (graph[min_idx][j] != INF && dist[min_idx] + graph[min_idx][j] < dist[j]) {
                dist[j] = dist[min_idx] + graph[min_idx][j];
            }
        }
    }

    // Print the distance of each vertex from the source vertex
    printf("The following table shows the distance of each vertex from the source vertex:\n");
    printf("Vertex\tDistance\n");
    for (i = 0; i < n; i++) {
        printf("%s\t", vertex_names[i]);
        if (dist[i] == INF) {
            printf("INF\n");
        } else {
            printf("%d\n", dist[i]);
        }
    }
}

int main() {
    int n, i, j;
    char src[MAX_SIZE];

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    int graph[n][n];
    char vertex_names[n][MAX_SIZE];

    printf("Enter the names of the vertices:\n");
    for (i = 0; i < n; i++) {
        scanf("%s", vertex_names[i]);
    }

    printf("Enter the adjacency matrix of the graph:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
            if (graph[i][j] == -1) {
                graph[i][j] = INF;
            }
        }
    }

    printf("Enter the source vertex: ");
    scanf("%s", src);

    dijkstra(n, graph, src);

    return 0;
}

