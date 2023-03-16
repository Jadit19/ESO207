#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN 0
#define MAX 1000000

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *newNode(int data)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct Node *insert(struct Node *root, int data)
{
    if (root == NULL)
    {
        return newNode(data);
    }

    if (data < root->data)
    {
        root->left = insert(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = insert(root->right, data);
    }

    return root;
}

struct Node *search(struct Node *root, int data)
{
    if (root == NULL || root->data == data)
    {
        return root;
    }

    if (data < root->data)
    {
        return search(root->left, data);
    }
    return search(root->right, data);
}

struct Node *deleteMin(struct Node *root, int *min)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (root->left == NULL)
    {
        struct Node *temp = root->right;
        *min = root->data;
        free(root);
        return temp;
    }

    root->left = deleteMin(root->left, min);
    return root;
}

void printInOrder(struct Node *node, FILE *filePtr)
{
    if (node != NULL)
    {
        printInOrder(node->left, filePtr);
        fprintf(filePtr, "%d\n", node->data);
        printInOrder(node->right, filePtr);
    }
}

int main(int argc, char **argv)
{
    struct Node *root = NULL;

    int i, j;
    srand(time(0));
    for (i = 0; i < 5000; i++)
    {
        j = MIN + rand() % (MAX - MIN + 1);
        root = insert(root, j);
    }
    printf("5000 random numbers successfully inserted!\n");

    FILE *filePtr;
    filePtr = fopen("inorder_bst.txt", "w");
    printInOrder(root, filePtr);
    fclose(filePtr);
    printf("Inorder traversal completed and output stored in `inorder_bst.txt`\n");

    filePtr = fopen("minimum_bst.txt", "w");
    for (i = 0; i < 1000; i++)
    {
        root = deleteMin(root, &j);
        fprintf(filePtr, "%d\n", j);
    }
    fclose(filePtr);
    printf("Delete Minimum implemented 1000 times, output stored in `minimum_bst.txt`\n");

    return EXIT_SUCCESS;
}