#include "read_file.h"
#include <time.h>

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
    end = clock();

    int i;
    for (i = 0; i < n; i++)
        printf("%d\n", arr[i]);
    printf("\n");

    printf("Total time taken: %.6lf seconds\n\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}