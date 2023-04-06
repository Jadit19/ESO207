#include <stdio.h>
#include <stdlib.h>

// define maximum number of vertices and edges
#define MAX_VERTICES 1000
#define MAX_EDGES 10000

// data structure to represent an edge in the graph
struct Edge
{
    int src, dest, weight;
};

// data structure to represent the disjoint set
struct DisjointSet
{
    int parent[MAX_VERTICES];
    int rank[MAX_VERTICES];
};

// initialize the disjoint set
void makeSet(struct DisjointSet *set, int vertices)
{
    for (int i = 0; i < vertices; i++)
    {
        set->parent[i] = i;
        set->rank[i] = 0;
    }
}

// find the parent of a node (with path compression)
int find(struct DisjointSet *set, int node)
{
    if (set->parent[node] != node)
    {
        set->parent[node] = find(set, set->parent[node]);
    }
    return set->parent[node];
}

// merge two sets by rank
void merge(struct DisjointSet *set, int node1, int node2)
{
    int parent1 = find(set, node1);
    int parent2 = find(set, node2);
    if (parent1 == parent2)
    {
        return;
    }
    if (set->rank[parent1] > set->rank[parent2])
    {
        set->parent[parent2] = parent1;
    }
    else if (set->rank[parent1] < set->rank[parent2])
    {
        set->parent[parent1] = parent2;
    }
    else
    {
        set->parent[parent2] = parent1;
        set->rank[parent1]++;
    }
}

// compare two edges by weight (for qsort)
int compare(const void *a, const void *b)
{
    struct Edge *edge1 = (struct Edge *)a;
    struct Edge *edge2 = (struct Edge *)b;
    return edge1->weight - edge2->weight;
}

// perform Kruskal's Algorithm to find the Minimum Spanning Tree
void kruskal(struct Edge edges[], int vertices, int edgesCount)
{
    // sort the edges in increasing order of weight
    qsort(edges, edgesCount, sizeof(struct Edge), compare);

    // initialize the disjoint set
    struct DisjointSet set;
    makeSet(&set, vertices);

    // loop over the edges and add them to the MST if they do not form a cycle
    int mstWeight = 0;
    for (int i = 0; i < edgesCount; i++)
    {
        int src = edges[i].src;
        int dest = edges[i].dest;
        int weight = edges[i].weight;
        if (find(&set, src) != find(&set, dest))
        {
            merge(&set, src, dest);
            mstWeight += weight;
            printf("Added edge (%d, %d) weighing %d\n", src, dest, weight);
        }
    }

    printf("Total weight of MST is %d\n", mstWeight);
}

// driver function to test the implementation
int main()
{
    int vertices = 6;               // number of vertices in the graph
    int edgesCount = 12;            // number of edges in the graph
    struct Edge edges[MAX_EDGES] = {// define the edges of the graph
                                    {0, 1, 4},
                                    {0, 2, 3},
                                    {1, 2, 1},
                                    {1, 3, 2},
                                    {2, 3, 4},
                                    {2, 4, 5},
                                    {3, 4, 7},
                                    {3, 5, 8},
                                    {4, 5, 6},
                                    {4, 0, 1},
                                    {5, 0, 0},
                                    {5, 1, 3}};

    kruskal(edges, vertices, edgesCount);

    return 0;
}
