#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

/* helper function prototypes */
void _print_node(Node* node);
Node* _create_node(void* data, enum QueueType type);


/*
 * Function:  queue_init
 * --------------------
 *  initializes an empty queue
 *
 *  returns: ptr to queue structure with 0 nodes
 */
Queue* queue_init()
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->head = NULL;
    queue->tail = NULL;
    queue->count = 0;
    return queue;
}


/*
 * Function:  queue_print
 * --------------------
 *  prints the input queue to the console
 *
 *  queue: (Queue*) the queue
 *
 *  returns: none (prints to screen)
 */
void queue_print(Queue* queue)
{
    Node* current = queue->head;
    while (current != NULL)
    {
        _print_node(current);
        current = current->next;
    }
    printf("\n");
}


/*
 * Function:  queue_enqueue
 * --------------------
 *  creates node using input data and appends it to end of queue 
 *
 *  queue: (Queue*) queue to which new node will be appended 
 *  data: (void*) void ptr representing the value of the node to be added
 *  type: (enum QueueType) data type; one of INT, DOUBLE, CHAR, STRING, or DATA
 *
 *  returns: true if node successfully appended, false otherwise 
 */
bool queue_enqueue(Queue* queue, void* data, enum QueueType type)
{
    Node* to_add = _create_node(data, type);
    to_add->prev = queue->tail;
    if (queue->tail)
    {
        queue->tail->next = to_add;
    }
    queue->tail = to_add;
    queue->head = (queue->count == 0) ? to_add : queue->head;
    queue->count++;
    return true;
} 


/*
 * Function:  queue_dequeue
 * --------------------
 *  removes head node from Queue and returns ptr its data value
 *
 *  queue: (Queue*) queue from which to pop
 *
 *  returns: void ptr to dequeued node's data value, or NULL if Queue empty 
 */
void* queue_dequeue(Queue* queue)
{
    if (queue->count == 0) {return NULL;}
    Node* to_remove = queue->head;
    void* node_data = to_remove->data;
    if (queue->count == 1)
    {
        queue->head = NULL;
        queue->tail = NULL;
        queue->count = 0;
    }
    else
    {
        queue->head->next->prev = NULL;
        queue->head = queue->head->next;
        queue->count--;
    }
    free(to_remove);
    return node_data;
}


/*
 * Function:  queue_clear
 * --------------------
 *  clears the input Queue of all its Nodes
 *  ***does not free the Queue structure itself***
 *
 *  queue: (Queue*) the queue to clear
 *  deep: (bool) determines whether to perform a shallow deep clear
 *          false - free all nodes in input Queue
 *          true - free all nodes along with the data of each node
 *
 *  returns: none
 */
void queue_clear(Queue* queue, bool deep)
{
    Node* current = queue->head;
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
    queue->count = 0;
    queue->head = NULL;
    queue->tail = NULL;
    return;
}


/*
 * Function:  queue_contains
 * --------------------
 *  determines whether node with given value exists in queue 
 *
 *  queue: (Queue*) queue to search
 *  data: (void*) void ptr to data to be searched for
 *  type: (enum QueueType) data type; one of INT, DOUBLE, CHAR, STRING, or DATA
 *
 *  returns: true if node matching value found, false otherwise
 */
bool queue_contains(Queue* queue, void* data, enum QueueType type)
{
    Node* current = queue->head;
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
 * Function:  queue_front
 * --------------------
 *  returns ptr to data contained front node of input Queue 
 *  does not delete the node or its data 
 *
 *  queue: (Queue*) the queue
 *
 *  returns: void ptr to node's data, or NULL if Queue empty
 */
void* queue_front(Queue* queue)
{
    return (queue->count > 0) ? queue->head->data : NULL;
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
 *  type: (enum QueueType) node data type
 *       one of INT, DOUBLE, CHAR, STRING, or DATA
 *
 *  returns: the created node
 */
Node* _create_node(void* data, enum QueueType type)
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

