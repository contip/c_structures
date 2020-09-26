#ifndef STACK_H_  /* guard */
#define STACK_H_
#include <stdbool.h>


/* data types accepted by stack */
enum StackType
{
    INT = 0,
    DOUBLE,
    CHAR,
    STRING,
    DATA,
};

/* Node and stack structure definitions */
typedef struct Node Node;
struct Node
{
    struct Node* next;
    struct Node* prev;
    enum StackType type;
    void* data;
};

typedef struct
{
    struct Node* head;
    struct Node* tail;
    int count;
}
Stack;

/* stack function prototypes */
Stack* stack_init();                          /* initialize new empty Stack */
void stack_print(Stack* stack);                              /* prints Stack*/
bool stack_push(Stack* stack, void* data,                  /* push to Stack */
        enum StackType type);                              
void* stack_pop(Stack* stack);                            /* pop from Stack */
void stack_clear(Stack* stack, bool deep);                   /* clear Stack */
bool stack_contains(Stack* stack,                  /* search Stack for data */
        void* data, enum StackType type); 
void* stack_peek(Stack* stack);                        /* peek top of Stack */ 

#endif
