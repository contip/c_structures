#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "bst.h"

/*
 * bst principle: any element's key is greater than or equal to all the keys
 * in the node's left subtree, and less than those in it's right subtree
 */

/*
 * Function:  create_node
 * --------------------
 *  creates a new Node with given key value, sets both children ptr to NULL
 *  
 *  key: (int) value for key of node
 *
 *  returns: the created node
 */
struct Node* create_node(int key)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;
    return new_node;
}


/*
 * Function:  create_bst
 * --------------------
 *  creates new, empty BST
 *
 *  returns: ptr to the created empty BST
 */
struct BST* create_bst()
{
    struct BST* bst = (struct BST*)malloc(sizeof(struct BST));
    bst->root = NULL;
    bst->count = 0;
    return bst;
}


/*
 * Function:  bst_add
 * --------------------
 *  adds node to BST; becomes root node if BST was empty
 *  
 *  bst: (struct BST*) BST to which new node is to be added
 *  key: (int) value for key of node to add
 *
 *  returns: none
 */
void bst_add(struct BST* bst, int key)
{
    /* create the new node */
    struct Node* to_add = create_node(key);
    if (bst->root == NULL)
    {
        /* if bst was empty, add new node as the root */
        bst->root = to_add;
        bst->count++;
    }
    else
    {
        /* otherwise, find appropriate spot in bst at which to add new node*/
        struct Node* curr_node = bst->root;
        struct Node* parent = curr_node;
        while (curr_node != NULL)
        {
            parent = curr_node;
            if (key < curr_node->key)
            {
                curr_node = curr_node->left;
            }
            else
            {
                curr_node = curr_node->right;
            }
        }
        /* parent is the node to which to add the new node */
        if (key < parent->key)
        {
            parent->left = to_add;
        }
        else
        {
            parent->right = to_add;
        }
        to_add->parent = parent;
        bst->count++;
    }
    return;
}


/*
 * Function:  bst_new
 * --------------------
 *  initializes a bst with given values anad returns ptr to it
 *
 *  vals: (array of int) values with which to initialize the bst
 *  vals_size: (int) size of values array
 *
 *  returns: ptr to bst initialized with given values
 */
struct BST* bst_new(int* vals, int vals_size)
{
    struct BST* bst = create_bst();
    int i;
    for (i = 0; i < vals_size; i++)
    {
        bst_add(bst, vals[i]);
    }
    return bst;
}


/*
 * Function:  trav_recur
 * --------------------
 *  helper function, recursively performs bst traversal
 *  
 *  node: (struct Node*) ptr to current node
 *  order: (int) order of traversal:
 *         0 for in-order, 1 for pre-order, 2 for post-order
 *  visited: (int *) ptr to array of ints representing traversal
 *  visited_idx: (&int) ptr to int storing current index of visited array
 *
 *  returns: none
 */
void trav_recur(struct Node* node, int order, int* visited, 
    int* visited_idx)
{
    if (node == NULL)
    {
        return;
    }
    if (order == 0)
    {
        trav_recur(node->left, order, visited, visited_idx);
        visited[*visited_idx] = node->key;
        *visited_idx = *visited_idx + 1;
        trav_recur(node->right, order, visited, visited_idx);
    }
    else if (order == 1)
    {
        visited[*visited_idx] = node->key;
        *visited_idx = *visited_idx + 1;
        trav_recur(node->left, order, visited, visited_idx);
        trav_recur(node->right, order, visited, visited_idx);
    }
    else
    {
        trav_recur(node->left, order, visited, visited_idx);
        trav_recur(node->right, order, visited, visited_idx);
        visited[*visited_idx] = node->key;
        *visited_idx = *visited_idx + 1;
    }
    return;
}


/*
 * Function:  bst_traverse
 * --------------------
 *  performs traversal of BST in specified order, returning ordered array
 *      of the sequence of node visitation
 *  
 *  bst: (struct BST*) ptr to BST to traverse
 *  order: (int) 0 for in-order, 1 for pre-order, 2 for post-order
 *
 *  returns: array of ints containing keys of nodes in order visited
 */
int* bst_traverse(struct BST* bst, int order)
{
    int visited_size = bst->count, visited_idx = 0;
    int* visited = calloc(visited_size, sizeof(int));
    trav_recur(bst->root, order, visited, &visited_idx);
    return visited;
}


/*
 * Function:  bst_find
 * --------------------
 *  checks to see if a node with given key exists in bst
 *  
 *  bst: (struct BST*) ptr to BST to search
 *  key: (int) key value to search for
 *
 *  returns: ptr to the node if it exists in BST, otherwise NULL
 */
struct Node* bst_find(struct BST* bst, int key)
{
    struct Node* current_node = bst->root;
    while (current_node != NULL)
    {
        if (key == current_node->key)
        {
            return current_node;
        }
        else
        {
            if (key < current_node->key)
            {
                current_node = current_node->left;
            }
            else
            {
                current_node = current_node->right;
            }
        }
    }
    return NULL;
}


/*
 * Function:  left_child
 * --------------------
 *  helper function to identify the left-most child of the given BST node
 *  
 *  node: (struct Node*) node from which to initiate search
 *
 *  returns: pointer to input node's left-most child (if input node has
 *           no left children, returns pointer to input node itself)
 */
struct Node* left_child(struct Node* node)
{
    if (node->left == NULL)
    {
        return node;
    }
    struct Node* next_node = node->left;
    while (next_node != NULL)
    {
        node = next_node;
        next_node = next_node->left;
    }
    return node;
}


/*
 * Function:  bst_remove
 * --------------------
 *  removes node with given key value from BST and returns true if
 *  successful, otherwise false
 *  
 *  bst: (struct BST*) ptr to BST from which to remove specified node
 *  key: (int) key value of node to remove
 *
 *  returns: true if node w/ given key removed from BST, false otherwise
 */
bool bst_remove(struct BST* bst, int key)
{
    /* initialize pointers to current node and its parent */
    struct Node* current = bst_find(bst, key);
    if (current == NULL)
    {
        return false;
    }
    struct Node* parent = current->parent;
    /* if node being removed has 0 children: set its parent to point to NULL
     * instead of it, and then free the node's memory */
    /* this is the only case in which we could be freeing entire tree */
    if (current->left == NULL && current->right == NULL)
    {
        if (current->parent == NULL)
        {
            free(current);
            return true;
        }
        if (key < parent->key)
        {
            parent->left = NULL;
        }
        else
        {
            parent->right = NULL;
        }
        bst->count--;
        free(current);
    }

    /* if node being removed has 1 child, set its parent to point to that
        child and then free */
    else if (current->left && !current->right ||
        current->right && !current->left)
    {
        /* get the child node */
        struct Node* child = (current->left) ? current->left : current->right;
        if (current != bst->root)
        {
            if (current == parent->left)
            {
                parent->left = child;
            }
            else
            {
                parent->right = child;
            }
            child->parent = parent;
        }
        else 
        {
            bst->root = child;
            child->parent = NULL;
        }
        bst->count--;
        free(current);
    }

    /* if the node being removed has 2 children, use in-order successor */
    else
    {
        struct Node* successor = left_child(current->right);
        int suc_val = successor->key;
        bst_remove(bst, successor->key);  /* does the free */
        bst->count--;
        current->key = suc_val;
    }
    return true;
}


/*
 * Function:  bst_root_val
 * --------------------
 *  returns value of the root node of given bst
 *      assumes bst non-empty
 *  
 *  bst: (struct BST*) ptr to BST from which to get root node's key value
 *
 *  returns: integer representing BST root node's key value
 */
int bst_root_val(struct BST* bst)
{
    return bst->root->key;
}


/*
 * Function:  max_depth_recur
 * --------------------
 *  recursive helper function for bst_max_depth
 *  finds max distance from given node to farthest leaf node
 *  
 *  node: (struct Node*) ptr to node
 *
 *  returns: the max depth (integer)
 */
int max_depth_recur(struct Node* node)
{
    if (node == NULL)
    {
        return 0;
    }
    /* get depths of left and right subtrees */
    int left = max_depth_recur(node->left);
    int right = max_depth_recur(node->right);
    /* compare left and right subtree depths, return greater */
    if (left > right)
    {
        return left + 1;
    }
    else
    {
        return right + 1;
    }
}


/*
 * Function:  bst_max_depth
 * --------------------
 *  returns number of nodes along longest path from root to farthest leaf node
 *  
 *  bst: (struct BST*) ptr to BST
 *
 *  returns: the BST's max depth (integer)
 */
int bst_max_depth(struct BST* bst)
{
    struct Node* root_ptr = bst->root;
    return max_depth_recur(root_ptr);
}


/*
 * Function:  min_depth_recur
 * --------------------
 *  recursive helper function for bst_min_depth
 *  finds min distance from given node to farthest leaf node
 *  
 *  node: (struct Node*) ptr to node
 *
 *  returns: the min depth (integer)
 */
int min_depth_recur(struct Node* node)
{
    /* return 0 if node is only node in bst */
    if (node == NULL)
    {
        return 0;
    }
    /* increment at leaf nodes */
    if (node->left == NULL && node->right == NULL)
    {
        return 1;
    }
    /* if node only has one child, get min depth of that child */
    if (node->left == NULL)
    {
        return min_depth_recur(node->right) + 1;
    }
    if (node->right == NULL)
    {
        return min_depth_recur(node->left) + 1;
    }
    /* if node has two children, recursively get min depth of L and R 
        subtrees and select the minimum */
    return (min_depth_recur(node->left) > min_depth_recur(node->right) ?
        min_depth_recur(node->right) : min_depth_recur(node->left)) + 1;

}


/*
 * Function:  bst_min_depth
 * --------------------
 *  returns number of nodes along shortest path from root to farthest leaf node
 *  
 *  bst: (struct BST*) ptr to BST
 *
 *  returns: the BST's max depth (integer)
 */
int bst_min_depth(struct BST* bst)
{
    struct Node* root_ptr = bst->root;
    return min_depth_recur(root_ptr);
}


/*
 * Function:  bst_node_level
 * --------------------
 *  returns level of given node in bst (root is considered level 1)
 *  
 *  bst: (struct BST*) ptr to BST
 *  node: (struct Node*) ptr to Node
 *
 *  returns: the node's level in the bst (integer), or NULL
 */
int bst_node_level(struct BST* bst, struct Node* node)
{
    int level = 1;
    while (node->parent != NULL)
    {
        node = node->parent;
        level++;
    }
    return level;
}
