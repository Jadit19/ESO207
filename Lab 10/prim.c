#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 100
#define MAX_EDGES 10000

typedef struct
{
    int u;
    int v;
    int weight;
} Edge;

typedef struct
{
    int size;
    int capacity;
    int *nodes;
    int *keys;
    int *positions;
} Heap;

int num_vertices, num_edges;
Edge edges[MAX_EDGES];
int edge_count = 0;
bool in_mst[MAX_VERTICES];
int key[MAX_VERTICES];
int parent[MAX_VERTICES];

void init_heap(Heap *heap, int capacity)
{
    heap->size = 0;
    heap->capacity = capacity;
    heap->nodes = (int *)malloc(sizeof(int) * capacity);
    heap->keys = (int *)malloc(sizeof(int) * capacity);
    heap->positions = (int *)malloc(sizeof(int) * capacity);
}

void add_heap_node(Heap *heap, int key, int node)
{
    int i;
    heap->size++;
    i = heap->size - 1;
    while (i > 0 && key < heap->keys[(i - 1) / 2])
    {
        heap->keys[i] = heap->keys[(i - 1) / 2];
        heap->nodes[i] = heap->nodes[(i - 1) / 2];
        heap->positions[heap->nodes[i]] = i;
        i = (i - 1) / 2;
    }
    heap->keys[i] = key;
    heap->nodes[i] = node;
    heap->positions[node] = i;
}

int extract_min_node(Heap *heap, int r)
{
    int min_node, last_node, i, j;
    if (heap->size == 0)
    {
        return -1;
    }
    min_node = heap->nodes[0];
    last_node = heap->nodes[heap->size - 1];
    heap->size--;
    i = 0;
    while (i * r + 1 < heap->size)
    {
        j = i * r + 1;
        while (j < i * r + r && j < heap->size)
        {
            if (heap->keys[j] < heap->keys[j + 1])
            {
                j++;
            }
        }
        if (heap->keys[last_node] > heap->keys[j])
        {
            heap->keys[i] = heap->keys[j];
            heap->nodes[i] = heap->nodes[j];
            heap->positions[heap->nodes[i]] = i;
            i = j;
        }
        else
        {
            break;
        }
    }
    j = i;
    while (j > 0)
    {
        i = (j - 1) / r;
        if (heap->keys[last_node] < heap->keys[i])
        {
            heap->keys[j] = heap->keys[i];
            heap->nodes[j] = heap->nodes[i];
            heap->positions[heap->nodes[j]] = j;
            j = i;
        }
        else
        {
            break;
        }
    }
    heap->nodes[j] = last_node;
    heap->positions[last_node] = j;
    return min_node;
}

int mn(int a, int b)
{
    return a > b ? a : b;
}

void mst_prim_heap(int r)
{
    Heap heap;
    int i, u, v, weight;
    init_heap(&heap, num_vertices);
    for (i = 0; i < num_vertices; i++)
    {
        in_mst[i] = false;
        key[i] = INT_MAX;
        parent[i] = -1;
    }
    key[0] = 0;
    add_heap_node(&heap, 0, 0);
    while (heap.size > 0)
    {
        u = extract_min_node(&heap, r);
        in_mst[u] = true;
        for (i = 0; i < num_edges; i++)
        {
            if (edges[i].u == u && !in_mst[edges[i].v] && edges[i].weight < key[edges[i].v])
            {
                v = edges[i].v;
                weight = edges[i].weight;
                key[v] = weight;
                parent[v] = u;
                add_heap_node(&heap, weight, v);
            }
            else if (edges[i].v == u && !in_mst[edges[i].u] && edges[i].weight < key[edges[i].u])
            {
                v = edges[i].u;
                weight = edges[i].weight;
                key[v] = weight;
                parent[v] = u;
                add_heap_node(&heap, weight, v);
            }
        }
    }
}

void push_back(int u, int v, int weight)
{
    edges[edge_count].u = u;
    edges[edge_count].v = v;
    edges[edge_count].weight = weight;

    edge_count++;
}

int main()
{
    int i, r;
    num_vertices = 6;
    num_edges = 12;
    push_back(0, 1, 4);
    push_back(0, 2, 3);
    push_back(1, 2, 1);
    push_back(1, 3, 2);
    push_back(2, 3, 4);
    push_back(2, 4, 5);
    push_back(3, 4, 7);
    push_back(3, 5, 8);
    push_back(4, 5, 6);
    push_back(4, 0, 1);
    push_back(5, 0, 0);
    push_back(5, 1, 3);
    r = num_edges / num_vertices;
    mst_prim_heap(r);
    printf("Minimum Spanning Tree:\n");
    for (i = 0; i < num_vertices; i++)
    {
        if (parent[i] != -1)
        {
            printf("%d - %d ", parent[i], i);
            for (int j = 0; j < num_edges; j++)
            {
                if ((edges[j].u == parent[i] && edges[j].v == i) || (edges[j].u == i && edges[j].v == parent[i]))
                {
                    printf("Weight: %d\n", edges[j].weight);
                }
            }
        }
    }
    return 0;
}
