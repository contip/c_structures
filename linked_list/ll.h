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
int* ll_to_array(struct LL* list);
int ll_remove_end(struct LL* list);
int ll_remove_front(struct LL* list);
bool ll_contains(struct LL* list, int val);
bool ll_remove_first_occurrence(struct LL* list, int val);
bool ll_remove_index(struct LL* list, int index);

#endif

