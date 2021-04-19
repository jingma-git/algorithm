#include <stdlib.h>
#include <stdio.h>
// Book: C and Pointer Ch12
// ordered singled linked list: insert an value

// struct tagType {};
// in C, struct tagType must be sticked together to declare a type
// typedef struct tagType {} AliasType; // AliasType is another name of 'struct tagType'
// struct tagType a;
// equals
// AliasType a;
typedef struct Node
{
    struct Node *link;
    int value;
} Node;

// this algo only works when there is at least one-element already in the list
void sll_insert(Node **linkp, int val)
{
    Node *current;
    while ((current = *linkp) != NULL && current->value < val)
    {
        linkp = &current->link;
    }
    Node *new = (Node *)malloc(sizeof(Node));
    new->value = val;
    new->link = current; // glue next larger element to 'new'
    *linkp = new;        // glue 'new' to previous smaller element
}

void sll_free(Node *root)
{
    if (root == NULL)
        return;
    Node *ptr = root;
    while (ptr)
    {
        Node *tmp = ptr;
        ptr = ptr->link;
        free(tmp);
    }
}

void sll_print(Node *root)
{
    if (root == NULL)
        return;
    Node *ptr = root;
    while (ptr)
    {
        printf("%d ", ptr->value);
        ptr = ptr->link;
    }
    printf("\n");
}

int main()
{
    Node *n0, *n1, *n2;
    n0 = (Node *)malloc(sizeof(Node));
    n0->value = 5;
    n1 = (Node *)malloc(sizeof(Node));
    n1->value = 10;
    n2 = (Node *)malloc(sizeof(Node));
    n2->value = 15;
    n0->link = n1;
    n1->link = n2;
    sll_print(n0);

    printf("insert at begin\n");
    sll_insert(&n0, 1);
    sll_print(n0);

    printf("insert at middle\n");
    sll_insert(&n0, 12);
    sll_print(n0);

    printf("insert at end\n");
    sll_insert(&n0, 20);
    sll_print(n0);

    sll_free(n0);
    return 0;
}