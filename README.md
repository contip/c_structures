# C Structures

A Collection of basic data structures not included in the C Standard Library

# Features
  - Binary Search Tree
  - Simple Linked-List (integers only)
  - Generic Doubly-Linked List (accepts any datatype)
  - Stack
  - Queue
  - (WIP) Hash Map
 
# Motivation

I took my University's Data Structures course during the height of the COVID-19
pandemic, in what was the inaugural semester for the course material being
converted to Python.  With no examinations, no classes, and only four
assignments (fill-in-the-blank style) comprising the entirety of the graded
coursework, I completed the class with an unsatisfactory grasp of the covered
material.

Further, I have often encountered situations in which the need for a data
structure not included in the C standard library has arisen, and despite the
existence of numerous libraries already containing these structures, this
project was undertaken in an effort to meet these needs while simultaneously
contributing to my practical knowledge of data structures, their implementation,
and their usage.

# API
### Binary Search Tree
##### BST* bst_init(int* vals, int vals_size)
Initialize a `BST` with nodes corresponding to the input array of integers
(its size must also be specified).  Values are added to the tree sequentially
 from left to right.  Initialize an empty BST with a NULL pointer and a
`vals_size` of 0.

```c
int num_vals = 5;
int vals[num_vals] = { 1, 2, 3, 4, 5 };
BST* my_bst = bst_init(vals, num_vals);
```
```c
BST* my_bst = bst_init(NULL, 0);  // empty BST
```

##### void bst_add(BST* bst, int key)
Initialize a node with specified `key` value and add it to proper location
in the specified `bst`.  Becomes the root node if `bst` was empty.

```c
bst_add(my_bst, 15);
```

##### int* bst_traverse(BST* bst, int order)
Traverses the input `bst` in the specified `order`, returning an array of
integers representing the keys of each node visited, in the order visited.
Specify `order` as one of:
  -  `0` in-order
  -  `1` pre-order
  -  `2` post-order
 
```c
int* pre_order_results = bst_traverse(my_bst, 1);
```

##### Node* bst_find(BST* bst, int key)
Searches input `bst` for a node with specified `key` value.  Returns ptr to
the Node if found, NULL otherwise.

```c
Node* found_node = bst_find(my_bst, search_val);
```

##### bool bst_remove(BST* bst, int key)
Searches input `bst` for node with specified `key`, removing it and returning
true if found, false otherwise.

```c
bst_remove(my_bst, remove_val);
```

##### int bst_root_val(BST* bst)
Returns the value of the key of the root node of the specified `bst`.

```c
int root_val = bst_root_val(my_bst);
```

##### int bst_max_depth(BST* bst)
Returns the number of nodes along a longest path from the root of the input
`bst` to the farthest leaf node

```c
int max_depth = bst_max_depth(my_bst);
```
##### int bst_min_depth(BST* bst)
Returns the number of nodes along a shortest path from the root of the input
`bst` to the closest leaf node

```c
int min_depth = bst_min_depth(my_bst);
```

##### int bst_node_level(BST* bst, Node* node)
Returns the distance of the specified `node` from the root node of the given
`bst`.

```c
int node_level = bst_node_level(my_bst, node_to_check);
```

##### int bst_clear(BST* bst)
Clears specified `bst` of all its nodes.  Does not free the `bst` structure
itself.

```c
bst_clear(my_bst);
```

### Generic Doubly-Linked List
##### LL* ll_init()
Initializes an empty linked list
```c
LL* my_linked_list = ll_init();
```

##### void ll_print(LL* list)
Prints the specified linked `list` to the console.  Node values are printed
directly for Nodes of type `INT`, `DOUBLE`, `CHAR`, or `STRING`, while object
address is printed for Nodes storing custom datatypes.

```c
ll_print(my_linked_list);
```

##### bool ll_append(LL* list, void* data, enum ListType type)
Creates Node with specified `data` and `type` and appends it to the end of the
given linked `list`.  Provide a void pointer to the `data` in question and
specify the `type` of the node to be added as one of:
 - INT
 - DOUBLE
 - CHAR
 - STRING
 - DATA
```c
int i, node_vals_size = 5;
int node_vals[node_vals_size] = { 1, 2, 3, 4, 5 };
for (i = 0; i < node_vals_size; i++)
{
    ll_append(my_linked_list, &node_vals[i], INT);
}
```

##### bool ll_prepend(LL* list, void* data, enum ListType type)
Creates Node with specified `data` and `type` and prepends it to the beginning
of the given linked `list`.  Provide a void pointer to the `data` in question
and specify the `type` of the node to be added.
```c
struct TestStruct
{
    int property_1;
    double property_2;
};
struct TestStruct* test_obj = malloc(sizeof(struct TestStruct));
test_obj->property_1 = 1;
test_obj->property_2 = 1.2;
ll_prepend(my_linked_list, (void*)test_obj, DATA);
```

##### void* ll_pop_end(LL* list)
Pops tail node from end of specified linked `list`, freeing the Node and
returning a void pointer to its data, or NULL if linked list empty.
```c
void* result = ll_pop_end(my_linked_list);
assert(((struct TestStruct*)result)->property_1 == 1);
```

##### void* ll_pop_front(LL* list)
Pops head node from front of specified linked `list`, freeing the Node and
returning a void pointer to its data, or NULL if linked list empty.
```c
void* result = ll_pop_front(my_linked_list);
```

##### void ll_clear(LL* list, bool deep)
Clears the input linked `list` of all its Nodes.  If `deep` is set, also frees
the data pointed to by each Node.  Does not free the linked `list` structure
itself.
```c
ll_clear(my_linked_list, false);   // clear Nodes, retain data
free(my_linked_list);
ll_clear(my_linked_list_2, true);  // clear everything
free(my_linked_list_2);
```

##### bool ll_contains(LL* list, void* data, enum ListType type)
Searches specified linked `list` for a node of the specified `type` containing
a reference to the specified `data`.  Returns true if found, false otherwise.

```c
if (ll_contains(my_linked_list, (void*)to_search, DATA)
{
    printf("Donut\n");
}
```

##### bool ll_remove_first(LL* list, void* data, enum ListType type)
Searches specified linked `list` for a node of the specified `type` containing
a reference to the specified `data`.  Removes the first occurrence and returns
true if found, false otherwise.
```c
ll_remove_first(my_linked_list, &string_val, STRING);
```

##### bool ll_remove_index(LL* list, int index)
Removes Node associated with the specified `index` from the given linked `list`
and returns true if `index` valid, false otherwise.
```c
ll_remove_index(my_linked_list, 0);  // remove head
ll_remove_index(my_linked_list, my_linked_list->count - 1);  // remove tail
```

##### bool ll_splice(LL* list, void* data, enum ListType type, int index)
Creates Node with specified `data` and `type` and inserts it at the specified
`index` position in the given linked `list`.  Returns true if successful,
false otherwise.
```c
ll_splice(my_linked_list, &char_val, CHAR, 3);
```

##### void* ll_get(LL* list, int index)
Returns pointer to data referred to by the Node at the specified `index` of the
given linked `list`.  Does not remove the Node or its data.

```c
int int_val = 5;
ll_splice(my_linked_list, &int_val, INT, 0);
assert(*((int*)ll_get(my_linked_list, 0)) == 5);
```

### Simple Linked List
The simple linked list implementation offers all of the same procedures as the
generic linked list with a much simpler interface.  Major differences between
the two implementations are noted.

##### SLL* sll_init(int* vals, int vals_size)
Initialize simple linked list with an array of integers and the size of the
array.  Initialize an empty SLL by passing a NULL pointer and a `vals_size`
of 0.

 - void sll_print(SLL* list)
 - void sll_append(SLL* list, int val)
 - void sll_prepend(SLL* list, int val)
 - int sll_pop_end(SLL* list)
 - int sll_pop_front(SLL* list)
 - bool sll_contains(SLL* list, int val)
 - bool sll_remove_first(SLL* list, int val)
 - bool sll_remove_index(SLL* list, int index)
 - void sll_splice(SLL* list, int index, int val)
##### void sll_clear(SLL* list)
Clears the specified simple linked `list`.  Does not require any additional
parameters.

Additionally, the simple linked provides the following function:
##### int* sll_to_array(SLL* list)
Returns an array of integers representing the values of the Nodes of the
specified linked `list`

```c
int* my_array = sll_to_array(my_linked_list);
free(my_array);
```


### Stack
##### Stack* stack_init()
Initializes a new, empty stack.

```c
Stack* my_stack = stack_init();
```

##### void stack_print(Stack* stack)
Prints the specified `stack` to the console.  Nodes storing built-in datatypes
are printed directly, custom datatypes print the pointer address.

```c
stack_print(my_stack);
```

##### bool stack_push(Stack* stack, void* data, enum StackType type)
Creates Node with specified `data` and `type` and pushes it onto the top of the
given `stack`.  Returns true if successful, false otherwise.

```c
int my_int = 5;
stack_push(my_stack, &my_int, INT);
```

##### void* stack_pop(Stack* stack)
Pops the top Node from the specified `stack`, freeing the Node and returning a
pointer to its data, or NULL if stack empty.

```c
int* result = stack_pop(my_stack);
assert(*result == 5);
free(result);
```

##### void stack_clear(Stack* stack, bool deep)
Clears the input `stack` of all its Nodes.  If `deep` is set, also frees the
data pointed to by each Node.  Does not free the `stack` structure itself.
```c
stack_clear(my_stack, false);   // clear Nodes, retain data
free(my_stack);
stack_clear(my_stack_2, true);  // clear everything
free(my_stack_2);
```

##### bool stack_contains(Stack* stack, void* data, enum StackType type)
Searches specified `stack` for a node of the specified `type` containing a 
reference to the specified `data`.  Returns true if found, false otherwise.

```c
int my_int = 5;
stack_push(my_stack, &my_int, INT);
assert(stack_contains(my_stack, &my_int, INT));
```
##### void* stack_peek(Stack* stack)
Returns pointer to the data referred to by the top Node of the input `stack`.
Does not delete the Node or its data.

```c
int my_int = 5;
stack_push(my_stack, &my_int, INT);
assert(my_stack->count == 1)
int* result = stack_peek(my_stack);
assert(*result == 5);
assert(my_stack->count == 1)
```

### Queue
##### Queue* queue_init()
Initializes a new, empty Queue.

```c
Queue* my_queue = queue_init();
```

##### void queue_print(Queue* queue)
Prints the specified `queue` to the console.  Nodes storing built-in datatypes
are printed directly, custom datatypes print the pointer address.

```c
queue_print(my_queue);
```

##### bool queue_enqueue(Queue* queue, void* data, enum QueueType type)
Creates Node with specified `data` and `type` and appends it to the end of the
given `queue`.  Returns true if successful, false otherwise.

```c
int my_int = 5;
queue_enqueue(my_queue, &my_int, INT);
```

##### void* queue_dequeue(Queue* queue)
Removes the front Node from the specified `queue`, freeing it and returning a
pointer to its data, or NULL if queue empty.

```c
void* result = queue_dequeue(my_queue);
```

##### void queue_clear(Queue* queue, bool deep)
Clears the input `queue` of all its Nodes.  If `deep` is set, also frees the
data pointed to by each Node.  Does not free the `queue` structure itself.
```c
queue_clear(my_queue, true);
```

##### bool queue_contains(Queue* queue, void* data, enum QueueType type)
Searches specified `queue` for a node of the specified `type` containing a
reference to the specified `data`.  Returns true if found, false otherwise.

```c
char my_char = 'A';
queue_enqueue(my_queue, &my_char, CHAR);
assert(queue_contains(my_queue, &my_char, CHAR));
```

##### void* queue_front(Queue* queue)
Returns pointer to the data referred to by the Node currently at the front
of the specified `queue`.  Does not delete the Node or its data.

```c
void* result = queue_front(my_queue);
```

### Installation
Include the header file of the desired structure in your program, and link the
relevant source file during compilation

```c
#include "gll.h"
```
```
clang my_program.c gll.c -o my_program
```

### Todos

 - Modify BST implementation to include general data in addition to key values
 - Hashmap

License
----

MIT
