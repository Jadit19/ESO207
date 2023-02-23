#include "linked_list.h"

void push(struct List *stack)
{
    pushBack(stack);
}

void pop(struct List *stack)
{
    popBack(stack);
}

int main(int argc, char **argv)
{
    struct List stack;
    init(&stack);

    int option;

    while (1)
    {
        printf("Enter your choice:\n");
        printf("\t(1) Push to Stack\n");
        printf("\t(2) Pop from Stack\n");
        printf("\t(3) Print Stack (Top to Bottom)\n");
        printf("\t(4) Exit\n");

        scanf("%d", &option);

        switch (option)
        {
        case 1:
            push(&stack);
            break;

        case 2:
            pop(&stack);
            break;

        case 3:
            printFromEnd(&stack);
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