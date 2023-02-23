#include "read_file.h"
#include <time.h>

int min(int x, int y)
{
    return (x < y) ? x : y;
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (l < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int n)
{
    int currSize;
    int leftStart;

    for (currSize = 1; currSize < n; currSize *= 2)
    {
        for (leftStart = 0; leftStart < n - 1; leftStart += 2 * currSize)
        {
            int mid = min(leftStart + currSize - 1, n - 1);
            int rightEnd = min(leftStart + 2 * currSize - 1, n - 1);
            merge(arr, leftStart, mid, rightEnd);
        }
    }
}

int main(int argc, char **argv)
{
    clock_t start, end;
    FILE *filePtr = fopen("numbers.txt", "r");

    if (filePtr == NULL)
    {
        printf("Cannot open file numbers.txt!\n");
        return 1;
    }

    int n = find_length(filePtr);
    int arr[n];

    read_array(filePtr, n, arr);

    start = clock();
    mergeSort(arr, n);
    end = clock();

    int i;
    for (i = 0; i < n; i++)
        printf("%d\n", arr[i]);
    printf("\n");

    printf("Total time taken: %.6lf seconds\n\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}