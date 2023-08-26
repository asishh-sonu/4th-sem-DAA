#include <stdio.h>

int binary_search(int arr[], int l, int r, int x) {
  if (r >= l) {
    int mid = l + (r - l) / 2;
    if (arr[mid] == x)
      return mid;
    if (arr[mid] > x)
      return binary_search(arr, l, mid - 1, x);
    return binary_search(arr, mid + 1, r, x);
  }
  return -1;
}

int main() {
  int n, x, i, result;
  printf("Enter the number of elements in the array: ");
  scanf("%d", &n);
  int arr[n];
  printf("Enter the elements of the array in ascending order: ");
  for (i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }
  printf("Enter the element to search for: ");
  scanf("%d", &x);
  result = binary_search(arr, 0, n - 1, x);
  (result == -1) ? printf("Element is not present in array")
                 : printf("Element is present at index %d", result);
  return 0;
}

