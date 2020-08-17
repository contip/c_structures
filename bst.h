#ifndef BST_H_  /* guard */
#define BST_H_
#include <stdbool.h>

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


struct BST* bst_new(int* vals[], int vals_size);
void bst_add(struct BST* bst, int key);
int* bst_traverse(struct BST* bst, int order);
struct Node* bst_find(struct BST* bst, int key);
bool bst_remove(struct BST* bst, int key);
int bst_root_val(struct BST* bst);

#endif

