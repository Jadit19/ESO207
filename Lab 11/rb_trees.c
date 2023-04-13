#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int key;
    int rank;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

Node *newNode(int key)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->rank = 0;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

int isRed(Node *node)
{
    return (node->rank == node->parent->rank) ? 1 : 0;
}

int getRank(Node *node)
{
    return (node == NULL) ? 0 : node->rank;
}

Node *triNode(Node *root, Node *node)
{
    Node *parent = node->parent;
    Node *grandparent = parent->parent;
    if ((grandparent->key > parent->key) && (parent->key > node->key))
    {
        grandparent->left = parent->right;
        if (parent->right != NULL)
        {
            parent->right->parent = grandparent;
        }
        parent->parent = grandparent->parent;
        if (grandparent->parent == NULL)
        {
            root = parent;
        }
        else if (grandparent == grandparent->parent->left)
        {
            grandparent->parent->left = parent;
        }
        else
        {
            grandparent->parent->right = parent;
        }
        parent->right = grandparent;
        grandparent->parent = parent;
    }
    else if ((grandparent->key < parent->key) && (parent->key < node->key))
    {
        grandparent->right = parent->left;
        if (parent->left != NULL)
        {
            parent->left->parent = grandparent;
        }
        parent->parent = grandparent->parent;
        if (grandparent->parent == NULL)
        {
            root = parent;
        }
        else if (grandparent == grandparent->parent->left)
        {
            grandparent->parent->left = parent;
        }
        else
        {
            grandparent->parent->right = parent;
        }
        parent->left = grandparent;
        grandparent->parent = parent;
    }
    else if ((grandparent->key > parent->key) && (parent->key < node->key))
    {
        parent->right = node->left;
        if (node->left != NULL)
        {
            node->left->parent = parent;
        }
        grandparent->left = node->right;
        if (node->right != NULL)
        {
            node->right->parent = grandparent;
        }
        node->parent = grandparent->parent;
        if (grandparent->parent == NULL)
        {
            root = node;
        }
        else if (grandparent == grandparent->parent->left)
        {
            grandparent->parent->left = node;
        }
        else
        {
            grandparent->parent->right = node;
        }
        node->left = parent;
        node->right = grandparent;
        parent->parent = node;
        grandparent->parent = node;
    }
    else if ((grandparent->key < parent->key) && (parent->key > node->key))
    {
        parent->left = node->right;
        if (node->right != NULL)
        {
            node->right->parent = parent;
        }
        grandparent->right = node->left;
        if (node->left != NULL)
        {
            node->left->parent = grandparent;
        }
        node->parent = grandparent->parent;
        if (grandparent->parent == NULL)
        {
            root = node;
        }
        else if (grandparent == grandparent->parent->left)
        {
            grandparent->parent->left = node;
        }
        else
        {
            grandparent->parent->right = node;
        }
        node->left = grandparent;
        node->right = parent;
        parent->parent = node;
        grandparent->parent = node;
    }
    return root;
}

Node *fixInsert(Node *root, Node *node)
{
    Node *parent = node->parent;
    Node *grandprent = parent->parent;
    while (parent != NULL && grandprent != NULL)
    {
        if (isRed(node) == isRed(parent))
        {
            if (parent == grandprent->right)
            {
                if (grandprent->left == NULL)
                {
                    root = triNode(root, node);
                }
                else
                {
                    if (grandprent->rank == grandprent->left->rank)
                    {
                        grandprent->rank++;
                        node = grandprent;
                        parent = grandprent->parent;
                        if (grandprent->parent != NULL)
                            grandprent = grandprent->parent->parent;
                        continue;
                    }
                    else
                    {
                        root = triNode(root, node);
                    }
                }
            }
            else if (parent == grandprent->left)
            {
                if (grandprent->right == NULL)
                {
                    root = triNode(root, node);
                }
                else
                {
                    if (grandprent->right->rank == grandprent->rank)
                    {
                        grandprent->rank++;
                        node = grandprent;
                        parent = grandprent->parent;
                        if (grandprent->parent != NULL)
                        {
                            grandprent = grandprent->parent->parent;
                        }
                        continue;
                    }
                    else
                    {
                        root = triNode(root, node);
                    }
                }
            }
            return root;
        }
        else
        {
            return root;
        }
    }
    return root;
}

Node *insert(Node *root, int key)
{
    Node *node = newNode(key);
    if (root == NULL)
    {
        node->rank = 1;
        root = node;
        return root;
    }
    else
    {
        Node *x = root;
        Node *y = NULL;
        while (x != NULL)
        {
            y = x;
            if (node->key < x->key)
            {
                x = x->left;
            }
            else if (node->key > x->key)
            {
                x = x->right;
            }
            else
            {
                return root;
            }
        }
        node->rank = 1;
        node->parent = y;
        if (node->key < y->key)
        {
            y->left = node;
        }
        else
        {
            y->right = node;
        }
        root = fixInsert(root, node);
    }
    return root;
}

void inOrderTraversal(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    inOrderTraversal(root->left);
    printf("\tValue: %d,\tRank: %d\n", root->key, root->rank);
    inOrderTraversal(root->right);
    return;
}

Node *join(Node *treeRoot1, Node *treeRoot2, int key)
{
    Node *joinedTreeRoot = NULL;
    Node *node = (Node *)malloc(sizeof(Node));
    if (getRank(treeRoot1) > getRank(treeRoot2))
    {
        Node *temp = treeRoot1;
        while (getRank(temp) != getRank(treeRoot2))
        {
            temp = temp->right;
        }
        node->parent = temp->parent;
        temp->parent->right = node;
        temp->parent = node;
        node->left = temp;
        node->right = treeRoot2;
        node->key = key;
        node->rank = getRank(treeRoot2) + 1;
        joinedTreeRoot = fixInsert(treeRoot1, node);
    }
    else if (getRank(treeRoot1) == getRank(treeRoot2))
    {
        node->parent = NULL;
        node->left = treeRoot1;
        node->right = treeRoot2;
        node->key = key;
        node->rank = getRank(treeRoot1) + 1;
        joinedTreeRoot = node;
    }
    else
    {
        Node *temp = treeRoot2;
        while (getRank(temp) != getRank(treeRoot1))
        {
            temp = temp->left;
        }
        node->parent = temp->parent;
        temp->parent->left = node;
        temp->parent = node;
        node->left = treeRoot1;
        node->right = temp;
        node->key = key;
        node->rank = getRank(treeRoot1) + 1;
        joinedTreeRoot = fixInsert(treeRoot2, node);
    }
    return joinedTreeRoot;
}

Node *search(Node *root, int key)
{
    if (root == NULL)
    {
        printf("\nProvided key (%d) is not present!\n", key);
        return NULL;
    }
    if (key > root->key)
    {
        return search(root->right, key);
    }
    else if (key < root->key)
    {
        return search(root->left, key);
    }
    else
    {
        return root;
    }
}

void split(Node *root, int key, Node **splitTreeRoot1, Node **splitTreeRoot2)
{
    Node *node = search(root, key);
    if (node == NULL)
    {
        return;
    }

    *splitTreeRoot1 = node->left;
    *splitTreeRoot2 = node->right;
    while (node->parent != NULL)
    {
        Node *parent = node->parent;
        if (parent->left == node)
        {
            *splitTreeRoot2 = join(*splitTreeRoot2, parent->right, parent->key);
        }
        else
        {
            *splitTreeRoot1 = join(*splitTreeRoot1, parent->left, parent->key);
        }
        node = parent;
    }
    return;
}

int main()
{
    int i, n = 5;
    int arr1[5] = {1, 2, 3, 4, 5};
    int arr2[20] = {7, 8, 9, 10, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28};

    Node *treeRoot1, *treeRoot2;
    for (i = 0; i < 5; i++)
    {
        treeRoot1 = insert(treeRoot1, arr1[i]);
    }
    for (i = 0; i < 20; i++)
    {
        treeRoot2 = insert(treeRoot2, arr2[i]);
    }

    printf("Inorder traversal of Tree #1 is:\n");
    inOrderTraversal(treeRoot1);
    printf("\nInorder traversal of Tree #2 is:\n");
    inOrderTraversal(treeRoot2);

    Node *joinedTreeRoot;
    joinedTreeRoot = join(treeRoot1, treeRoot2, 6);
    printf("\nInorder traversal of Joined tree is:\n");
    inOrderTraversal(joinedTreeRoot);

    Node *splitTreeRoot1;
    Node *splitTreeRoot2;
    split(joinedTreeRoot, 18, &splitTreeRoot1, &splitTreeRoot2);

    printf("\nInorder traversal of Split tree #1 is:\n");
    inOrderTraversal(splitTreeRoot1);
    printf("\nInorder traversal of Split tree #2 is:\n");
    inOrderTraversal(splitTreeRoot2);

    return 0;
}