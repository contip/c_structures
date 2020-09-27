#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gll.h"

/* private helper functions */
void _remove_node(LL* list, Node* node);
void _print_node(Node* node);
Node* _create_node(void* data, enum ListType type);


/*
 * Function:  ll_init
 * --------------------
 *  initializes an empty linked list
 *
 *  returns: ptr to linked list structure with 0 nodes
 */
LL* ll_init()
{
    LL* list = (LL*)malloc(sizeof(LL));
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
    return list;
}


/*
 * Function:  ll_print
 * --------------------
 *  prints the input linked list to the console
 *
 *  list: (LL*) the linked list
 *
 *  returns: none (prints to screen)
 */
void ll_print(LL* list)
{
    Node* current = list->head;
    while (current != NULL)
    {
        _print_node(current);
        current = current->next;
    }
    printf("\n");
}


/*
 * Function:  ll_append
 * --------------------
 *  creates node using input data and appends it to end of linked list 
 *
 *  list: (LL*) linked list to which new node will be appended 
 *  data: (void*) void ptr representing the value of the node to be added
 *  type: (enum ListType) data type; one of INT, DOUBLE, CHAR, STRING, or DATA
 *
 *  returns: true if node successfully appended, false otherwise 
 */
bool ll_append(LL* list, void* data, enum ListType type)
{
    Node* to_add = _create_node(data, type);
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
 * Function:  ll_prepend
 * --------------------
 *  creates node using input data and prepends it to front of linked list 
 *
 *  list: (LL*) linked list to which new node will be added 
 *  data: (void*) void ptr representing the value of the node to be added
 *  type: (enum ListType) data type; one of INT, DOUBLE, CHAR, STRING, or DATA
 *
 *  returns: true if node successfully prepended, false otherwise 
 */
bool ll_prepend(LL* list, void* data, enum ListType type)
{
    Node* to_add = _create_node(data, type);
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
 *  removes tail node from LL and returns ptr to its data value
 *
 *  list: (LL*) linked list from which to pop
 *
 *  returns: void ptr to popped node's data value, or NULL if LL empty 
 */
void* ll_pop_end(LL* list)
{
    if (list->count == 0) {return NULL;}
    Node* to_remove = list->tail;
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
 *  removes head node from LL and returns ptr its data value
 *
 *  list: (LL*) linked list from which to pop
 *
 *  returns: void ptr to popped node's data value, or NULL if LL empty 
 */
void* ll_pop_front(LL* list)
{
    if (list->count == 0) {return NULL;}
    Node* to_remove = list->head;
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
 *  clears input LL of all its Nodes
 *  ***does not free the LL structure itself***
 *
 *  list: (LL*) the linked list to clear
 *  deep: (bool) determines whether to perform a shallow deep clear
 *          false - free all nodes in input LL
 *          true - free all nodes along with the data of each node
 *
 *  returns: none
 */
void ll_clear(LL* list, bool deep)
{
    Node* current = list->head;
    while (current != NULL)
    {
        Node* prev = current;
        if (deep)
        {
            if (current->type != DATA)
            {
                void* node_data = current->data;
                free(node_data);
            }
        }
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
 *  list: (LL*) linked list to search
 *  data: (void*) void ptr to data to be searched for
 *  type: (enum ListType) data type; one of INT, DOUBLE, CHAR, STRING, or DATA
 *
 *  returns: true if node matching value found, false otherwise
 */
bool ll_contains(LL* list, void* data, enum ListType type)
{
    Node* current = list->head;
    while (current != NULL)
    {
        switch (type)
        {
            case INT:
                if (current->type == INT)
                {
                    if (*((int*)current->data) == *((int*)data))
                    {
                        return true;
                    }
                }
                break;
            case DOUBLE:
                if (current->type == DOUBLE)
                {
                    if (*((double*)current->data) == *((double*)data))
                    {
                        return true;
                    }
                }
                break;
            case CHAR:
                if (current->type == CHAR)
                {
                    if (*((char*)current->data) == *((char*)data))
                    {
                        return true;
                    }
                }
                break;
            case STRING:
                if (current->type == STRING)
                {
                    if (strcmp((char*)current->data, (char*)data) == 0)
                    {
                        return true;
                    }
                }
                break;
            case DATA:
                if (current->type == DATA)
                {
                    /* in the case of general data, check if the two pointers
                     * both refer to the same object */
                    if (current->data == data)
                    {
                        return true;
                    }
                }
                break;
            default:
                return false;
        }
        current = current->next;
    }
    return false;
}


/*
 * Function:  ll_remove_first
 * --------------------
 *  removes first node from linked list with value matching input value
 *
 *  list: (LL*) the linked list from which to delete
 *  data: (void*) void ptr to data to search nodes for
 *  type: (enum ListType) data type; one of INT, DOUBLE, CHAR, STRING, or DATA
 *
 *  returns: true if node successfully removed, false otherwise
 */
bool ll_remove_first(LL* list, void* data, enum ListType type)
{
    Node* current = list->head;
    while (current != NULL)
    {
        switch (type)
        {
            case INT:
                if (current->type == INT)
                {
                    if (*((int*)current->data) == *((int*)data))
                    {
                        _remove_node(list, current);
                        return true;
                    }
                }
                break;
            case DOUBLE:
                if (current->type == DOUBLE)
                {
                    if (*((double*)current->data) == *((double*)data))
                    {
                        _remove_node(list, current);
                        return true;
                    }
                }
                break;
            case CHAR:
                if (current->type == CHAR)
                {
                    if (*((char*)current->data) == *((char*)data))
                    {
                        _remove_node(list, current);
                        return true;
                    }
                }
                break;
            case STRING:
                if (current->type == STRING)
                {
                    if (strcmp((char*)current->data, (char*)data) == 0)
                    {
                        _remove_node(list, current);
                        return true;
                    }
                }
                break;
            case DATA:
                if (current->type == DATA)
                {
                    if (current->data == data)
                    {
                        _remove_node(list, current);
                        return true;
                    }
                }
                break;
            default:
                return false;
        }
        current = current->next;
    }
    return false;
}


/*
 * Function:  ll_remove_index
 * --------------------
 *  removes node associated with input index, if it exists
 *
 *  list: (LL*) the linked list from which to delete
 *  index: (int) index of the node to be deleted
 *
 *  returns: true if node successfully removed, false otherwise
 */
bool ll_remove_index(LL* list, int index)
{
    if (index >= list->count)
    {
        return false;
    }
    if (index == 0)
    {
        _remove_node(list, list->head);
        return true;
    }
    if (index == list->count - 1)
    {
        _remove_node(list, list->tail);
        return true;
    }
    int counter = 0;
    Node* current_node = list->head;
    while (counter != index)
    {
        counter++;
        current_node = current_node->next;
    }
    _remove_node(list, current_node);
    return true;
}


/*
 * Function:  ll_splice
 * --------------------
 *  creates node with specified value and inserts at specified position in LL
 *
 *  list: (LL*) linked list to which new node will be added 
 *  data: (void*) void ptr to the value of the node to be added
 *  type: (enum ListType) data type; one of INT, DOUBLE, CHAR, STRING, or DATA
 *  index: (int) index at which to insert the new node
 *
 *  returns: true if node successfully inserted, false otherwise
 */
bool ll_splice(LL* list, void* data, enum ListType type, int index)
{
    if (index >= list->count)
    {
        return (index == 0 && list->count == 0) ?
            ll_prepend(list , data, type) : false;
    }
    if (index == 0)
    {
        return ll_prepend(list, data, type);
    }
    Node* to_add = _create_node(data, type);
    int counter = 0;
    Node* current_node = list->head;
    while (counter != index)
    {
        counter++;
        current_node = current_node->next;
    }
    to_add->prev = current_node->prev;
    to_add->next = current_node;
    current_node->prev->next = to_add;
    current_node->prev = to_add;
    list->count++;
    return true;
}


/*
 * Function:  ll_get
 * --------------------
 *  returns ptr to data contained in node specified by input index
 *  does not delete the node or its data 
 *
 *  list: (LL*) the linked list
 *  index: (int) index of the node whose data will be retrieved 
 *
 *  returns: void ptr to node's data, or NULL if invalid index given
 */
void* ll_get(LL* list, int index)
{
    if (index == 0)
    {
        return (list->count > 0) ? list->head->data : NULL;
    }
    if (index >= list->count)
    {
        return NULL;
    }
    if (index == list->count - 1)
    {
        return list->tail->data;
    }
    int counter = 0;
    Node* current_node = list->head;
    while (counter != index)
    {
        counter++;
        current_node = current_node->next;
    }
   return current_node->data; 
}


/* ====helper functions follow==== */
/*
 * Private Function:  _remove_node
 * --------------------
 *  removes specified node from specified linked list, freeing memory 
 *  assumes node exists in LL, and that LL is not empty
 *
 *  list: (LL*) linked list from which to delete
 *  node: (Node*) ptr to node being removed 
 *
 *  returns: none 
 */
void _remove_node(LL* list, Node* node)
{
    if (node->type != DATA)
    {
        free(node->data);
    }
    if (list->count == 1 || list->tail == node)
    {
        ll_pop_end(list);
        return;
    }
    if (list->head == node)
    {
        ll_pop_front(list);
        return;
    }
    node->prev->next = node->next;
    node->next->prev = node->prev;
    list->count--;
    free(node);
}


/*
 * Private Function:  _print_node
 * --------------------
 *  prints the data stored in input node to the screen
 *
 *  node: (Node*) ptr to node whose value will be printed
 *
 *  returns: none 
 */
void _print_node(Node* node)
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
        case DATA:
            printf("Object(%p) ", node->data);
            break;
        default:
            printf("Error printing node data!\n");
    }
}


/*
 * Private Function:  _create_node
 * --------------------
 *  creates node using input data
 *
 *  data: (void*) void ptr to the value that will be assigned to the node
 *  type: (enum ListType) node data type
 *       one of INT, DOUBLE, CHAR, STRING, or DATA
 *
 *  returns: ptr to the created Node
 */
Node* _create_node(void* data, enum ListType type)
{
    int data_size;
    Node* to_add = (Node*)malloc(sizeof(Node));
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
        case DATA:
            /* in the case of general data, just store pointer */
            to_add->data = data;
            return to_add;
        default:
            return NULL;
    }
    /* copy data by byte into newly allocated memory */
    int i;
    for (i = 0; i < data_size; i++)
    {
        *(char*)(to_add->data + i) = *(char*)(data + i);
    }
    return to_add;
}

