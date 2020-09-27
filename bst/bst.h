#ifndef BST_H_  /* guard */
#define BST_H_
#include <stdbool.h>

/* Node and BST structure definitions */
typedef struct Node Node;
struct Node
{
    int key;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
};

typedef struct 
{
    struct Node* root;
    int count;
}
BST;

/* binary search tree function prototypes */
BST* bst_init(int* vals, int vals_size);      /* create new BST from array */
void bst_add(BST* bst, int key);           /* add node w/ given val to BST */
int* bst_traverse(BST* bst, int order);                    /* traverse BST */
Node* bst_find(BST* bst, int key);            /* search BST for val */
bool bst_remove(BST* bst, int key);         /* remove node w/ matching val */
int bst_root_val(BST* bst);                      /* get value of root node */
int bst_max_depth(BST* bst);                       /* get max depth of BST */
int bst_min_depth(BST* bst);                       /* get min depth of BST */
int bst_node_level(BST* bst, Node* node);       /* get node's depth */
void bst_clear(BST* bst);                      /* clear all nodes from BST */

#endif
