#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

int max(int a, int b) {
    return (a > b) ? a : b;
}

void LCS(char *string1, char *string2, int length1, int length2) {
    int matrix[MAX_LENGTH+1][MAX_LENGTH+1];
    int i, j;

    // Initialize matrix with zeros
    for (i = 0; i <= length1; i++) {
        for (j = 0; j <= length2; j++) {
            matrix[i][j] = 0;
        }
    }

    // Fill in the matrix using dynamic programming
    for (i = 1; i <= length1; i++) {
        for (j = 1; j <= length2; j++) {
            if (string1[i-1] == string2[j-1]) {
                matrix[i][j] = matrix[i-1][j-1] + 1;
            } else {
                matrix[i][j] = max(matrix[i-1][j], matrix[i][j-1]);
            }
        }
    }

    // Print the longest common subsequence
    int index = matrix[length1][length2];
    char lcs[index+1];
    lcs[index] = '\0';
    i = length1;
    j = length2;
    while (i > 0 && j > 0) {
        if (string1[i-1] == string2[j-1]) {
            lcs[--index] = string1[i-1];
            i--;
            j--;
        } else if (matrix[i-1][j] > matrix[i][j-1]) {
            i--;
        } else {
            j--;
        }
    }
    printf("The longest common subsequence is %s\n", lcs);
}

int main() {
    char string1[MAX_LENGTH];
    char string2[MAX_LENGTH];

    printf("Enter the first string: ");
    scanf("%s", string1);

    printf("Enter the second string: ");
    scanf("%s", string2);

    int length1 = strlen(string1);
    int length2 = strlen(string2);

    LCS(string1, string2, length1, length2);

    return 0;
}

