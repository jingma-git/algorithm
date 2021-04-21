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

int sll_remove(Node **rootp, Node *node)
{
    Node *cur = *rootp;
    if (node == cur && cur->link == NULL)
        *rootp = NULL;

    Node *prev = NULL;
    Node *next = NULL;
    while (cur)
    {
        next = cur->link;
        if (cur == node)
        {
            if (prev == NULL) // remove from head
            {
                *rootp = next;
            }
            else if (next == NULL) // remove from end
            {
                prev->link = NULL;
            }
            else // remove from middle
            {
                prev->link = next;
            }
            free(cur);
            return 1;
        }
        prev = cur;
        cur = cur->link;
    }
    return 0;
}

Node *sll_reverse(Node *first)
{
    if (first == NULL)
        return NULL;
    if (first->link == NULL)
        return first;

    Node *prev, *cur;
    prev = first;
    cur = first->link;
    first->link = NULL;
    while (1)
    {
        Node *next = cur->link;

        cur->link = prev;
        if (next == NULL)
            break;
        prev = cur;
        cur = next;
    }
    return cur;
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

    printf("reverse\n");
    n0 = sll_reverse(n0);
    sll_print(n0);

    printf("remove\n");
    sll_remove(&n0, n2);
    sll_print(n0);
    sll_remove(&n0, n0);
    sll_print(n0);
    sll_free(n0);
    return 0;
}