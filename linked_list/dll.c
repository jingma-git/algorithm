#include <stdlib.h>
#include <stdio.h>
// Book: C and Pointer Ch12
// ordered doubly linked list
// root_node: fwd=first_node, bwd=last_node
// first_node: bwd=NULL
// last_node:fwd=NULL

typedef struct Node
{
    struct Node *fwd;
    struct Node *bwd;
    int val;
} Node;

int dll_insert(Node *rootp, int val)
{
    Node *this, *next, *newnode; // this: store pointer before insertion, next: store pointer after insertion

    //find insertion position
    //if val already exist in the list, do not insert
    this = rootp;                      // (1)
    while ((next = this->fwd) != NULL) // (2)
    {
        if (next->val == val)
            return 0;
        if (next->val > val)
            break;
        this = next; // (3)
    }
    // (1)(2)(3) == for(this=rootp; (next=this->fwd)!=NULL; this=next)

    newnode = (Node *)malloc(sizeof(Node));
    if (newnode == NULL) // fail to allocate memory
        return -1;
    newnode->val = val;

    if (next != NULL)
    {
        newnode->fwd = next;
        if (this == rootp) //insert to head
        {
            newnode->bwd = NULL;
            rootp->fwd = newnode;
        }
        else // insert to middle
        {
            newnode->bwd = this;
            this->fwd = newnode;
        }
        next->bwd = newnode;
    }
    else
    {
        newnode->fwd = NULL;
        if (this == rootp) // insert to empty
        {
            newnode->bwd = NULL;
            rootp->fwd = newnode;
        }
        else //insert to end
        {
            newnode->bwd = this;
            this->fwd = newnode;
        }
        rootp->bwd = newnode;
    }
    return 1;
}

void dll_print(Node *rootp)
{
    Node *cur = rootp->fwd;
    while (cur)
    {
        printf("%d ", cur->val);
        cur = cur->fwd;
    }
    printf("\n");
}

void dll_free(Node *rootp)
{
    Node *cur = rootp->fwd;
    while (cur)
    {
        Node *tmp = cur;
        cur = cur->fwd;
        free(tmp);
    }
}

int dll_remove(Node *rootp, Node *node)
{
    Node *cur, *prev = NULL, *next = NULL;
    cur = rootp->fwd;
    if (node == cur && cur->fwd == NULL)
    {
        free(node);
        rootp->fwd = NULL;
        rootp->bwd = NULL;
        return 1;
    }

    while (1)
    {
        next = cur->fwd;
        if (cur == node)
        {
            if (prev == NULL) // remove from head
            {
                rootp->fwd = next;
                next->bwd = NULL;
                free(node);
            }
            else if (next == NULL) //remove from end
            {
                prev->fwd = NULL;
                rootp->bwd = prev;
                free(node);
            }
            else // remove from middle
            {
                prev->fwd = next;
                next->bwd = prev;
                free(node);
            }

            return 1;
        }
        prev = cur;
        cur = cur->fwd;
    }

    return 0;
}

Node *dll_search(Node *rootp, int val)
{
    Node *cur = rootp->fwd;
    while (cur)
    {
        if (cur->val == val)
            return cur;
        cur = cur->fwd;
    }
}
void test_dll_rootp()
{
    Node *root = (Node *)malloc(sizeof(Node));
    printf("insert to empty list\n");
    dll_insert(root, 5);
    dll_print(root);

    printf("insert to head\n");
    dll_insert(root, 1);
    dll_print(root);

    printf("insert to tail\n");
    dll_insert(root, 12);
    dll_print(root);

    printf("insert into middle\n");
    dll_insert(root, 10);
    dll_print(root);

    Node *head = root->fwd;
    Node *tail = root->bwd;
    Node *mid = dll_search(root, 10);
    dll_remove(root, mid);
    printf("remove from mid\n");
    dll_print(root);
    dll_remove(root, head);
    printf("remove from head\n");
    dll_print(root);
    dll_remove(root, tail);
    printf("remove from tail\n");
    dll_print(root);
}

int dll_insert2(Node **firstp, Node **lastp, int val)
{
    Node *this, *newnode; // this: store pointer after insertion

    this = *firstp;
    while (this)
    {
        if (this->val == val)
            return 0;
        if (this->val > val)
            break;
        this = this->fwd;
    }
    newnode = (Node *)malloc(sizeof(Node));
    newnode->val = val;

    if (newnode == NULL)
        return -1;
    if (this == *firstp) // insert to head
    {
        newnode->fwd = *firstp;
        newnode->bwd = NULL;
        (*firstp)->bwd = newnode;
        *firstp = newnode;
    }
    else if (this == NULL) // insert to end
    {
        newnode->fwd = NULL;
        newnode->bwd = (*lastp);
        (*lastp)->fwd = newnode;
        *lastp = newnode;
    }
    else // insert to middle
    {
        Node *prev = this->bwd;
        newnode->fwd = this;
        newnode->bwd = prev;
        prev->fwd = newnode;
        this->bwd = newnode;
    }
    return 1;
}

void dll_print2(Node *first, Node *last)
{
    Node *cur = first;
    while (cur)
    {
        printf("%d ", cur->val);
        cur = cur->fwd;
    }
    printf("\n");
}

void test_dll_doublep()
{
    Node *first = (Node *)malloc(sizeof(Node));
    Node *last = (Node *)malloc(sizeof(Node));
    first->val = 5;
    last->val = 11;
    first->fwd = last;
    first->bwd = NULL;
    last->fwd = NULL;
    last->bwd = first;

    printf("insert to head\n");
    dll_insert2(&first, &last, 1);
    dll_print2(first, last);

    printf("insert to tail\n");
    dll_insert2(&first, &last, 12);
    dll_print2(first, last);

    printf("insert into middle\n");
    dll_insert2(&first, &last, 10);
    dll_print2(first, last);
}

int main()
{
    test_dll_rootp();
    // test_dll_doublep();
    return 0;
}