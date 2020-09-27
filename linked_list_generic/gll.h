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
    DATA,
};

/* Node and linked list structure definitions */
typedef struct Node Node;
struct Node
{
    struct Node* next;
    struct Node* prev;
    enum ListType type;
    void* data;
};

typedef struct
{
    struct Node* head;
    struct Node* tail;
    int count;
}
LL;

/* linked-list function prototypes */
LL* ll_init();                                  /* initialize new empty LL */
void ll_print(LL* list);                                       /* prints LL*/
bool ll_append(LL* list, void* data, enum ListType type);        /* append */
bool ll_prepend(LL* list, void* data, enum ListType type);      /* prepend */
void* ll_pop_end(LL* list);                    /* pop last element from LL */
void* ll_pop_front(LL* list);                 /* pop first element from LL */
void ll_clear(LL* list, bool deep);           /* clear all entries from LL */
bool ll_contains(LL* list, void* data, enum ListType type);      /* search */
bool ll_remove_first(LL* list,          /* remove first occurrence from LL */
        void* data, enum ListType type);
bool ll_remove_index(LL* list, int index);         /* remove node by index */
bool ll_splice(LL* list, void* data,               /* insert node by index */
        enum ListType type, int index);
void* ll_get(LL* list, int index);        /* get node data by index (peek) */

#endif
