#include "read_file.h"
#include <time.h>

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high)
{
    srand(time(0));
    int random = low + rand() % (high - low);

    swap(&arr[random], &arr[low]);

    int pivot = arr[low];
    int i = low - 1;
    int j = high + 1;

    while (1)
    {
        do
        {
            i++;
        } while (arr[i] < pivot);

        do
        {
            j--;
        } while (arr[j] > pivot);

        if (i >= j)
            return j;

        swap(&arr[i], &arr[j]);
    }
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
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
    quickSort(arr, 0, n - 1);
    end = clock();

    int i;
    for (i = 0; i < n; i++)
        printf("%d\n", arr[i]);
    printf("\n");

    printf("Total time taken: %.6lf seconds\n\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}