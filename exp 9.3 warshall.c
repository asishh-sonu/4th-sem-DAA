#include <stdio.h>
#define INF 99999
#define MAX 100

int main() {
    int adj[MAX][MAX], dist[MAX][MAX];
    int n, i, j, k;

    
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    
    printf("Enter the adjacency matrix:\n");
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            scanf("%d", &adj[i][j]);
            if(adj[i][j] == 0) {
                dist[i][j] = INF;  
            }
            else {
                dist[i][j] = adj[i][j]; 
            }
        }
    }

    
    for(k=0; k<n; k++) {
        for(i=0; i<n; i++) {
            for(j=0; j<n; j++) {
                if(dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    
    printf("Shortest distances between all pairs of vertices:\n");
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            if(dist[i][j] == INF) {
                printf("INF ");
            }
            else {
                printf("%d ", dist[i][j]);
            }
        }
        printf("\n");
    }

    return 0;
}
