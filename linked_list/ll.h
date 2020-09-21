#ifndef LL_H_  /* guard */
#define LL_H_
#include <stdbool.h>

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

void ll_print(struct LL* list);
void ll_add_end(struct LL* list, int val);
void ll_add_front(struct LL* list, int val);
struct LL* ll_new(int* vals, int vals_size);

#endif

