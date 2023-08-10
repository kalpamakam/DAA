#include <stdio.h>
#include <string.h>

void swap(char *a, char *b) {
    char temp[100];
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}

int partition(char arr[][100], int low, int high) {
    char pivot[100];
    strcpy(pivot, arr[high]);

    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (strcmp(arr[j], pivot) < 0) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(char arr[][100], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int n;

    printf("Enter the number of names in the attendance register: ");
    scanf("%d", &n);

    char names[n][100];

    printf("Enter the names:\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", names[i]);
    }

    quickSort(names, 0, n - 1);

    printf("\nSorted list of names:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", names[i]);
    }

    return 0;
}