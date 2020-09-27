#ifndef SLL_H_  /* guard */
#define SLL_H_
#include <stdbool.h>

/* Node and linked list structure definitions */
typedef struct Node Node;
struct Node
{
    int val;
    struct Node* next;
    struct Node* prev;
};

typedef struct
{
    struct Node* head;
    struct Node* tail;
    int count;
}
SLL;

/* simple linked list function prototypes */
SLL* sll_init(int* vals, int vals_size);      /* creates new SLL from array */
void sll_print(SLL* list);                                    /* prints SLL */
void sll_append(SLL* list, int val);                  /* push to end of SLL */
void sll_prepend(SLL* list, int val);               /* push to front of SLL */
int sll_pop_end(SLL* list);                         /* pop last node of SLL */
int sll_pop_front(SLL* list);                      /* pop first node of SLL */
bool sll_contains(SLL* list, int val);                /* search SLL for val */
bool sll_remove_first(SLL* list, int val);          /* removes first by val */
bool sll_remove_index(SLL* list, int index);            /* removes by index */
void sll_clear(SLL* list);                     /* clears all nodes from SLL */
void sll_splice(SLL* list, int index, int val);         /* inserts by index */
int* sll_to_array(SLL* list);         /* converts SLL into an array of ints */

#endif
