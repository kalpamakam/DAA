#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(char arr[][12], int low, int mid, int high) {
    int i, j, k;
    int n1 = mid - low + 1;
    int n2 = high - mid;

    char L[n1][12], R[n2][12];

    for (i = 0; i < n1; i++)
        strcpy(L[i], arr[low + i]);
    for (j = 0; j < n2; j++)
        strcpy(R[j], arr[mid + 1 + j]);

    i = 0;
    j = 0;
    k = low;

    while (i < n1 && j < n2) {
        if (strcmp(L[i], R[j]) <= 0) {
            strcpy(arr[k], L[i]);
            i++;
        } else {
            strcpy(arr[k], R[j]);
            j++;
        }
        k++;
    }

    while (i < n1) {
        strcpy(arr[k], L[i]);
        i++;
        k++;
    }

    while (j < n2) {
        strcpy(arr[k], R[j]);
        j++;
        k++;
    }
}

void mergeSort(char arr[][12], int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

int main() {
    int n;

    printf("Enter the number of mobile numbers in the contact list: ");
    scanf("%d", &n);

    char mobileNumbers[n][12];

    printf("Enter the mobile numbers:\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", mobileNumbers[i]);
    }

    mergeSort(mobileNumbers, 0, n - 1);

    printf("\nSorted list of mobile numbers:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", mobileNumbers[i]);
    }

    return 0;
}