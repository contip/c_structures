#include <stdio.h>
#include <stdlib.h>
#include "sll.h"

SLL* _create_ll();  /* internal function, initializes empty SLL struct */


/*
 * Function:  sll_init
 * --------------------
 *  initializes a new linked list with entries based on the input array
 *  of integers, or an EMPTY linked list if size of input array is 0
 *  ***create empty SLL with: sll_init(NULL, 0)*** 
 *
 *  vals: (int[]) array of ints representing SLL node values, in order
 *  vals_size: (int) size of vals array
 *
 *  returns: ptr to the initialized linked list
 */
SLL* sll_init(int* vals, int vals_size)
{
    SLL* list = _create_ll();
	if (vals_size != 0)
	{
		int i;
		for (i = 0; i < vals_size; i++)
		{
			sll_append(list, vals[i]);
		}
	}
    return list;
}


/*
 * Function:  sll_print
 * --------------------
 *  prints the input linked list to the console
 *
 *  list: (SLL*) linked list to print
 *
 *  returns: none
 */
void sll_print(SLL* list)
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


/*
 * Function:  sll_to_array
 * --------------------
 *  returns an array of integers representing values of linked list nodes 
 *  assumes ll is not empty
 *
 *  list: (SLL*) the linked list
 *
 *  returns: ptr to array of ints representing SLL node values
 */
int* sll_to_array(SLL* list)
{
    /* initialize the array using the SLL's count */
    int array_size = list->count;
    int* array = (int*)calloc(array_size, sizeof(int));
    /* populate array with values of SLL nodes */
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


/*
 * Function:  sll_append
 * --------------------
 *  creates node with input value and appends it to end of linked list
 *
 *  list: (SLL*) the linked list to which node will be appended
 *  val: (int) value of node to add to end of linked list
 *
 *  returns: none
 */
void sll_append(SLL* list, int val)
{
    /* create the node, set its next to NULL */
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->val = val;
    new_node->next = NULL;
    struct Node* current = list->head;
    if (current == NULL)
    {
        /* if list was empty, insert new node as both root and tail */
        new_node->prev = NULL;
        list->head = new_node;
        list->tail = new_node;
        list->count++;
        return;
    }
    while (current->next != NULL)
    {
        /* otherwise, traverse the SLL until reaching the terminal node */
        current = current->next;
    }
    /* set pointers to add the new node and increment count */
    current->next = new_node;
    new_node->prev = current;
    list->tail = new_node;
    list->count++;
}


/*
 * Function:  sll_prepend
 * --------------------
 *  creates node with input value and pushes it to front of linked list
 *
 *  list: (SLL*) the linked list
 *  val: (int) value of node to add to front of linked list
 *
 *  returns: none
 */
void sll_prepend(SLL* list, int val)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->val = val;
    new_node->prev = NULL;
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
}


/*
 * Function:  sll_pop_end
 * --------------------
 *  pops last item from linked list, freeing node and returning its value 
 *  ***assumes input linked list is not empty***
 *
 *  list: (SLL*) the linked list
 *
 *  returns: integer representing the value of the node removed from end
 */
int sll_pop_end(SLL* list)
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


/*
 * Function:  sll_pop_front
 * --------------------
 *  pops first item from linked list, freeing node and returning its value 
 *  ***assumes input linked list is not empty***
 *
 *  list: (SLL*) the linked list
 *
 *  returns: integer representing the value of the node removed from front 
 */
int sll_pop_front(SLL* list)
{
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


/*
 * Function:  sll_contains
 * --------------------
 *  determines whether node with given value exists in linked list 
 *
 *  list: (SLL*) the linked list to search
 *  val: (int) value to be searched for
 *
 *  returns: true if node matching value found, false otherwise
 */
bool sll_contains(SLL* list, int val)
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


/*
 * Function:  sll_remove_first
 * --------------------
 *  removes first node from linked list with value matching input value
 *
 *  list: (SLL*) the linked list to search
 *  val: (int) value of the node to be deleted
 *
 *  returns: true if node successfully removed, false otherwise
 */
bool sll_remove_first(SLL* list, int val)
{
    if (list->count == 1 && list->head->val == val)
    {
        sll_pop_front(list);
        return true;
    }
    struct Node* current = list->head;
    while (current != NULL)
    {
        if (current->val == val)
        {
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


/*
 * Function:  sll_remove_index
 * --------------------
 *  removes node associated with input index, if it exists
 *
 *  list: (SLL*) the linked list from which to delete
 *  index: (int) index position of the node to be removed
 *
 *  returns: true if node successfully removed, false otherwise
 */
bool sll_remove_index(SLL* list, int index)
{
    if (list->count == 1 || index == 0)
    {
        sll_pop_front(list);
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
                /* remove the node; if head or tail is being removed, use 
                 * pop_front or pop_end */ 
                if (index == 0)
                {
                    sll_pop_front(list);
                    return true;
                }
                if (index == list->count - 1)
                {
                    sll_pop_end(list);
                    return true;
                }
                /* update pointers to remove node from ll, then free memory */
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


/*
 * Function:  sll_clear
 * --------------------
 *  deletes each node from input linked list, freeing memory of each
 *  ***does not delete or free the SLL itself***
 *  
 *  list: (SLL*) the linked list to clear
 *
 *  returns: none
 */
void sll_clear(SLL* list)
{
    while (list->count > 0)
    {
        sll_pop_front(list);
    }
    return;
}


/*
 * Function:  sll_splice
 * --------------------
 *  inserts a node with given value at specified index position in SLL
 *  
 *  list: (SLL*) the linked list
 *  index: (int) index position at which new node is to be inserted
 *  val: (int) value of the new node to be inserted
 *
 *  returns: none
 */
void sll_splice(SLL* list, int index, int val)
{
    if (index == 0)
    {
        sll_prepend(list, val);
    }
    else
    {
        struct Node* to_add = (struct Node*)malloc(sizeof(struct Node));
        to_add->val = val;
        int current_index = 0;
        struct Node* current = list->head;
        while (current != NULL)
        {
            if (current_index == index)
            {
                /* add the node before current */
                to_add->prev = current->prev;
                to_add->next = current;
                current->prev->next = to_add;
                current->prev = to_add;
                list->count++;
                break;
            }
            current_index++;
            current = current->next;
        }
    }
}


/* ====helper functions follow====*/
/*
 * Function:  _create_ll
 * --------------------
 *  private function that initializes a SLL structure
 *
 *  returns: none
 */
SLL* _create_ll()
{
    SLL* list = (SLL*)malloc(sizeof(SLL));
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
    return list;
}
