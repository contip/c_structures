#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

/* returns array representing the linked list */
/* assumes ll is not empty */
int* ll_to_array(struct LL* list)
{
    /* initialize the array using the LL's count */
    int array_size = list->count;
    int* array = (int*)calloc(array_size, sizeof(int));

    /* populate array with values of LL nodes */
    struct Node* current = list->head;
    int i = 0;
    while (current != NULL)
    {
        array[i] = current->val;
        current = current->next;
        i++;
    }
    return array;
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

/* pops last item from ll, freeing the node and returning its value */
/* assumes LL is not empty */
int ll_remove_end(struct LL* list)
{
    struct Node* to_free = list->tail;
    int return_value = to_free->val;
    if (list->count == 1)
    {
        list->head = NULL;
        list->tail = NULL;
        list->count = 0;
    }
    else
    {
        list->tail->prev->next = NULL;
        list->tail = list->tail->prev;
        list->count--;
    }
    free(to_free);
    return return_value;
}

/* pops first item from ll, freeing the node and returning its value */
/* assumes LL is not empty */
int ll_remove_front(struct LL* list)
{
    /* create pointer to head of ll */
    struct Node* to_free = list->head;
    int return_value = to_free->val;
    if (list->count == 1)
    {
        list->head = NULL;
        list->tail = NULL;
        list->count = 0;
    }
    else
    {
        list->head->next->prev = NULL;
        list->head = list->head->next;
        list->count--;
    }
    free(to_free);
    return return_value;
}

/* returns true if a node exists in ll with value matchiing input value */
bool ll_contains(struct LL* list, int val)
{
    struct Node* current = list->head;
    while (current != NULL)
    {
        if (current->val == val)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

/* if input val exists in LL, removes first node with matching val and
 * returns true, false otherwise */
bool ll_remove_first_occurrence(struct LL* list, int val)
{
    if (list->count == 1 && list->head->val == val)
    {
        ll_remove_front;
        return true;
    }
    struct Node* current = list->head;
    while (current != NULL)
    {
        if (current->val == val)
        {
            /* remove the node */
            current->prev->next = current->next;
            current->next->prev = current->prev;
            list->count--;
            free(current);
            return true;
        }
        current = current->next;
    }
    return false;
}

/* removes LL node associated with input index and retruns true if index is
 * valid, false otherwise */
bool ll_remove_index(struct LL* list, int index)
{
    if (list->count == 1 && index == 0)
    {
        ll_remove_front;
        return true;
    }
    if (!(index > list->count - 1))
    {
        struct Node* to_remove = list->head;
        int count = 0;
        while (to_remove != NULL)
        {
            if (count == index)
            {
                /* remove the node */
                /* if head or tail is being removed, use above fxns */
                if (index == 0)
                {
                    ll_remove_front(list);
                    return true;
                }
                if (index == list->count - 1)
                {
                    ll_remove_end(list);
                    return true;
                }
                to_remove->prev->next = to_remove->next;
                to_remove->next->prev = to_remove->prev;
                list->count--;
                free(to_remove);
                return true;
            }
            count++;
            to_remove = to_remove->next;
        }
        return false;
    }
    return false;
}

