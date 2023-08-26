#include <stdio.h>

// function to implement activity selection problem
void activitySelection(int start[], int end[], int n)
{
    int i, j;
    // select the first activity
    printf("Selected activity: %d\n", 0);
    i = 0;
    // iterate over remaining activities
    for (j = 1; j < n; j++)
    {
        // if start time of current activity is greater than or equal to end time of previous activity
        if (start[j] >= end[i])
        {
            // select the current activity
            printf("Selected activity: %d\n", j);
            i = j;
        }
    }
}

int main()
{
    int n, i;
    printf("Enter the number of activities: ");
    scanf("%d", &n);

    int start[n], end[n];
    // get input for start and end time of each activity
    for (i = 0; i < n; i++)
    {
        printf("Enter the start and end time of activity %d: ", i + 1);
        scanf("%d %d", &start[i], &end[i]);
    }

    // call the activity selection function
    activitySelection(start, end, n);

    return 0;
}
