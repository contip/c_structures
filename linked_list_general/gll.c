#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "gll.h"


/*
 * Private Function:  _print_node
 * --------------------
 *  prints the data stored in input node to the screen
 *
 *  node: (struct Node*) ptr to node whose value will be printed
 *
 *  returns: none 
 */
void _print_node(struct Node* node)
{
    switch (node->type)
    {
        case INT:
            printf("%d ", *((int*)node->data));
            break;
        case DOUBLE:
            printf("%f ", *((double*)node->data));
            break;
        case CHAR:
            printf("%c ", *((char*)node->data));
            break;
        case STRING:
            printf("%s ", (char*)node->data);
            break;
        default:
            printf("Error printing node data!\n");
    }
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
        _print_node(current);
        current = current->next;
    }
}


/*
 * Function:  ll_init
 * --------------------
 *  initializes an empty linked list
 *
 *  returns: ptr to linked list structure with 0 nodes
 */
struct LL* ll_init()
{
    struct LL* list = (struct LL*)malloc(sizeof(struct LL));
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
    return list;
}


/*
 * Private Function:  _create_node
 * --------------------
 *  creates node using input data
 *
 *  data: (void*) void ptr to the value that will be assigned to the node
 *  type: (enum ListType) node data type; one of INT, DOUBLE, CHAR, or STRING
 *
 *  returns: true if node successfully appended, false otherwise 
 */
struct Node* _create_node(void* data, enum ListType type)
{
    int data_size;
    struct Node* to_add = (struct Node*)malloc(sizeof(struct Node));
    to_add->type = type;
    to_add->next = NULL;
    to_add->prev = NULL;
    /* allocate memory for node's data */
    switch (type)
    {
        case INT:
            to_add->data = malloc(sizeof(int));
            data_size = sizeof(int);
            break;
        case DOUBLE:
            to_add->data = malloc(sizeof(double));
            data_size = sizeof(double);
            break;
        case CHAR:
            to_add->data = malloc(sizeof(char));
            data_size = sizeof(char);
            break;
        case STRING:
            data_size = strlen((const char*)data) + 1;
            to_add->data = malloc(sizeof(char) * data_size);
            break;
        default:
            return false;
    }
    /* copy data by byte into newly allocated memory */
    int i;
    for (i = 0; i < data_size; i++)
    {
        *(char*)(to_add->data + i) = *(char*)(data + i);
    }
    return to_add;
}


/*
 * Function:  ll_add_end
 * --------------------
 *  creates node using input data and appends it to end of linked list 
 *
 *  list: (struct LL*) linked list to which new node will be appended 
 *  data: (void*) void ptr to the value of the node to be added
 *  type: (enum ListType) data type; one of INT, DOUBLE, CHAR, or STRING
 *
 *  returns: true if node successfully appended, false otherwise 
 */
bool ll_add_end(struct LL* list, void* data, enum ListType type)
{
    struct Node* to_add = _create_node(data, type);
    to_add->prev = list->tail;
    if (list->tail)
    {
        list->tail->next = to_add;
    }
    list->tail = to_add;
    list->head = (list->count == 0) ? to_add : list->head;
    list->count++;
    return true;
} 


/*
 * Function:  ll_add_front
 * --------------------
 *  creates node using input data and prepends it to front of linked list 
 *
 *  list: (struct LL*) linked list to which new node will be added 
 *  data: (void*) void ptr to the value of the node to be added
 *  type: (enum ListType) data type; one of INT, DOUBLE, CHAR, or STRING
 *
 *  returns: true if node successfully prepended, false otherwise 
 */
bool ll_add_front(struct LL* list, void* data, enum ListType type)
{
    struct Node* to_add = _create_node(data, type);
    to_add->next = list->head;
    if (list->head)
    {
        list->head->prev = to_add;
    }
    list->head = to_add;
    list->tail = (list->count == 0) ? to_add : list->tail;
    list->count++;
    return true;
} 


/*
 * Function:  ll_pop_end
 * --------------------
 *  removes tail node from LL, returns ptr to node's data value
 *  ***returned node data is malloced and must be freed by caller***
 *
 *  list: (struct LL*) linked list from which to pop
 *
 *  returns: void ptr to popped node's data value, or NULL if LL empty 
 */
void* ll_pop_end(struct LL* list)
{
    if (list->count == 0) {return NULL;}
    /* set pointers to the Node and its data */
    struct Node* to_remove = list->tail;
    void* node_data = to_remove->data;

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
    free(to_remove);
    return node_data;
}


/*
 * Function:  ll_pop_front
 * --------------------
 *  removes head node from LL, returns ptr to node's data value
 *  ***returned node data is malloced and must be freed by caller***
 *
 *  list: (struct LL*) linked list from which to pop
 *
 *  returns: void ptr to popped node's data value, or NULL if LL empty 
 */
void* ll_pop_front(struct LL* list)
{
    if (list->count == 0) {return NULL;}
    /* set pointers to the Node and its data */
    struct Node* to_remove = list->head;
    void* node_data = to_remove->data;
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
    free(to_remove);
    return node_data;
}


/*
 * Function:  ll_clear
 * --------------------
 *  clears LL by freeing each Node as well as each Node's data
 *  does not free the LL structure itself 
 *
 *  list: (struct LL*) the linked list to clear
 *
 *  returns: none
 */
void ll_clear(struct LL* list)
{
    struct Node* current = list->head;
    while (current != NULL)
    {
        struct Node* prev = current;
        void* node_data = current->data;
        free(node_data);
        current = current->next;
        free(prev);
    }
    list->count = 0;
    list->head = NULL;
    list->tail = NULL;
    return;
}


/*
 * Function:  ll_contains
 * --------------------
 *  determines whether node with given value exists in linked list 
 *
 *  list: (struct LL*) the linked list
 *  data: (void*) void ptr to data to be searched for
 *  type: (enum ListType) data type; one of INT, DOUBLE, CHAR, or STRING
 *
 *  returns: true if node matching value found, false otherwise
 */
bool ll_contains(struct LL* list, void* data, enum ListType type)
{
    struct Node* current = list->head;
    switch (type)
    {
        case INT:
            while (current != NULL)
            {
                if (*((int*)current->data) == *((int*)data))
                {
                    return true;
                }
                current = current->next;
            }
            break;
        case DOUBLE:
            while (current != NULL)
            {
                if (*((double*)current->data) == *((double*)data))
                {
                    return true;
                }
                current = current->next;
            }
            break;
        case CHAR:
            while (current != NULL)
            {
                if (*((char*)current->data) == *((char*)data))
                {
                    return true;
                }
                current = current->next;
            }
            break;
        case STRING:
            while (current != NULL)
            {
                if (strcmp((char*)current->data, (char*)data) == 0)
                {
                    return true;
                }
                current = current->next;
            }
            break;
        default:
            return false;
    }
    return false;
}

