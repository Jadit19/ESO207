#include <stdio.h>
#include <stdlib.h>

int find_length(FILE *filePtr)
{
    int n = 0;
    fseek(filePtr, 0, SEEK_SET);

    int temp;
    while (fscanf(filePtr, "%d", &temp) == 1)
    {
        n++;
    }
    return n;
}

void read_array(FILE *filePtr, int n, int arr[])
{
    int i = 0;
    fseek(filePtr, 0, SEEK_SET);

    int temp;
    while (fscanf(filePtr, "%d", &temp) == 1)
    {
        arr[i] = temp;
        i++;
    }
}