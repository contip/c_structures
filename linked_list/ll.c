#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ll.h"

struct LL* _create_ll();  /* internal function, initializes empty LL struct */


/*
 * Function:  ll_new
 * --------------------
 *  initializes a new linked list with entries based on the input array
 *  of integers, or an EMPTY linked list if size of input array is 0
 *
 *  vals: (int[]) array of ints representing LL node values
 *  vals_size: (int) size of vals array
 *
 *  returns: ptr to the initialized empty or populated linked list
 */
struct LL* ll_new(int* vals, int vals_size)
{
    struct LL* list = _create_ll();
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

/*
 * Function:  ll_print
 * --------------------
 *  prints the input linked list to the console
 *
 *  list: (struct LL*) the linked list
 *
 *  returns: none (prints to screen)
 */
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

/*
 * Function:  ll_to_array
 * --------------------
 *  returns an array of integers representing values of linked list nodes 
 *  assumes ll is not empty
 *
 *  list: (struct LL*) the linked list
 *
 *  returns: ptr to the array of ints representing LL node values
 */
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

/*
 * Function:  ll_add_end
 * --------------------
 *  creates node with input value and appends it to end of linked list
 *
 *  list: (struct LL*) the linked list
 *  val: (int) value of node to add to end of linked list
 *
 *  returns: none
 */
void ll_add_end(struct LL* list, int val)
{
    /* create the node, set its next to NULL */
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->val = val;
    new_node->next = NULL;
    struct Node* current = list->head;
    if (current == NULL)
    {
        /* if the ll was empty, add the new node as root and return */
        new_node->prev = NULL;
        list->head = new_node;
        list->tail = new_node;
        list->count++;
        return;
    }
    while (current->next != NULL)
    {
        /* otherwise, traverse the LL until reaching the terminal node */
        current = current->next;
    }
    /* set pointers to add the new node and increment count */
    current->next = new_node;
    new_node->prev = current;
    list->tail = new_node;
    list->count++;
    return;
}

/*
 * Function:  ll_add_front
 * --------------------
 *  creates node with input value and pushes it to front of linked list
 *
 *  list: (struct LL*) the linked list
 *  val: (int) value of node to add to front of linked list
 *
 *  returns: none
 */
void ll_add_front(struct LL* list, int val)
{
    /* create the node, set its prev to NULL */
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->val = val;
    new_node->prev = NULL;
    if (list->head == NULL)
    {
        /* if list was empty, insert new node as both root and tail */
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

/*
 * Function:  ll_remove_end
 * --------------------
 *  pops last item from linked list, freeing node and returning its value 
 *  assumes input linked list is not empty
 *
 *  list: (struct LL*) the linked list
 *
 *  returns: integer representing the value of the node removed from end
 */
int ll_remove_end(struct LL* list)
{
    struct Node* to_free = list->tail;
    int return_value = to_free->val;
    if (list->count == 1)
    {
        /* must set additional NULL pointers if only 1 item in LL */
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
 * Function:  ll_remove_front
 * --------------------
 *  pops first item from linked list, freeing node and returning its value 
 *  assumes input linked list is not empty
 *
 *  list: (struct LL*) the linked list
 *
 *  returns: integer representing the value of the node removed from front 
 */
int ll_remove_front(struct LL* list)
{
    struct Node* to_free = list->head;
    int return_value = to_free->val;
    if (list->count == 1)
    {
        /* must set additional NULL pointers if only 1 item in LL */
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
 * Function:  ll_contains
 * --------------------
 *  determines whether node with given value exists in linked list 
 *
 *  list: (struct LL*) the linked list
 *  val: (int) value to be searched for
 *
 *  returns: true if node matching value found, false otherwise
 */
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

/*
 * Function:  ll_remove_first_occurrence
 * --------------------
 *  removes first node from linked list with value matching input value
 *
 *  list: (struct LL*) the linked list
 *  val: (int) value of the node to be deleted
 *
 *  returns: true if node successfully removed, false otherwise
 */
bool ll_remove_first_occurrence(struct LL* list, int val)
{
    if (list->count == 1 && list->head->val == val)
    {
        ll_remove_front(list);
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

/*
 * Function:  ll_remove_index
 * --------------------
 *  removes LL node associated with input index, if input index valid
 *
 *  list: (struct LL*) the linked list
 *  index: (int) index position of the node to be removed
 *
 *  returns: true if node successfully removed, false otherwise
 */
bool ll_remove_index(struct LL* list, int index)
{
    if (list->count == 1 || index == 0)
    {
        ll_remove_front(list);
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
                 * remove_front or remove_end */ 
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
 * Function:  ll_clear
 * --------------------
 *  deletes each node from input linked list, freeing memory of each
 *  does not delete or free the ll itself
 *  
 *  list: (struct LL*) the linked list to clear
 *
 *  returns: none
 */
void ll_clear(struct LL* list)
{
    while (list->count > 0)
    {
        ll_remove_front(list);
    }
    return;
}

/*
 * Function:  ll_insert_before
 * --------------------
 *  inserts a node with given value before the given index position in the LL
 *  if index 0 given, inserts at the beginning of the linked list
 *  
 *  list: (struct LL*) the linked list
 *  index: (int) index position before which new node is to be inserted
 *  val: (int) value of the new node to be inserted
 *
 *  returns: none
 */
void ll_insert_before(struct LL* list, int index, int val)
{
    if (index == 0)
    {
        ll_add_front(list, val);
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
    return;
}

/*
 * Function:  _create_ll
 * --------------------
 *  private function that initializes a LL structure
 *
 *  returns: none
 */
struct LL* _create_ll()
{
    struct LL* list = (struct LL*)malloc(sizeof(struct LL));
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
    return list;
}
