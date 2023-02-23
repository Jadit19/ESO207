#include "read_file.h"
#include <time.h>

void buildMaxHeap(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        if (arr[i] > arr[(i - 1) / 2])
        {
            j = i;
            while (arr[j] > arr[(j - 1) / 2])
            {
                int temp = arr[j];
                arr[j] = arr[(j - 1) / 2];
                arr[(j - 1) / 2] = temp;
                j = (j - 1) / 2;
            }
        }
    }
}

void heapSort(int arr[], int n)
{
    buildMaxHeap(arr, n);

    int i;
    for (i = n - 1; i > 0; i--)
    {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        int j = 0, index;
        do
        {
            index = (2 * j + 1);
            if (arr[index] < arr[index + 1] && index < (i - 1))
                index++;

            if (arr[j] < arr[index] && index < i)
            {
                int temp1 = arr[j];
                arr[j] = arr[index];
                arr[index] = temp;
            }

            j = index;
        } while (index < i);
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
    heapSort(arr, n);
    end = clock();

    int i;
    for (i = 0; i < n; i++)
        printf("%d\n", arr[i]);
    printf("\n");

    printf("Total time taken: %.6lf seconds\n\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}