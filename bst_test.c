#include "bst.h"
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

void add_node_tests()
{
    /*   Expected Tree:
     *                         15
     *                     0       20
     *                  -5   5  17    25
     */
    int test_1[7] = { 15, 0, -5, 5, 20, 25, 17 };
    int test_1_size = 7;
    struct BST* test_1_bst = bst_new(test_1, test_1_size);

    /* test 1: verify root node correctly set to 15 */
    assert(test_1[0] == bst_root_val(test_1_bst));

    /* test 2: test value of root's left child (0) */
    assert(test_1[1] == test_1_bst->root->left->key);

    /* test 3: test value of root's right child (20) */
    assert(test_1[4] == test_1_bst->root->right->key);

    /* test 4: test value of root's left left child (-5) */
    assert(test_1[2] == test_1_bst->root->left->left->key);

    /* test 5: test value of root's left child's right child (5) */
    assert(test_1[3] == test_1_bst->root->left->right->key);

    /* test 6: test value of root's right child's right child (25) */
    assert(test_1[5] == test_1_bst->root->right->right->key);

    /* test 7: test value of root's right child's left child (17) */
    assert(test_1[6] == test_1_bst->root->right->left->key);
    
    int i;
    for (i = 0; i < test_1_size; i++)
    {
        bst_remove(test_1_bst, test_1[i]);
    }
    free(test_1_bst);
    return;
}

void traversal_tests()
{

    /*   Expected Tree:
     *             7
     *         5       8
     *     1      6        9
     *   0   3
     *      2  4
     */
    int test_trav_1[10] = { 7 , 5 , 1 , 8 , 3 , 6 , 0 , 9 , 4 , 2 };
    int test_trav_1_size = 10;
    struct BST* test_trav_1_bst = bst_new(test_trav_1, test_trav_1_size);

    /* test 1: in order traversal of the test bst */
    int in_order_expected[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int i;
    int* in_order_experimental = bst_traverse(test_trav_1_bst, 0);
    for (i = 0; i < test_trav_1_size; i++)
    {
        assert(in_order_expected[i] == in_order_experimental[i]);
    }
    free(in_order_experimental);

    /* test 2: pre-order traversal */
    int pre_order_expected[10] = { 7, 5, 1, 0, 3, 2, 4, 6, 8, 9 };
    int* pre_order_experimental = bst_traverse(test_trav_1_bst, 1);
    for (i = 0; i < test_trav_1_size; i++)
    {
        assert(pre_order_expected[i] == pre_order_experimental[i]);
    }
    free(pre_order_experimental);

    /* test 3: post-order traversal */
    int post_order_expected[10] = { 0, 2, 4, 3, 1, 6, 5, 9, 8, 7 };
    int* post_order_experimental = bst_traverse(test_trav_1_bst, 2);
    for (i = 0; i < test_trav_1_size; i++)
    {
        assert(post_order_expected[i] == post_order_experimental[i]);
    }
    free(post_order_experimental);

    for (i = 0; i < test_trav_1_size; i++)
    {
        bst_remove(test_trav_1_bst, test_trav_1[i]);
    }
    free(test_trav_1_bst);

    /*   Expected Tree:
     *                         15
     *                     0       20
     *                  -5   5  17    25
     */
    int test_trav_2[7] = { 15, 0, -5, 5, 20, 25, 17 };
    int test_trav_2_size = 7;
    struct BST* test_trav_2_bst = bst_new(test_trav_2, test_trav_2_size);

    /* test 4: in-order traversal */
    int in_order_expected_2[7] = { -5, 0, 5, 15, 17, 20, 25 };
    int* in_order_experimental_2 = bst_traverse(test_trav_2_bst, 0);
    for (i = 0; i < test_trav_2_size; i++)
    {
        assert(in_order_expected_2[i] == in_order_experimental_2[i]);
    }
    free(in_order_experimental_2);

    /* test 5: pre-order traversal */
    int pre_order_expected_2[7] = { 15, 0, -5, 5, 20, 17, 25 };
    int* pre_order_experimental_2 = bst_traverse(test_trav_2_bst, 1);
    for (i = 0; i < test_trav_2_size; i++)
    {
        assert(pre_order_expected_2[i] == pre_order_experimental_2[i]);
    }
    free(pre_order_experimental_2);

    /* test 6: post-order traversal */
    int post_order_expected_2[7] = { -5, 5, 0, 17, 25, 20, 15 };
    int* post_order_experimental_2 = bst_traverse(test_trav_2_bst, 2);
    for (i = 0; i < test_trav_2_size; i++)
    {
        assert(post_order_expected_2[i] == post_order_experimental_2[i]);
    }
    free(post_order_experimental_2);

    for (i = 0; i < test_trav_2_size; i++)
    {
        bst_remove(test_trav_2_bst, test_trav_2[i]);
    }

    free(test_trav_2_bst);
    return;
}

void remove_tests()
{
    /* Starting Tree:
     *                     15
     *                 0       20
     *              -5   5  17    25
     */
    int test_rem[7] = { 15, 0, -5, 5, 20, 25, 17 };
    int test_rem_size = 7;
    struct BST* test_rem_bst = bst_new(test_rem, test_rem_size);

    /* test 1: remove root */
       /* Expected Tree:
        *                     17
        *                 0       20
        *              -5   5        25
        */
    bst_remove(test_rem_bst, 15);
    assert(bst_root_val(test_rem_bst) == 17);
    assert(test_rem_bst->root->right->key == 20);
    assert(test_rem_bst->root->left->key == 0);
    /* verify all values besides removed are still in tree */
    int i;
    for (i = 0; i < test_rem_size; i++)
    {
        if (test_rem[i] == 15)
        {
            continue;
        }
        else
        {
            /* find doesn't return boolean.. it returns a node or NULL */
            assert(bst_find(test_rem_bst, test_rem[i])->key == test_rem[i]);
        }
    }

    /* test 2: remove root again */
       /* Expected Tree:
        *                     20
        *                 0       25
        *              -5   5
        */
    bst_remove(test_rem_bst, 17);
    assert(bst_root_val(test_rem_bst) == 20);
    assert(test_rem_bst->root->right->key == 25);
    assert(test_rem_bst->root->left->key == 0);
    /* verify all values besides removed are still in tree */
    for (i = 0; i < test_rem_size; i++)
    {
        if (test_rem[i] == 15 || test_rem[i] == 17)
        {
            continue;
        }
        else
        {
            assert(bst_find(test_rem_bst, test_rem[i])->key == test_rem[i]);
        }
    }

    /* test 3: remove root yet again */
       /* Expected Tree:
        *                     25
        *                 0
        *              -5   5
        */
    bst_remove(test_rem_bst, 20);
    assert(bst_root_val(test_rem_bst) == 25);
    assert(test_rem_bst->root->right == NULL);
    assert(test_rem_bst->root->left->key == 0);
    /* verify all values besides removed are still in tree */
    for (i = 0; i < test_rem_size; i++)
    {
        if (test_rem[i] == 15 || test_rem[i] == 17 || test_rem[i] == 20)
        {
            continue;
        }
        else
        {
            assert(bst_find(test_rem_bst, test_rem[i])->key == test_rem[i]);
        }
    }

    /* test 4: remove key 5 */
       /* Expected Tree:
        *                     25
        *                 0
        *              -5
        */
    bst_remove(test_rem_bst, 5);
    assert(bst_root_val(test_rem_bst) == 25);
    assert(test_rem_bst->root->right == NULL);
    assert(test_rem_bst->root->left->key == 0);
    /* verify all values besides removed are still in tree */
    for (i = 0; i < test_rem_size; i++)
    {
        if (test_rem[i] == 15 || test_rem[i] == 17 || test_rem[i] == 20 ||
            test_rem[i] == 5)
        {
            continue;
        }
        else
        {
            assert(bst_find(test_rem_bst, test_rem[i])->key == test_rem[i]);
        }

        /* test 5: remove key 0 */
          /* Expected Tree:
           *                     25
           *                 -5
           */
        bst_remove(test_rem_bst, 0);
        assert(bst_root_val(test_rem_bst) == 25);
        assert(test_rem_bst->root->right == NULL);
        assert(test_rem_bst->root->left->key == -5);
        assert(test_rem_bst->root->left->right == NULL);
        assert(test_rem_bst->root->left->left == NULL);
        /* verify all values besides removed are still in tree */
        for (i = 0; i < test_rem_size; i++)
        {
            if (test_rem[i] == 15 || test_rem[i] == 17 || test_rem[i] == 20 ||
                test_rem[i] == 5 || test_rem[i] == 0)
            {
                continue;
            }
            else
            {
                assert(bst_find(test_rem_bst, test_rem[i])->key == test_rem[i]);
            }
        }
    }

    for (i = 0; i < test_rem_size; i++)
    {
        bst_remove(test_rem_bst, test_rem[i]);
    }
    free(test_rem_bst);

       /* Starting Tree:
        *                     15
        *                 0       20
        *              -5   5  17    25
        *                        19
        */
    int test_rem_2[8] = { 15, 0, -5, 5, 20, 25, 17, 19 };
    int test_rem_2_size = 8;
    struct BST* test_rem_2_bst = bst_new(test_rem_2, test_rem_2_size);

    /* test 6: remove root */
       /* Expected Tree:
        *                     17
        *                 0       20
        *              -5   5  19    25
        *
        */
    bst_remove(test_rem_2_bst, 15);
    assert(bst_root_val(test_rem_2_bst) == 17);
    assert(test_rem_2_bst->root->right->key == 20);
    assert(test_rem_2_bst->root->right->left->key == 19);
    /* verify all values besides removed are still in tree */
    for (i = 0; i < test_rem_2_size; i++)
    {
        if (test_rem_2[i] == 15)
        {
            continue;
        }
        else
        {
            assert(bst_find(test_rem_2_bst, test_rem_2[i])->key == test_rem_2[i]);
        }
    }

    /* test 7: again remove root */
       /* Expected Tree:
        *                     19
        *                 0       20
        *              -5   5        25
        *
        */
    bst_remove(test_rem_2_bst, 17);
    assert(bst_root_val(test_rem_2_bst) == 19);
    assert(test_rem_2_bst->root->right->key == 20);
    assert(test_rem_2_bst->root->right->right->key == 25);
    assert(test_rem_2_bst->root->right->left == NULL);
    assert(test_rem_2_bst->root->left->right->key == 5);
    /* verify all values besides removed are still in tree */
    for (i = 0; i < test_rem_2_size; i++)
    {
        if (test_rem_2[i] == 15 || test_rem_2[i] == 17)
        {
            continue;
        }
        else
        {
            assert(bst_find(test_rem_2_bst, test_rem_2[i])->key == test_rem_2[i]);
        }
    }

    /* test 8: again remove root */
       /* Expected Tree:
        *                     20
        *                 0       25
        *              -5   5
        *
        */
    bst_remove(test_rem_2_bst, 19);
    assert(bst_root_val(test_rem_2_bst) == 20);
    assert(test_rem_2_bst->root->right->key == 25);
    assert(test_rem_2_bst->root->right->right == NULL);
    assert(test_rem_2_bst->root->right->left == NULL);
    assert(test_rem_2_bst->root->left->key == 0);
    /* verify all values besides removed are still in tree */
    for (i = 0; i < test_rem_2_size; i++)
    {
        if (test_rem_2[i] == 15 || test_rem_2[i] == 17 || test_rem_2[i] == 19)
        {
            continue;
        }
        else
        {
            assert(bst_find(test_rem_2_bst, test_rem_2[i])->key == test_rem_2[i]);
        }
    }

    /* test 9: again remove root */
       /* Expected Tree:
        *                     25
        *                 0
        *              -5   5
        *
        */
    bst_remove(test_rem_2_bst, 20);
    assert(bst_root_val(test_rem_2_bst) == 25);
    assert(test_rem_2_bst->root->right == NULL);
    assert(test_rem_2_bst->root->left->right->key == 5);
    assert(test_rem_2_bst->root->left->left->key == -5);
    /* verify all values besides removed are still in tree */
    for (i = 0; i < test_rem_2_size; i++)
    {
        if (test_rem_2[i] == 15 || test_rem_2[i] == 17 || test_rem_2[i] == 19
            || test_rem_2[i] == 20)
        {
            continue;
        }
        else
        {
            assert(bst_find(test_rem_2_bst, test_rem_2[i])->key == test_rem_2[i]);
        }
    }

    /* test 10: again remove root */
       /* Expected Tree:
        *                 0
        *              -5   5
        */
    bst_remove(test_rem_2_bst, 25);
    assert(bst_root_val(test_rem_2_bst) == 0);
    assert(test_rem_2_bst->root->right->key == 5);
    assert(test_rem_2_bst->root->left->key == -5);
    assert(test_rem_2_bst->root->left->left == NULL);
    /* verify all values besides removed are still in tree */
    for (i = 0; i < test_rem_2_size; i++)
    {
        if (test_rem_2[i] == 15 || test_rem_2[i] == 17 || test_rem_2[i] == 19
            || test_rem_2[i] == 20 || test_rem_2[i] == 25)
        {
            continue;
        }
        else
        {
            assert(bst_find(test_rem_2_bst, test_rem_2[i])->key == test_rem_2[i]);
        }
    }

    /* test 11: again remove root */
       /* Expected Tree:
        *                 5
        *              -5
        */
    bst_remove(test_rem_2_bst, 0);
    assert(bst_root_val(test_rem_2_bst) == 5);
    assert(test_rem_2_bst->root->right == NULL);
    assert(test_rem_2_bst->root->left->key == -5);
    assert(test_rem_2_bst->root->left->left == NULL);
    /* verify all values besides removed are still in tree */
    for (i = 0; i < test_rem_2_size; i++)
    {
        if (test_rem_2[i] == 15 || test_rem_2[i] == 17 || test_rem_2[i] == 19
            || test_rem_2[i] == 20 || test_rem_2[i] == 25 || 
            test_rem_2[i] == 0)
        {
            continue;
        }
        else
        {
            assert(bst_find(test_rem_2_bst, test_rem_2[i])->key == test_rem_2[i]);
        }
    }

    /* test 12: again remove root */
       /* Expected Tree:
        *              -5
        */
    bst_remove(test_rem_2_bst, 5);
    assert(bst_root_val(test_rem_2_bst) == -5);
    assert(test_rem_2_bst->root->right == NULL);
    assert(test_rem_2_bst->root->left == NULL);
    /* verify all values besides removed are still in tree */
    for (i = 0; i < test_rem_2_size; i++)
    {
        if (test_rem_2[i] == 15 || test_rem_2[i] == 17 || test_rem_2[i] == 19
            || test_rem_2[i] == 20 || test_rem_2[i] == 25 || 
            test_rem_2[i] == 0 || test_rem_2[i] == 5)
        {
            continue;
        }
        else
        {
            assert(bst_find(test_rem_2_bst, test_rem_2[i])->key == test_rem_2[i]);
        }
    }
    for (i = 0; i < test_rem_2_size; i++)
    {
        bst_remove(test_rem_2_bst, test_rem_2[i]);
    }
    free(test_rem_2_bst);
}

void max_depth_tests()
{
    /* test 1 */
    /* tree is: 
     *                 1
	 *  		          3
	 *  		             4
	 *  				        69
	 *  			         10     
     *
     *  depth of 5
     */
    int test_max_depth[5] = { 1, 3, 4, 69, 10 };
    int i, test_max_depth_size = 5;
    struct BST* test_max_depth_bst = bst_new(test_max_depth,
        test_max_depth_size);
    assert(bst_max_depth(test_max_depth_bst) == 5);

    for (i = 0; i < test_max_depth_size; i++)
    {
        bst_remove(test_max_depth_bst, test_max_depth[i]);
    }
    free(test_max_depth_bst);

    /* test 2 */
    /* tree is:
                3
                 \
                  9
                /  \
               7   20
                  /
                15

    *  depth of 4
     */
    int test_max_depth_2[5] = { 3, 9, 20, 15, 7 };
    int test_max_depth_2_size = 5;
    struct BST* test_max_depth_2_bst = bst_new(test_max_depth_2,
        test_max_depth_2_size);
    assert(bst_max_depth(test_max_depth_2_bst) == 4);
    for (i = 0; i < test_max_depth_2_size; i++)
    {
        bst_remove(test_max_depth_2_bst, test_max_depth_2[i]);
    }
    free(test_max_depth_2_bst);

     /* test 3 */
    /* tree is:
     *            3
     *        1       5
     *              4   12
     *  depth of 3
     */
    int test_max_depth_3[5] = { 3, 5, 1, 12, 4 };
    int test_max_depth_3_size = 5;
    struct BST* test_max_depth_3_bst = bst_new(test_max_depth_3,
        test_max_depth_3_size);
    assert(bst_max_depth(test_max_depth_3_bst) == 3);
    for (i = 0; i < test_max_depth_3_size; i++)
    {
        bst_remove(test_max_depth_3_bst, test_max_depth_3[i]);
    }
    free(test_max_depth_3_bst);
}


void min_depth_tests()
{
    /* test 1 */
    /* tree is: 
     *                 1
	 *  		          3
	 *  		             4
	 *  				        69
	 *  			         10     
     *
     *  depth of 5
     */
    int test_min_depth[5] = { 1, 3, 4, 69, 10 };
    int i, test_min_depth_size = 5;
    struct BST* test_min_depth_bst = bst_new(test_min_depth,
        test_min_depth_size);
    assert(bst_min_depth(test_min_depth_bst) == 5);
    for (i = 0; i < test_min_depth_size; i++)
    {
        bst_remove(test_min_depth_bst, test_min_depth[i]);
    }
    free(test_min_depth_bst);

    /* test 2 */
    /* tree is:
                3
                 \
                  9
                /  \
               7   20
                  /
                15

    *  depth of 3
     */
    int test_min_depth_2[5] = { 3, 9, 20, 15, 7 };
    int test_min_depth_2_size = 5;
    struct BST* test_min_depth_2_bst = bst_new(test_min_depth_2,
        test_min_depth_2_size);
    assert(bst_min_depth(test_min_depth_2_bst) == 3);
    for (i = 0; i < test_min_depth_2_size; i++)
    {
        bst_remove(test_min_depth_2_bst, test_min_depth_2[i]);
    }
    free(test_min_depth_2_bst);

     /* test 3 */
    /* tree is:
     *            3
     *        1       5
     *              4   12
     *  depth of 2
     */
    int test_min_depth_3[5] = { 3, 5, 1, 12, 4 };
    int test_min_depth_3_size = 5;
    struct BST* test_min_depth_3_bst = bst_new(test_min_depth_3,
        test_min_depth_3_size);
    assert(bst_min_depth(test_min_depth_3_bst) == 2);
    for (i = 0; i < test_min_depth_3_size; i++)
    {
        bst_remove(test_min_depth_3_bst, test_min_depth_3[i]);
    }
    free(test_min_depth_3_bst);
}
int main(void)
{

    add_node_tests();
    traversal_tests();
    remove_tests();
    max_depth_tests();
    min_depth_tests();
    printf("All tests completed successfully!\n");
    return 0;
}
