#ifndef GLL_H_  /* guard */
#define GLL_H_
#include <stdbool.h>


/* data types accepted by LL */
enum ListType
{
    INT = 0,
    DOUBLE,
    CHAR,
    STRING,
};
/* Node and LL (linked list) structure definitions */
struct Node
{
    struct Node* next;
    struct Node* prev;
    enum ListType type;
    void* data;
};

struct LL
{
    struct Node* head;
    struct Node* tail;
    int count;
};

/* linked-list functions provided */
struct LL* ll_init();                             /* initialize new empty LL */
void ll_print(struct LL* list);                                  /* prints LL*/
bool ll_add_end(struct LL* list, void* data, enum ListType type);  /* append */
bool ll_add_front(struct LL* list, void* data, enum ListType type); /*prepend*/
void* ll_pop_end(struct LL* list);               /* pop last element from LL */
void* ll_pop_front(struct LL* list);            /* pop first element from LL */
void ll_clear(struct LL* list);                 /* clear all entries from LL */
bool ll_contains(struct LL* list, void* data, enum ListType type); /* search */

#endif

