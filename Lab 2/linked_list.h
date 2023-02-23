#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;
};

struct List
{
    struct Node *head;
    struct Node *tail;
};

void init(struct List *list)
{
    list->head = NULL;
    list->tail = NULL;
}

void pushFront(struct List *list)
{
    int data;
    printf("Enter data to be added: ");
    scanf("%d", &data);
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = list->head;
    if (list->head != NULL)
        list->head->prev = newNode;
    else
        list->tail = newNode;
    list->head = newNode;
}

void pushBack(struct List *list)
{
    int data;
    printf("Enter data to be added: ");
    scanf("%d", &data);
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = list->tail;
    newNode->next = NULL;
    if (list->tail != NULL)
        list->tail->next = newNode;
    else
        list->head = newNode;
    list->tail = newNode;
}

void popFront(struct List *list)
{
    if (list->head == NULL)
    {
        printf("Linked list is empty! Insert some data first.\n");
        return;
    }
    struct Node *temp = list->head;
    list->head = list->head->next;
    if (list->head != NULL)
        list->head->prev = NULL;
    else
        list->tail = NULL;
    free(temp);
    printf("First item deleted successfully!\n");
}

void popBack(struct List *list)
{
    if (list->tail == NULL)
    {
        printf("Linked list is empty! Insert some data first.\n");
        return;
    }
    struct Node *temp = list->tail;
    list->tail = list->tail->prev;
    if (list->tail != NULL)
        list->tail->next = NULL;
    else
        list->head = NULL;
    free(temp);
    printf("Last item deleted successfully!\n");
}

void printFromStart(struct List *list)
{
    if (list->head == NULL)
    {
        printf("Linked list is empty! Insert some data first.\n");
        return;
    }
    struct Node *current = list->head;
    printf("The list contains: \t%d", current->data);
    while (current->next != NULL)
    {
        printf(", %d", current->next->data);
        current = current->next;
    }
    printf("\n");
}

void printFromEnd(struct List *list)
{
    if (list->tail == NULL)
    {
        printf("Linked list is empty! Insert some data first.\n");
        return;
    }
    struct Node *current = list->tail;
    printf("The list contains: \t%d", current->data);
    while (current->prev != NULL)
    {
        printf(", %d", current->prev->data);
        current = current->prev;
    }
    printf("\n");
}