#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    int rank;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct QueueNode
{
    Node *node;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue
{
    QueueNode *front;
    QueueNode *rear;
} Queue;

Queue *createQueue()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

void enqueue(Queue *queue, Node *node)
{
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    newNode->node = node;
    newNode->next = NULL;

    if (queue->front == NULL)
    {
        queue->front = newNode;
    }
    else
    {
        queue->rear->next = newNode;
    }
    queue->rear = newNode;
}

Node *dequeue(Queue *queue)
{
    if (queue->front == NULL)
    {
        return NULL;
    }
    QueueNode *dequeuedNode = queue->front;
    Node *dequeuedTreeNode = dequeuedNode->node;
    queue->front = queue->front->next;
    free(dequeuedNode);
    return dequeuedTreeNode;
}

void levelOrderTraversal(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    Queue *queue = createQueue();
    enqueue(queue, root);

    while (queue->front != NULL)
    {
        Node *node = dequeue(queue);
        printf("%d \t- %d\n", node->data, node->rank);

        if (node->left != NULL)
            enqueue(queue, node->left);
        if (node->right != NULL)
            enqueue(queue, node->right);
    }
    printf("\n\n");
}

int max(int a, int b)
{
    return a > b ? a : b;
}

Node *newNode(int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->rank = 1;
    node->left = NULL;
    node->right = NULL;

    return node;
}

int getRank(Node *node)
{
    return node ? node->rank : 0;
}

void updateRank(Node *node)
{
    if (node)
    {
        node->rank = 1 + max(node->left ? node->left->rank : 0, node->right ? node->right->rank : 0);
    }
}

Node *rotateRight(Node *node)
{
    Node *leftChild = node->left;
    Node *rightGrandChild = leftChild->right;
    leftChild->right = node;
    node->left = rightGrandChild;
    updateRank(node);
    updateRank(leftChild);
    return leftChild;
}

Node *rotateLeft(Node *node)
{
    Node *rightChild = node->right;
    Node *leftGrandChild = rightChild->left;
    rightChild->left = node;
    node->right = leftGrandChild;
    updateRank(node);
    updateRank(rightChild);
    return rightChild;
}

Node *balance(Node *node)
{
    int balanceFactor = getRank(node->left) - getRank(node->right);

    if (balanceFactor > 1)
    {
        if (getRank(node->left->left) >= getRank(node->left->right))
            node = rotateRight(node);
        else
        {
            node->left = rotateLeft(node->left);
            node = rotateRight(node);
        }
    }
    else if (balanceFactor < -1)
    {
        if (getRank(node->right->right) >= getRank(node->right->left))
            node = rotateLeft(node);
        else
        {
            node->right = rotateRight(node->right);
            node = rotateLeft(node);
        }
    }
    updateRank(node);
    return node;
}

Node *findMin(Node *node)
{
    if (node == NULL)
        return NULL;

    while (node->left)
        node = node->left;

    return node;
}

void inorderTraversal(Node *node)
{
    if (node)
    {
        inorderTraversal(node->left);
        printf("%d \t- %d\n", node->data, node->rank);
        inorderTraversal(node->right);
    }
}

Node *insert(Node *node, int data)
{
    if (node == NULL)
        return newNode(data);
    else if (data < node->data)
    {
        node->left = insert(node->left, data);
        updateRank(node);
        if (getRank(node->left) > getRank(node->right) + 1)
            node = balance(node);
    }
    else if (data > node->data)
    {
        node->right = insert(node->right, data);
        updateRank(node);
        if (getRank(node->right) > getRank(node->left) + 1)
            node = balance(node);
    }
    return node;
}

Node *delete(Node *node, int data)
{
    Node *parent = NULL;
    Node *current = node;

    while (current && current->data != data)
    {
        parent = current;
        if (data < current->data)
            current = current->left;
        else
            current = current->right;
    }

    if (current == NULL)
        return node;

    if (current->left == NULL && current->right == NULL)
    {
        if (parent == NULL)
        {
            free(current);
            return NULL;
        }
        else if (current == parent->left)
            parent->left = NULL;
        else
            parent->right = NULL;
        free(current);
    }
    else if (current->left == NULL || current->right == NULL)
    {
        Node *child = current->left ? current->left : current->right;
        if (parent == NULL)
            *node = *child;
        else if (current == parent->left)
            parent->left = child;
        else
            parent->right = child;
        free(current);
    }
    else
    {
        Node *successor = findMin(current->right);
        current->data = successor->data;
        current->right = delete (current->right, successor->data);
    }

    if (node == NULL)
        return NULL;

    updateRank(node);

    if (getRank(node->left) > getRank(node->right) + 1)
        node = balance(node);

    return node;
}

int main()
{
    int i, j, n, temp;

    FILE *filePtr = fopen("numbers.txt", "r");
    if (filePtr == NULL)
    {
        printf("Error opening file randomNumbers.txt!");
        return 1;
    }

    n = 0;
    while (fscanf(filePtr, "%d", &temp) == 1)
    {
        n++;
    }

    int arr[n];
    i = 0;
    fseek(filePtr, 0, SEEK_SET);
    while (fscanf(filePtr, "%d", &temp) == 1)
    {
        arr[i] = temp;
        i++;
    }

    fclose(filePtr);

    Node *root = NULL;
    for (int i = 0; i < n; i++)
        root = insert(root, arr[i]);

    printf("Level Order traversal is: \n");
    levelOrderTraversal(root);

    printf("Inorder traversal is: \n");
    inorderTraversal(root);
    printf("\n\n");

    for (int i = 0; i < 5; i++)
    {
        Node *mn = findMin(root);
        printf("Inorder traversalafter deleting %d is: \n\n", mn->data);
        root = delete (root, mn->data);
        inorderTraversal(root);
        printf("\n\n");
    }
    return 0;
}