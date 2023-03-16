#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN 0
#define MAX 1000000

struct Node
{
    int data;
};

struct Heap
{
    int r;
    int size;
    struct Node *nodes;
};

struct Heap *createHeap(int r, int size)
{
    struct Heap *heap = (struct Heap *)malloc(sizeof(struct Heap));
    heap->r = r;
    heap->size = 0;
    heap->nodes = (struct Node *)malloc(size * sizeof(struct Node));

    return heap;
}

void swap(struct Heap *heap, int i, int j)
{
    struct Node temp = heap->nodes[i];
    heap->nodes[i] = heap->nodes[j];
    heap->nodes[j] = temp;
}

void heapifyUp(struct Heap *heap, int index)
{
    if (index == 0)
    {
        return;
    }

    int parentIndex = (index - 1) / heap->r;
    if (heap->nodes[index].data < heap->nodes[parentIndex].data)
    {
        swap(heap, index, parentIndex);
        heapifyUp(heap, parentIndex);
    }
}

void heapifyDown(struct Heap *heap, int index)
{
    int minChild = index * heap->r + 1;
    if (minChild >= heap->size)
    {
        return;
    }

    for (int i = 2; i <= heap->r; i++)
    {
        int childIndex = index * heap->r + i;
        if (childIndex < heap->size && heap->nodes[childIndex].data < heap->nodes[minChild].data)
        {
            minChild = childIndex;
        }
    }

    if (heap->nodes[minChild].data < heap->nodes[index].data)
    {
        swap(heap, index, minChild);
        heapifyDown(heap, minChild);
    }
}

void insert(struct Heap *heap, int data)
{
    heap->nodes[heap->size].data = data;
    heapifyUp(heap, heap->size);
    heap->size++;
}

void reduceKey(struct Heap *heap, int index, int newKey)
{
    heap->nodes[index].data = newKey;
    heapifyUp(heap, index);
}

int deleteMin(struct Heap *heap)
{
    int minData = heap->nodes[0].data;
    heap->size--;
    heap->nodes[0] = heap->nodes[heap->size];
    heapifyDown(heap, 0);

    return minData;
}

void printHeap(struct Heap *heap, FILE *filePtr)
{
    for (int i = 0; i < heap->size; i++)
    {
        fprintf(filePtr, "%d\n", heap->nodes[i].data);
    }
    printf("\n");
}

int main()
{
    int r = 4;
    int size = 10000;
    struct Heap *heap = createHeap(r, size);

    int i, j;
    srand(time(0));
    for (i = 0; i < 5000; i++)
    {
        j = MIN + rand() % (MAX - MIN + 1);
        insert(heap, j);
    }

    FILE *filePtr;
    filePtr = fopen("heap.txt", "w");
    printHeap(heap, filePtr);
    printf("Heap stored in `heap.txt`\n");
    fclose(filePtr);

    filePtr = fopen("minimum_heap.txt", "w");
    for (i = 0; i < 1000; i++)
    {
        j = deleteMin(heap);
        fprintf(filePtr, "%d\n", j);
    }
    fclose(filePtr);
    printf("Delete Minimum implemented 1000 times, output stored in `minimum_heap.txt`\n");

    return 0;
}