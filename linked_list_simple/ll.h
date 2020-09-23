#ifndef LL_H_  /* guard */
#define LL_H_
#include <stdbool.h>

/* Node and linked list structure definitions */
struct Node
{
    int val;
    struct Node* next;
    struct Node* prev;
};

struct LL
{
    struct Node* head;
    struct Node* tail;
    int count;
};

/* linked list functions provided */
struct LL* ll_init(int* vals, int vals_size);   /* creates new LL from array */
void ll_print(struct LL* list);                                 /* prints LL */
void ll_append(struct LL* list, int val);               /* push to end of LL */
void ll_prepend(struct LL* list, int val);            /* push to front of LL */
int ll_pop_end(struct LL* list);                      /* pop last node of LL */
int ll_pop_front(struct LL* list);                   /* pop first node of LL */
bool ll_contains(struct LL* list, int val);           /* searches LL for val */
bool ll_remove_first(struct LL* list, int val);      /* removes first by val */
bool ll_remove_index(struct LL* list, int index);        /* removes by index */
void ll_clear(struct LL* list);                  /* clears all nodes from LL */
void ll_splice(struct LL* list, int index, int val);     /* inserts by index */
int* ll_to_array(struct LL* list);      /* converts LL into an array of ints */

#endif
