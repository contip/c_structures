#ifndef LL_H_  /* guard */
#define LL_H_
#include <stdbool.h>

/* Node and LL (linked list) structure definitions */
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

/* linked-list methods */
struct LL* ll_new(int* vals, int vals_size);    /* creates new LL from array */
void ll_add_end(struct LL* list, int val);              /* adds to end of LL */
void ll_add_front(struct LL* list, int val);          /* adds to front of LL */
void ll_print(struct LL* list);                                 /* prints LL */
int* ll_to_array(struct LL* list);      /* converts LL into an array of ints */
int ll_remove_end(struct LL* list);               /* removes last node of LL */
int ll_remove_front(struct LL* list);            /* removes first node of LL */
bool ll_contains(struct LL* list, int val);           /* searches LL for val */
bool ll_remove_first_occurrence(struct LL* list, int val);  /* remove by val */
bool ll_remove_index(struct LL* list, int index);         /* remove by index */
void ll_clear(struct LL* list);                   /* clear all nodes from LL */
void ll_insert_before(struct LL* list, int index, int val); /* insert b4 idx */

#endif

