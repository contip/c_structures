#include "bst.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

void add_tests()
{
    /*   Expected Tree:
     *                         15
     *                     0       20
     *                  -5   5  17    25
     */
    int test_1[7] = { 15, 0, -5, 5, 20, 25, 17 };
    int i, test_1_size = 7;
    BST* test_1_bst = bst_init(NULL, 0);
    for (i = 0; i < test_1_size; i++)
    {
        bst_add(test_1_bst, test_1[i]);

    }

    assert(test_1[0] == bst_root_val(test_1_bst));
    assert(test_1[1] == test_1_bst->root->left->key);
    assert(test_1[4] == test_1_bst->root->right->key);
    assert(test_1[2] == test_1_bst->root->left->left->key);
    assert(test_1[3] == test_1_bst->root->left->right->key);
    assert(test_1[5] == test_1_bst->root->right->right->key);
    assert(test_1[6] == test_1_bst->root->right->left->key);
    
    /* free memory */
    bst_clear(test_1_bst);
    free(test_1_bst);
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
    BST* test_trav_1_bst = bst_init(test_trav_1, test_trav_1_size);

    /* test 1: in order traversal */
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

    
    /*   Expected Tree:
     *                         15
     *                     0       20
     *                  -5   5  17    25
     */
    int test_trav_2[7] = { 15, 0, -5, 5, 20, 25, 17 };
    int test_trav_2_size = 7;
    BST* test_trav_2_bst = bst_init(test_trav_2, test_trav_2_size);

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

    /* free memory */
    bst_clear(test_trav_1_bst);
    bst_clear(test_trav_2_bst);
    free(test_trav_1_bst);
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
    BST* test_rem_bst = bst_init(test_rem, test_rem_size);

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
            assert(bst_find(test_rem_bst, test_rem[i])->key == test_rem[i]);
        }
    }

    /* test 2: remove root */
       /* Expected Tree:
        *                     20
        *                 0       25
        *              -5   5
        */
    bst_remove(test_rem_bst, 17);
    assert(bst_root_val(test_rem_bst) == 20);
    assert(test_rem_bst->root->right->key == 25);
    assert(test_rem_bst->root->left->key == 0);

    /* test 3: remove root */
       /* Expected Tree:
        *                     25
        *                 0
        *              -5   5
        */
    bst_remove(test_rem_bst, 20);
    assert(bst_root_val(test_rem_bst) == 25);
    assert(test_rem_bst->root->right == NULL);
    assert(test_rem_bst->root->left->key == 0);

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


       /* Starting Tree:
        *                     15
        *                 0       20
        *              -5   5  17    25
        *                        19
        */
    int test_rem_2[8] = { 15, 0, -5, 5, 20, 25, 17, 19 };
    int test_rem_2_size = 8;
    BST* test_rem_2_bst = bst_init(test_rem_2, test_rem_2_size);

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

    /* test 12: again remove root */
       /* Expected Tree:
        *              -5
        */
    bst_remove(test_rem_2_bst, 5);
    assert(bst_root_val(test_rem_2_bst) == -5);
    assert(test_rem_2_bst->root->right == NULL);
    assert(test_rem_2_bst->root->left == NULL);

    /* free memory */
    bst_clear(test_rem_bst);
    bst_clear(test_rem_2_bst);
    free(test_rem_bst);
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
    BST* test_max_depth_bst = bst_init(test_max_depth,
        test_max_depth_size);
    assert(bst_max_depth(test_max_depth_bst) == 5);

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
    BST* test_max_depth_2_bst = bst_init(test_max_depth_2,
        test_max_depth_2_size);
    assert(bst_max_depth(test_max_depth_2_bst) == 4);

     /* test 3 */
    /* tree is:
     *            3
     *        1       5
     *              4   12
     *  depth of 3
     */
    int test_max_depth_3[5] = { 3, 5, 1, 12, 4 };
    int test_max_depth_3_size = 5;
    BST* test_max_depth_3_bst = bst_init(test_max_depth_3,
        test_max_depth_3_size);
    assert(bst_max_depth(test_max_depth_3_bst) == 3);

    /* free memory */
    bst_clear(test_max_depth_bst);
    bst_clear(test_max_depth_2_bst);
    bst_clear(test_max_depth_3_bst);
    free(test_max_depth_bst);
    free(test_max_depth_2_bst);
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
    BST* test_min_depth_bst = bst_init(test_min_depth,
        test_min_depth_size);
    assert(bst_min_depth(test_min_depth_bst) == 5);

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
    BST* test_min_depth_2_bst = bst_init(test_min_depth_2,
        test_min_depth_2_size);
    assert(bst_min_depth(test_min_depth_2_bst) == 3);

     /* test 3 */
    /* tree is:
     *            3
     *        1       5
     *              4   12
     *  depth of 2
     */
    int test_min_depth_3[5] = { 3, 5, 1, 12, 4 };
    int test_min_depth_3_size = 5;
    BST* test_min_depth_3_bst = bst_init(test_min_depth_3,
        test_min_depth_3_size);
    assert(bst_min_depth(test_min_depth_3_bst) == 2);

    /* free memory */
    bst_clear(test_min_depth_bst);
    bst_clear(test_min_depth_2_bst);
    bst_clear(test_min_depth_3_bst);
    free(test_min_depth_bst);
    free(test_min_depth_2_bst);
    free(test_min_depth_3_bst);
}

void node_level_tests()
{
    /* test 1 */
    /* tree is:
     *           3
     *            \
     *             9
     *           /  \
     *          7   20
     *             /
     *           15
     */

    int level_array_1[5] = { 3, 9, 20, 15, 7 };
    int level_size_1 = 5;
    BST* level_bst_1 = bst_init(level_array_1,
        level_size_1);
    assert(bst_node_level(level_bst_1, level_bst_1->root) == 1);
    assert(bst_node_level(level_bst_1, level_bst_1->root->right) == 2);
    assert(bst_node_level(level_bst_1, level_bst_1->root->right->left) == 3);
    assert(bst_node_level(level_bst_1, level_bst_1->root->right->right) == 3);
    assert(bst_node_level(level_bst_1, level_bst_1->root->right->right->left)
            == 4);

    bst_clear(level_bst_1);
    free(level_bst_1);

}

void clear_tests()
{
    /* test 1 */
    /* tree is:
     *            3
     *        1       5
     *              4   12
     *  depth of 2
     */
    int clear_array_1[5] = { 3, 5, 1, 12, 4 };
    int clear_size_1 = 5;
    BST* clear_bst_1 = bst_init(clear_array_1,
        clear_size_1);
    assert(clear_bst_1->count == 5);
    bst_clear(clear_bst_1);
    assert(clear_bst_1->count == 0);
    assert(clear_bst_1->root == NULL);
    free(clear_bst_1);
}

int main(void)
{
    add_tests();
    printf("All bst_add tests completed successfully!\n");
    traversal_tests();
    printf("All bst_traverse tests completed successfully!\n");
    remove_tests();
    printf("All bst_remove tests completed successfully!\n");
    max_depth_tests();
    printf("All bst_max_depth tests completed successfully!\n");
    min_depth_tests();
    printf("All bst_min_depth tests completed successfully!\n");
    node_level_tests();
    printf("All bst_node_level tests completed successfully!\n");
    clear_tests();
    printf("All bst_clear tests completed successfully!\n");
    return 0;
}
