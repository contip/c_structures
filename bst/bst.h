#ifndef BST_H_  /* guard */
#define BST_H_
#include <stdbool.h>

/* Node and BST structure definitions */
struct Node
{
    int key;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
};

struct BST
{
    struct Node* root;
    int count;
};

/* binary search tree functions provided */
struct BST* bst_init(int* vals, int vals_size); /* create new BST from array */
void bst_add(struct BST* bst, int key);      /* add node w/ given val to BST */
int* bst_traverse(struct BST* bst, int order);               /* traverse BST */
struct Node* bst_find(struct BST* bst, int key);       /* search BST for val */
bool bst_remove(struct BST* bst, int key);    /* remove node w/ matching val */
int bst_root_val(struct BST* bst);                 /* get value of root node */
int bst_max_depth(struct BST* bst);                  /* get max depth of BST */
int bst_min_depth(struct BST* bst);                  /* get min depth of BST */
int bst_node_level(struct BST* bst, struct Node* node);  /* get node's depth */
void bst_clear(struct BST* bst);                 /* clear all nodes from BST */

#endif
