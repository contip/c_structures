#include "sll.h"
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void sll_init_tests()
{
    /* test 1: initiaiilze ll with an array, verify values */
    int array_test[5] = { 15, 0, 1, 2, 7 };
    int array_test_size = 5;
    SLL* new_1 = sll_init(array_test, array_test_size);
    assert(new_1->head->val == 15);
    assert(new_1->tail->val == 7);
    assert(new_1->count == 5);
    assert(new_1->head->next->val == 0);
    assert(new_1->head->next->next->val == 1);
    assert(new_1->head->next->next->next->val == 2);
    assert(new_1->head->next->next->next->next->val == 7);

    /* test 2: initialize and verify empty ll */
    SLL* new_2 = sll_init(0, 0);
    assert(new_2->count == 0);
    assert(new_2->head == NULL && new_2->tail == NULL);

    /* free memory */
    sll_clear(new_1);
    sll_clear(new_2);
    free(new_1);
    free(new_2);
    return;
}

void sll_prepend_tests()
{
    /* test 1: initialize empty ll and build by adding values to front */
    SLL* prepend_1 = sll_init(0, 0);
    sll_prepend(prepend_1, 1);
    sll_prepend(prepend_1, 2);
    sll_prepend(prepend_1, 3);
    sll_prepend(prepend_1, 4);
    sll_prepend(prepend_1, 5);
    assert(prepend_1->head->val == 5);
    assert(prepend_1->tail->val == 1);
    assert(prepend_1->count == 5);

    /* test 2: initialize ll with array, then add to front */
    int array_test[7] = { 8, 6, 7, 5, 3, 0, 9 };
    int array_test_size = 7;
    SLL* prepend_2 = sll_init(array_test, array_test_size);
    sll_prepend(prepend_2, 1);
    assert(prepend_2->head->val == 1);
    assert(prepend_2->count == 8);
    sll_prepend(prepend_2, 5);
    assert(prepend_2->head->val == 5);
    assert(prepend_2->count == 9);

    /* free memory*/
    sll_clear(prepend_1);
    sll_clear(prepend_2);
    free(prepend_1);
    free(prepend_2);
    return;
}

void sll_append_tests()
{
    /* test 1: initialize empty ll and build by adding values to end */
    SLL* append_1 = sll_init(0, 0);
    sll_append(append_1, 1);
    sll_append(append_1, 2);
    sll_append(append_1, 3);
    sll_append(append_1, 4);
    sll_append(append_1, 5);
    assert(append_1->head->val == 1);
    assert(append_1->tail->val == 5);
    assert(append_1->count == 5);

    /* test 2: initialize ll with array, then add to end */
    int array_test[7] = { 8, 6, 7, 5, 3, 0, 9 };
    int array_test_size = 7;
    SLL* append_2 = sll_init(array_test, array_test_size);
    sll_append(append_2, -69);
    assert(append_2->tail->val == -69);
    assert(append_2->count == 8);
    sll_append(append_2, 1);
    sll_append(append_2, 2);
    sll_append(append_2, 3);
    sll_append(append_2, 4);
    sll_append(append_2, 5);
    assert(append_2->count == 13);
    assert(append_2->tail->val == 5);

    /* free memory */
    sll_clear(append_1);
    sll_clear(append_2);
    free(append_1);
    free(append_2);
    return;
}

void sll_to_array_tests()
{
    /* test 1: verify sll_to_array produces same array as original */
    int array_test[7] = { 8, 6, 7, 5, 3, 0, 9 };
    int array_test_size = 7;
    SLL* to_array_1 = sll_init(array_test, array_test_size);
    int* result = sll_to_array(to_array_1);
    assert(!memcmp(array_test, result, sizeof(array_test)));

    /* test 2: verify function works for linked list of size 1 */
    SLL* to_array_2 = sll_init(0, 0);
    sll_prepend(to_array_2, 69);
    int* result_2 = sll_to_array(to_array_2);
    assert(*result_2 == 69);

    /* free memory */
    sll_clear(to_array_1);
    sll_clear(to_array_2);
    free(to_array_1);
    free(to_array_2);
    free(result);
    free(result_2);
    return;
}

void sll_pop_end_tests()
{
    /* test 1: remove end until empty ll */
    int array_test[7] = { 8, 6, 7, 5, 3, 0, 9 };
    int array_test_size = 7;
    SLL* pop_end_1 = sll_init(array_test, array_test_size);
    assert(sll_pop_end(pop_end_1) == 9);
    assert(pop_end_1->count == 6);
    assert(pop_end_1->tail->val == 0);
    assert(sll_pop_end(pop_end_1) == 0);
    assert(pop_end_1->count == 5);
    assert(pop_end_1->tail->val == 3);
    assert(sll_pop_end(pop_end_1) == 3);
    assert(pop_end_1->count == 4);
    assert(pop_end_1->tail->val == 5);
    assert(sll_pop_end(pop_end_1) == 5);
    assert(sll_pop_end(pop_end_1) == 7);
    assert(sll_pop_end(pop_end_1) == 6);
    assert(pop_end_1->count == 1);
    assert(pop_end_1->head->val == pop_end_1->tail->val &&
            pop_end_1->head->val == 8);
    assert(sll_pop_end(pop_end_1) == 8);
    assert(pop_end_1->count == 0);
    assert(pop_end_1->head == NULL && pop_end_1->tail == NULL);

    /* free memory */
    free(pop_end_1);
    return;
}

void sll_pop_front_tests()
{
    /* test 1: remove front until empty ll */
    int array_test[9] = { 5, -1, 2, 6, 9, 3, 7, 8, 0 };
    int i, array_test_size = 9;
    SLL* pop_front_1 = sll_init(array_test, array_test_size);
    assert(sll_pop_front(pop_front_1) == 5);
    assert(pop_front_1->count == 8);
    assert(pop_front_1->head->val == -1);
    assert(sll_pop_front(pop_front_1) == -1);
    assert(pop_front_1->count == 7);
    assert(pop_front_1->head->val == 2);
    assert(sll_pop_front(pop_front_1) == 2);
    assert(pop_front_1->count == 6);
    assert(pop_front_1->head->val == 6);
    assert(sll_pop_front(pop_front_1) == 6);
    assert(sll_pop_front(pop_front_1) == 9);
    assert(sll_pop_front(pop_front_1) == 3);
    assert(sll_pop_front(pop_front_1) == 7);
    assert(sll_pop_front(pop_front_1) == 8);
    assert(pop_front_1->count == 1);
    assert(pop_front_1->head->val == pop_front_1->tail->val &&
            pop_front_1->head->val == 0);
    assert(sll_pop_front(pop_front_1) == 0);
    assert(pop_front_1->count == 0);
    assert(pop_front_1->head == NULL && pop_front_1->tail == NULL);

    /* free memory */
    free(pop_front_1);
    return;
}

void sll_contains_tests()
{
    /* test 1 */
    SLL* contains_1 = sll_init(0, 0);
    assert(sll_contains(contains_1, 69) == false);
    sll_append(contains_1, 1);
    assert(sll_contains(contains_1, 1) == true);
    sll_prepend(contains_1, 69);
    assert(sll_contains(contains_1, 0) == false);
    assert(sll_contains(contains_1, 68) == false);
    assert(sll_contains(contains_1, 69) == true);
    sll_prepend(contains_1, 3);
    assert(sll_contains(contains_1, 3) == true);

    /* free memory */
    sll_clear(contains_1);
    free(contains_1);
    return;
}

void sll_remove_first_tests()
{
    /* test 1 */
    int array_test[9] = { 5, -1, 2, 6, 9, 3, -1, 8, 0 };
    int array_test_size = 9;
    SLL* rem_first_1 = sll_init(array_test, array_test_size);
    assert(sll_remove_first(rem_first_1, 69) == false);
    assert(sll_remove_first(rem_first_1, -1) == true);
    assert(sll_contains(rem_first_1, -1) == true);
    assert(rem_first_1->head->val == 5);
    assert(rem_first_1->head->next->val == 2);
    assert(sll_remove_first(rem_first_1, -1) == true);
    assert(sll_remove_first(rem_first_1, -1) == false);
    assert(sll_contains(rem_first_1, -1) == false);
    assert(rem_first_1->tail->prev->prev->val == 3);

    /* free memory */
    sll_clear(rem_first_1);
    free(rem_first_1);
    return;
}

void sll_remove_index_tests()
{
    /* test 1 */
    int array_test[7] = { 8, 6, 7, 5, 3, 0, 9 };
    int array_test_size = 7;
    SLL* remove_index_1 = sll_init(array_test, array_test_size);
    assert(sll_remove_index(remove_index_1, 7) == false);
    assert(sll_remove_index(remove_index_1, 6) == true);
    assert(remove_index_1->tail->val == 0);
    assert(sll_remove_index(remove_index_1, 6) == false);
    assert(sll_remove_index(remove_index_1, 0) == true);
    assert(sll_remove_index(remove_index_1, 2) == true);
    /* current state of ll: { 6, 7, 3, 0 } */
    assert(remove_index_1->head->val == 6);
    assert(remove_index_1->count == 4);
    assert(sll_remove_index(remove_index_1, 4) == false);

    /* free memory */
    sll_clear(remove_index_1);
    free(remove_index_1);
    return;
}

void sll_clear_tests()
{
    /* test 1 */
    int array_test[7] = { 8, 6, 7, 5, 3, 0, 9 };
    int array_test_size = 7;
    SLL* clear_1 = sll_init(array_test, array_test_size);
    sll_clear(clear_1);
    assert(clear_1->count == 0);
    assert(clear_1->head == NULL);
    assert(clear_1->tail == NULL);

    /* test 2: attempting to clear an empty ll */
    SLL* clear_2 = sll_init(0, 0);
    sll_clear(clear_2);
    assert(clear_1->count == 0);
    assert(clear_1->head == NULL);
    assert(clear_1->tail == NULL);

    /* free memory */
    free(clear_1);
    free(clear_2);
    return;
}

void sll_splice_tests()
{
    /* test 1 */
    int array_test[7] = { 8, 6, 7, 5, 3, 0, 9 };
    int array_test_size = 7;
    SLL* splice_1 = sll_init(array_test, array_test_size);
    sll_splice(splice_1, 0, 69);
    assert(splice_1->head->val == 69);
    assert(splice_1->head->next->val == 8);
    assert(splice_1->count == 8);
    sll_splice(splice_1, 7, 69);
    assert(splice_1->tail->prev->val == 69);
    assert(splice_1->count == 9);
    assert(splice_1->tail->prev->next->val == 9);
    /* { 69, 8, 6, 7, 5, 3, 0, 69, 9 } */
    sll_splice(splice_1, 4, -69);
    assert(splice_1->head->next->next->next->next->val == -69);
    assert(splice_1->count == 10);

    /* free memory */
    sll_clear(splice_1);
    free(splice_1);
    return;
}

int main(void)
{
    sll_init_tests();
    printf("All sll_init tests pass!\n");
    sll_prepend_tests();
    printf("All sll_prepend tests pass!\n");
    sll_append_tests();
    printf("All sll_append tests pass!\n");
    sll_to_array_tests();
    printf("All sll_to_array tests pass!\n");
    sll_pop_end_tests();
    printf("All sll_pop_end tests pass!\n");
    sll_pop_front_tests();
    printf("All sll_pop_front tests pass!\n");
    sll_contains_tests();
    printf("All sll_contains tests pass!\n");
    sll_remove_first_tests();
    printf("All sll_remove_first tests pass!\n");
    sll_remove_index_tests();
    printf("All sll_remove_index tests pass!\n");
    sll_clear_tests();
    printf("All sll_clear tests pass!\n");
    sll_splice_tests();
    printf("All sll_splice tests pass!\n");
    return 0;
}
