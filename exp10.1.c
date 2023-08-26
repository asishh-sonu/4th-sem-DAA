#include <stdio.h>
#include <stdlib.h>

#define MAXN 100

int n, ans;
int col[MAXN], diag1[MAXN * 2], diag2[MAXN * 2];

void search(int y) {
    if (y == n) {
        ans++;
        return;
    }
    for (int x = 0; x < n; x++) {
        if (col[x] || diag1[x+y] || diag2[x-y+n-1]) continue;
        col[x] = diag1[x+y] = diag2[x-y+n-1] = 1;
        search(y+1);
        col[x] = diag1[x+y] = diag2[x-y+n-1] = 0;
    }
}

int main() {
    printf("Enter the size of the board: ");
    scanf("%d", &n);
    search(0);
    printf("There are %d solutions to the %d-Queens problem.\n", ans, n);
    return 0;
}

