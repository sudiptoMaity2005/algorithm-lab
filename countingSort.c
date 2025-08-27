#include <stdio.h>
#include <stdlib.h>

void countingSort(int arr[], int n) {
    int i;
    int max = arr[0];

    // Find the maximum element
    for (i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    // Create count array
    int *count = (int *)calloc(max + 1, sizeof(int));
    int *output = (int *)malloc(n * sizeof(int));

    // Store count of each element
    for (i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    // Update count array to store positions
    for (i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // Copy sorted array to original
    for (i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(count);
    free(output);
}

int main() {
    int n, i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements (non-negative integers): ", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    countingSort(arr, n);

    printf("Sorted array: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
