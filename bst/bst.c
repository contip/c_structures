#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* internal helper functions */
Node* _create_node(int key);
BST* _create_bst();
Node* _left_child(Node* node);
bool _remove_helper(BST* bst, int key, bool recur);
int _max_depth_recur(Node* node);
int _min_depth_recur(Node* node);
void _trav_recur(Node* node, int order, int* visited, 
    int* visited_idx);


/*
 * Function:  bst_init
 * --------------------
 *  initializes a bst with given values and returns ptr to it
 *
 *  vals: (array of int) values with which to initialize the bst
 *  vals_size: (int) size of values array
 *
 *  returns: ptr to bst initialized with given values
 */
BST* bst_init(int* vals, int vals_size)
{
    BST* bst = _create_bst();
    int i;
    for (i = 0; i < vals_size; i++)
    {
        bst_add(bst, vals[i]);
    }
    return bst;
}


/*
 * Function:  bst_add
 * --------------------
 *  adds node to BST; becomes root node if BST was empty
 *  
 *  bst: (BST*) BST to which new node is to be added
 *  key: (int) value for key of node to add
 *
 *  returns: none
 */
void bst_add(BST* bst, int key)
{
    /* create the new node */
    Node* to_add = _create_node(key);
    if (bst->root == NULL)
    {
        /* if bst was empty, add new node as the root */
        bst->root = to_add;
        bst->count++;
    }
    else
    {
        /* otherwise, find appropriate spot in bst at which to add new node*/
        Node* curr_node = bst->root;
        Node* parent = curr_node;
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
 * Function:  bst_traverse
 * --------------------
 *  performs traversal of BST in specified order, returning ordered array
 *      representing the sequence of node visitation
 *  
 *  bst: (BST*) ptr to BST to traverse
 *  order: (int) 0 for in-order, 1 for pre-order, 2 for post-order
 *
 *  returns: ptr to array of ints containing keys of nodes in order visited
 */
int* bst_traverse(BST* bst, int order)
{
    int visited_size = bst->count, visited_idx = 0;
    int* visited = calloc(visited_size, sizeof(int));
    _trav_recur(bst->root, order, visited, &visited_idx);
    return visited;
}


/*
 * Function:  bst_find
 * --------------------
 *  checks to see if a node with given key exists in bst
 *  
 *  bst: (BST*) ptr to BST to search
 *  key: (int) key value to search for
 *
 *  returns: ptr to the node if it exists in BST, otherwise NULL
 */
Node* bst_find(BST* bst, int key)
{
    if (bst->count > 0)
    {
        Node* current_node = bst->root;
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
    }
    return NULL;
}


/*
 * Function:  bst_remove
 * --------------------
 *  removes node with given key value from BST if it exists in BST
 *  
 *  bst: (BST*) ptr to BST from which to remove specified node
 *  key: (int) key value of node to remove
 *
 *  returns: true if node w/ given key removed from BST, false otherwise
 */
bool bst_remove(BST* bst, int key)
{
    return _remove_helper(bst, key, false);
}


/*
 * Function:  bst_root_val
 * --------------------
 *  returns value of the root node of given bst
 *  assumes bst non-empty
 *  
 *  bst: (BST*) ptr to BST from which to get root node's key value
 *
 *  returns: integer representing BST root node's key value
 */
int bst_root_val(BST* bst)
{
    return bst->root->key;
}


/*
 * Function:  bst_max_depth
 * --------------------
 *  returns number of nodes along longest path from root to farthest leaf node
 *  
 *  bst: (BST*) ptr to BST
 *
 *  returns: the BST's max depth (integer)
 */
int bst_max_depth(BST* bst)
{
    Node* root_ptr = bst->root;
    return _max_depth_recur(root_ptr);
}


/*
 * Function:  bst_min_depth
 * --------------------
 *  returns number of nodes along shortest path from root to closest leaf node
 *  
 *  bst: (BST*) ptr to BST
 *
 *  returns: the BST's max depth (integer)
 */
int bst_min_depth(BST* bst)
{
    Node* root_ptr = bst->root;
    return _min_depth_recur(root_ptr);
}


/*
 * Function:  bst_node_level
 * --------------------
 *  returns level of given node in bst (root is considered level 1)
 *  
 *  bst: (BST*) ptr to BST
 *  node: (Node*) ptr to Node
 *
 *  returns: the node's level in the bst (integer), or NULL
 */
int bst_node_level(BST* bst, Node* node)
{
    int level = 1;
    while (node->parent != NULL)
    {
        node = node->parent;
        level++;
    }
    return level;
}


/*
 * Function:  bst_clear
 * --------------------
 *  deletes all nodes and frees their memory from input bst
 *  
 *  bst: (BST*) the bst to clear
 *
 *  returns: none
 */
void bst_clear(BST* bst)
{
    while (bst->count > 0)
    {
        bst_remove(bst, bst->root->key);
    }
    return;
}


/* ====helper functions follow==== */
/*
 * Function:  _create_node
 * --------------------
 *  creates a new Node with given key value, sets both children to NULL
 *  
 *  key: (int) value for key of node
 *
 *  returns: the created node
 */
Node* _create_node(int key)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;
    return new_node;
}


/*
 * Function:  _create_bst
 * --------------------
 *  creates new, empty BST
 *
 *  returns: ptr to the created empty BST
 */
BST* _create_bst()
{
    BST* bst = (BST*)malloc(sizeof(BST));
    bst->root = NULL;
    bst->count = 0;
    return bst;
}


/*
 * Function:  _trav_recur
 * --------------------
 *  helper function, recursively performs bst traversal
 *  
 *  node: (Node*) ptr to current node
 *  order: (int) order of traversal:
 *         0 for in-order, 1 for pre-order, 2 for post-order
 *  visited: (int *) ptr to array of ints representing traversal
 *  visited_idx: (&int) ptr to int storing current index of visited array
 *
 *  returns: none
 */
void _trav_recur(Node* node, int order, int* visited, 
    int* visited_idx)
{
    if (node == NULL)
    {
        return;
    }
    if (order == 0)
    {
        _trav_recur(node->left, order, visited, visited_idx);
        visited[*visited_idx] = node->key;
        *visited_idx = *visited_idx + 1;
        _trav_recur(node->right, order, visited, visited_idx);
    }
    else if (order == 1)
    {
        visited[*visited_idx] = node->key;
        *visited_idx = *visited_idx + 1;
        _trav_recur(node->left, order, visited, visited_idx);
        _trav_recur(node->right, order, visited, visited_idx);
    }
    else
    {
        _trav_recur(node->left, order, visited, visited_idx);
        _trav_recur(node->right, order, visited, visited_idx);
        visited[*visited_idx] = node->key;
        *visited_idx = *visited_idx + 1;
    }
    return;
}


/*
 * Function:  _left_child
 * --------------------
 *  helper function to identify the left-most child of the given BST node
 *  
 *  node: (Node*) node from which to initiate search
 *
 *  returns: pointer to input node's left-most child (if input node has
 *           no left children, returns pointer to input node itself)
 */
Node* _left_child(Node* node)
{
    if (node->left == NULL)
    {
        return node;
    }
    Node* next_node = node->left;
    while (next_node != NULL)
    {
        node = next_node;
        next_node = next_node->left;
    }
    return node;
}


/*
 * Function:  _remove_helper
 * --------------------
 *  helper function to remove specified node from BST 
 *  
 *  bst: (BST*) ptr to BST from which to remove specified node
 *  key: (int) key value of node to remove
 *  recur: (bool) if true, function assumes it is in a recursive call
 *      to 'delete' in-order successor, and will NOT decrement count
 *
 *  returns: true if node w/ given key removed from BST, false otherwise
 */
bool _remove_helper(BST* bst, int key, bool recur)
{
    /* initialize pointers to current node and its parent */
    Node* current = bst_find(bst, key);
    if (current == NULL)
    {
        return false;
    }
    Node* parent = current->parent;
    /* if node being removed has 0 children: set its parent to point to NULL
     * instead of it, and then free the node's memory */
    if (current->left == NULL && current->right == NULL)
    {
        if (current->parent == NULL)
        {
            free(current);
            bst->root = NULL;
            bst->count = 0;
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
        if (!recur)
        {
            bst->count--;
        }
        free(current);
    }
    /* if node being removed has 1 child, set its parent to point to that
        child and then free */
    else if (current->left && !current->right ||
        current->right && !current->left)
    {
        Node* child = (current->left) ? current->left : current->right;
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
        if (!recur)
        {
            bst->count--;
        }
        free(current);
    }
    /* if the node being removed has 2 children, use in-order successor */
    else
    {
        Node* successor = _left_child(current->right);
        int suc_val = successor->key;
        _remove_helper(bst, successor->key, true);  /* does the free */
        if (!recur)
        {
            bst->count--;
        }
        current->key = suc_val;
    }
    return true;
}


/*
 * Function:  _max_depth_recur
 * --------------------
 *  recursive helper function for bst_max_depth
 *  finds max distance from given node to farthest leaf node
 *  
 *  node: (Node*) ptr to node
 *
 *  returns: the max depth (integer)
 */
int _max_depth_recur(Node* node)
{
    if (node == NULL)
    {
        return 0;
    }
    /* get depths of left and right subtrees */
    int left = _max_depth_recur(node->left);
    int right = _max_depth_recur(node->right);
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
 * Function:  _min_depth_recur
 * --------------------
 *  recursive helper function for bst_min_depth
 *  finds min distance from given node to farthest leaf node
 *  
 *  node: (Node*) ptr to node
 *
 *  returns: the min depth (integer)
 */
int _min_depth_recur(Node* node)
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
        return _min_depth_recur(node->right) + 1;
    }
    if (node->right == NULL)
    {
        return _min_depth_recur(node->left) + 1;
    }
    /* if node has two children, recursively get min depth of L and R 
        subtrees and select the minimum */
    return (_min_depth_recur(node->left) > _min_depth_recur(node->right) ?
        _min_depth_recur(node->right) : _min_depth_recur(node->left)) + 1;
}
