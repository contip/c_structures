#include <stdio.h>
#include <stdlib.h>
#include "ll.h"

/* private: creates a new, empty LL */
struct LL* create_ll()
{
    struct LL* list = (struct LL*)malloc(sizeof(struct LL));
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
    return list;
}

/* initializes a new linked list based on input array of int, returns EMPTY ll if vals_size == 0 */
struct LL* ll_new(int* vals, int vals_size)
{
    struct LL* list = create_ll();
	if (vals_size != 0)
	{
		int i;
		for (i = 0; i < vals_size; i++)
		{
			ll_add_end(list, vals[i]);
		}
	}
    return list;
}

/* prints the input linked list */
void ll_print(struct LL* list)
{
    struct Node* current = list->head;
    while (current != NULL)
    {
        if (current->next == NULL)
        {
            printf("%d\n", current->val);
        }
        else
        {
            printf("%d --> ", current->val);
        }
        current = current->next;
    }
}

/* creates node with input value and appends to end of linked list */
void ll_add_end(struct LL* list, int val)
{
    /* create the node, set its next to NULL */
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->val = val;
    new_node->next = NULL;

    struct Node* current = list->head;
    /* if the ll was empty, add the new node as root and return */
    if (current == NULL)
    {
        new_node->prev = NULL;
        list->head = new_node;
        list->tail = new_node;
        list->count++;
        return;
    }
    /* otherwise, traverse the LL until reaching the terminal node */
    while (current->next != NULL)
    {
        current = current->next;
    }
    /* set parent/child relationships for terminal node and new_node */
    current->next = new_node;
    new_node->prev = current;
    list->tail = new_node;
    list->count++;
    return;
}

/* creates node with input value and pushes it to front of linked list */
void ll_add_front(struct LL* list, int val)
{
    /* create the node, set its prev to NULL */
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->val = val;
    new_node->prev = NULL;

    /* if list was empty, insert new node as root and tail */
    if (list->head == NULL)
    {
        new_node->next = NULL;
        list->head = new_node;
        list->tail = new_node;
    }
    else
    {
        list->head->prev = new_node;
        new_node->next = list->head;
        list->head = new_node;
    }
    list->count++;
    return;
}


