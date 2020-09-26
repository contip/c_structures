#ifndef QUEUE_H_  /* guard */
#define QUEUE_H_
#include <stdbool.h>


/* data types accepted by Queue */
enum QueueType
{
    INT = 0,
    DOUBLE,
    CHAR,
    STRING,
    DATA,
};

/* Node and Queue structure definitions */
typedef struct Node Node;
struct Node
{
    struct Node* next;
    struct Node* prev;
    enum QueueType type;
    void* data;
};

typedef struct
{
    struct Node* head;
    struct Node* tail;
    int count;
}
Queue;

/* queue function prototypes */
Queue* queue_init();                          /* initialize new empty Queue */
void queue_print(Queue* queue);                              /* prints Queue*/
bool queue_enqueue(Queue* queue,                 /* enqueue to end of Queue */
        void* data, enum QueueType type);   
void* queue_dequeue(Queue* queue);           /* dequeue from front of Queue */
void queue_clear(Queue* queue, bool deep);                   /* clear Queue */
bool queue_contains(Queue* queue,                  /* search Queue for data */
        void* data, enum QueueType type); 
void* queue_front(Queue* queue);      /* get data of node at front of Queue */

#endif
