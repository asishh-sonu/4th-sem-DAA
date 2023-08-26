#include<stdio.h>
#include<stdlib.h>

// function to compare two activities based on their finish time
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void printMaxActivities(int start[], int finish[], int n) {
    // Sort activities based on their finish time
    qsort(finish, n, sizeof(int), compare);
  
    printf("The following activities are selected:\n");
    
    // Select the first activity
    int i = 0;
    printf("%d ", i);
  
    // Iterate over the remaining activities
    for (int j = 1; j < n; j++) {
        // If the start time of the current activity is greater than or equal to the finish time of the previously selected activity
        if (start[j] >= finish[i]) {
            printf("%d ", j);
            i = j;
        }
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of activities: ");
    scanf("%d", &n);
    
    int start[n], finish[n];
    printf("Enter the start time and finish time of each activity:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &start[i], &finish[i]);
    }
    
    printMaxActivities(start, finish, n);
    
    return 0;
}

