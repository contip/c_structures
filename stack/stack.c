#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

/* helper function prototypes */
void _print_node(Node* node);
Node* _create_node(void* data, enum StackType type);


/*
 * Function:  stack_init
 * --------------------
 *  initializes an empty stack
 *
 *  returns: ptr to stack structure with 0 nodes
 */
Stack* stack_init()
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->head = NULL;
    stack->tail = NULL;
    stack->count = 0;
    return stack;
}


/*
 * Function:  stack_print
 * --------------------
 *  prints the input stack to the console
 *
 *  stack: (Stack*) the stack
 *
 *  returns: none (prints to screen)
 */
void stack_print(Stack* stack)
{
    Node* current = stack->tail;
    while (current != NULL)
    {
        _print_node(current);
        current = current->prev;
    }
    printf("\n");
}


/*
 * Function:  stack_push
 * --------------------
 *  creates node using input data and pushes it to top of stack 
 *
 *  stack: (Stack*) stack to which new node will be pushed 
 *  data: (void*) void ptr representing the value of the node to be added
 *  type: (enum StackType) data type; one of INT, DOUBLE, CHAR, STRING, or DATA
 *
 *  returns: true if node successfully pushed, false otherwise 
 */
bool stack_push(Stack* stack, void* data, enum StackType type)
{
    Node* to_add = _create_node(data, type);
    to_add->prev = stack->tail;
    if (stack->tail)
    {
        stack->tail->next = to_add;
    }
    stack->tail = to_add;
    stack->head = (stack->count == 0) ? to_add : stack->head;
    stack->count++;
    return true;
} 


/*
 * Function:  stack_pop
 * --------------------
 *  pops top node from Stack and returns ptr to its data value
 *
 *  stack: (Stack*) stack from which to pop
 *
 *  returns: void ptr to popped node's data value, or NULL if Stack empty 
 */
void* stack_pop(Stack* stack)
{
    if (stack->count == 0) {return NULL;}
    Node* to_remove = stack->tail;
    void* node_data = to_remove->data;
    if (stack->count == 1)
    {
        stack->head = NULL;
        stack->tail = NULL;
        stack->count = 0;
    }
    else
    {
        stack->tail->prev->next = NULL;
        stack->tail = stack->tail->prev;
        stack->count--;
    }
    free(to_remove);
    return node_data;
}


/*
 * Function:  stack_clear
 * --------------------
 *  clears input Stack of all its Nodes
 *  ***does not free the Stack structure itself***
 *
 *  stack: (Stack*) the stack to clear
 *  deep: (bool) determines whether to perform a shallow deep clear
 *          false - free all nodes in input Stack
 *          true - free all nodes along with the data of each node
 *
 *  returns: none
 */
void stack_clear(Stack* stack, bool deep)
{
    Node* current = stack->head;
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
    stack->count = 0;
    stack->head = NULL;
    stack->tail = NULL;
    return;
}


/*
 * Function:  stack_contains
 * --------------------
 *  determines whether node with given value exists in stack 
 *
 *  stack: (Stack*) stack to search
 *  data: (void*) void ptr to data to be searched for
 *  type: (enum StackType) data type; one of INT, DOUBLE, CHAR, STRING, or DATA
 *
 *  returns: true if node matching value found, false otherwise
 */
bool stack_contains(Stack* stack, void* data, enum StackType type)
{
    Node* current = stack->head;
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
 * Function:  stack_peek
 * --------------------
 *  returns ptr to data contained in node on top of the input stack
 *  does not delete the node or its data 
 *
 *  stack: (Stack*) the stack to peek from
 *
 *  returns: void ptr to node's data, or NULL stack empty
 */
void* stack_peek(Stack* stack)
{
    return (stack->count > 0) ? stack->tail->data : NULL;
}


/* ====helper functions follow==== */


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
 *  type: (enum StackType) node data type
 *       one of INT, DOUBLE, CHAR, STRING, or DATA
 *
 *  returns: ptr to the created Node
 */
Node* _create_node(void* data, enum StackType type)
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

