#include <stdio.h>
#include <stdlib.h>

#define MIN 0
#define MAX 1000000

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Provide an argument for the length of random numbers to be generated!\n");
        return 0;
    }

    FILE *filePtr;
    int i, num, count;

    count = atoi(argv[1]);

    filePtr = fopen("numbers.txt", "w");
    if (filePtr == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }

    srand(time(0));

    for (i = 0; i < count; i++)
    {
        num = MIN + rand() % (MAX - MIN + 1);
        fprintf(filePtr, "%d\n", num);
    }

    fclose(filePtr);

    return 0;
}