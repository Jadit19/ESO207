#include "linked_list.h"

void insert(struct List *queue)
{
    pushBack(queue);
}

void delete(struct List *queue)
{
    popFront(queue);
}

int main(int argc, char **argv)
{
    struct List queue;
    init(&queue);

    int option;

    while (1)
    {
        printf("Enter your choice:\n");
        printf("\t(1) Insert to Queue\n");
        printf("\t(2) Delete from Queue\n");
        printf("\t(3) Print Queue (Front to End)\n");
        printf("\t(4) Exit\n");

        scanf("%d", &option);

        switch (option)
        {
        case 1:
            insert(&queue);
            break;

        case 2:
            delete (&queue);
            break;

        case 3:
            printFromStart(&queue);
            break;

        case 4:
            exit(0);

        default:
            printf("Enter a valid option choice!\n");
            break;
        }

        printf("\n");
    }

    return 0;
}