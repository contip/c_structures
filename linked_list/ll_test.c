#include "ll.h"
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


void ll_new_tests()
{
    /* test 1: initiaiilze ll with an array, verify values */
    int array_test[5] = { 15, 0, 1, 2, 7 };
    int array_test_size = 5;
    struct LL* new_1 = ll_new(array_test, array_test_size);
    assert(new_1->head->val == 15);
    assert(new_1->tail->val == 7);
    assert(new_1->count == 5);
    assert(new_1->head->next->val == 0);
    assert(new_1->head->next->next->val == 1);
    assert(new_1->head->next->next->next->val == 2);
    assert(new_1->head->next->next->next->next->val == 7);

    /* test 2: initialize and verify empty ll */
    struct LL* new_2 = ll_new(0, 0);
    assert(new_2->count == 0);
    assert(new_2->head == NULL && new_2->tail == NULL);

    /* free memory */
    ll_clear(new_1);
    ll_clear(new_2);
    free(new_1);
    free(new_2);
    return;
}

void ll_add_front_tests()
{
    /* test 1: initialize empty ll and build by adding values to front */
    struct LL* add_front_1 = ll_new(0, 0);
    ll_add_front(add_front_1, 1);
    ll_add_front(add_front_1, 2);
    ll_add_front(add_front_1, 3);
    ll_add_front(add_front_1, 4);
    ll_add_front(add_front_1, 5);
    assert(add_front_1->head->val == 5);
    assert(add_front_1->tail->val == 1);
    assert(add_front_1->count == 5);

    /* test 2: initialize ll with array, then add to front */
    int array_test[7] = { 8, 6, 7, 5, 3, 0, 9 };
    int array_test_size = 7;
    struct LL* add_front_2 = ll_new(array_test, array_test_size);
    ll_add_front(add_front_2, 1);
    assert(add_front_2->head->val == 1);
    assert(add_front_2->count == 8);
    ll_add_front(add_front_2, 5);
    assert(add_front_2->head->val == 5);
    assert(add_front_2->count == 9);

    /* free memory*/
    ll_clear(add_front_1);
    ll_clear(add_front_2);
    free(add_front_1);
    free(add_front_2);
    return;
}

void ll_add_end_tests()
{
    /* test 1: initialize empty ll and build by adding values to end */
    struct LL* add_end_1 = ll_new(0, 0);
    ll_add_end(add_end_1, 1);
    ll_add_end(add_end_1, 2);
    ll_add_end(add_end_1, 3);
    ll_add_end(add_end_1, 4);
    ll_add_end(add_end_1, 5);
    assert(add_end_1->head->val == 1);
    assert(add_end_1->tail->val == 5);
    assert(add_end_1->count == 5);

    /* test 2: initialize ll with array, then add to end */
    int array_test[7] = { 8, 6, 7, 5, 3, 0, 9 };
    int array_test_size = 7;
    struct LL* add_end_2 = ll_new(array_test, array_test_size);
    ll_add_end(add_end_2, -69);
    assert(add_end_2->tail->val == -69);
    assert(add_end_2->count == 8);
    ll_add_end(add_end_2, 1);
    ll_add_end(add_end_2, 2);
    ll_add_end(add_end_2, 3);
    ll_add_end(add_end_2, 4);
    ll_add_end(add_end_2, 5);
    assert(add_end_2->count == 13);
    assert(add_end_2->tail->val == 5);

    /* free memory */
    ll_clear(add_end_1);
    ll_clear(add_end_2);
    free(add_end_1);
    free(add_end_2);
    return;
}

void ll_to_array_tests()
{
    /* test 1: verify ll_to_array produces same array as original */
    int array_test[7] = { 8, 6, 7, 5, 3, 0, 9 };
    int array_test_size = 7;
    struct LL* to_array_1 = ll_new(array_test, array_test_size);
    int* result = ll_to_array(to_array_1);
    assert(!memcmp(array_test, result, sizeof(array_test)));

    /* test 2: verify function works for linked list of size 1 */
    struct LL* to_array_2 = ll_new(0, 0);
    ll_add_front(to_array_2, 69);
    int* result_2 = ll_to_array(to_array_2);
    assert(*result_2 == 69);

    /* free memory */
    ll_clear(to_array_1);
    ll_clear(to_array_2);
    free(to_array_1);
    free(to_array_2);
    free(result);
    free(result_2);
    return;
}

void ll_remove_end_tests()
{
    /* test 1: remove end until empty ll */
    int array_test[7] = { 8, 6, 7, 5, 3, 0, 9 };
    int array_test_size = 7;
    struct LL* remove_end_1 = ll_new(array_test, array_test_size);
    assert(ll_remove_end(remove_end_1) == 9);
    assert(remove_end_1->count == 6);
    assert(remove_end_1->tail->val == 0);
    assert(ll_remove_end(remove_end_1) == 0);
    assert(remove_end_1->count == 5);
    assert(remove_end_1->tail->val == 3);
    assert(ll_remove_end(remove_end_1) == 3);
    assert(remove_end_1->count == 4);
    assert(remove_end_1->tail->val == 5);
    assert(ll_remove_end(remove_end_1) == 5);
    assert(ll_remove_end(remove_end_1) == 7);
    assert(ll_remove_end(remove_end_1) == 6);
    assert(remove_end_1->count == 1);
    assert(remove_end_1->head->val == remove_end_1->tail->val &&
            remove_end_1->head->val == 8);
    assert(ll_remove_end(remove_end_1) == 8);
    assert(remove_end_1->count == 0);
    assert(remove_end_1->head == NULL && remove_end_1->tail == NULL);

    /* free memory */
    free(remove_end_1);
    return;
}

void ll_remove_front_tests()
{
    /* test 1: remove front until empty ll */
    int array_test[9] = { 5, -1, 2, 6, 9, 3, 7, 8, 0 };
    int i, array_test_size = 9;
    struct LL* remove_front_1 = ll_new(array_test, array_test_size);
    assert(ll_remove_front(remove_front_1) == 5);
    assert(remove_front_1->count == 8);
    assert(remove_front_1->head->val == -1);
    assert(ll_remove_front(remove_front_1) == -1);
    assert(remove_front_1->count == 7);
    assert(remove_front_1->head->val == 2);
    assert(ll_remove_front(remove_front_1) == 2);
    assert(remove_front_1->count == 6);
    assert(remove_front_1->head->val == 6);
    assert(ll_remove_front(remove_front_1) == 6);
    assert(ll_remove_front(remove_front_1) == 9);
    assert(ll_remove_front(remove_front_1) == 3);
    assert(ll_remove_front(remove_front_1) == 7);
    assert(ll_remove_front(remove_front_1) == 8);
    assert(remove_front_1->count == 1);
    assert(remove_front_1->head->val == remove_front_1->tail->val &&
            remove_front_1->head->val == 0);
    assert(ll_remove_front(remove_front_1) == 0);
    assert(remove_front_1->count == 0);
    assert(remove_front_1->head == NULL && remove_front_1->tail == NULL);

    /* free memory */
    free(remove_front_1);
    return;
}

void ll_contains_tests()
{
    /* test 1 */
    struct LL* contains_1 = ll_new(0, 0);
    assert(ll_contains(contains_1, 69) == false);
    ll_add_end(contains_1, 1);
    assert(ll_contains(contains_1, 1) == true);
    ll_add_front(contains_1, 69);
    assert(ll_contains(contains_1, 0) == false);
    assert(ll_contains(contains_1, 68) == false);
    assert(ll_contains(contains_1, 69) == true);
    ll_add_front(contains_1, 3);
    assert(ll_contains(contains_1, 3) == true);

    /* free memory */
    ll_clear(contains_1);
    free(contains_1);
    return;
}

void ll_remove_first_occurrence_tests()
{
    /* test 1 */
    int array_test[9] = { 5, -1, 2, 6, 9, 3, -1, 8, 0 };
    int array_test_size = 9;
    struct LL* rem_first_1 = ll_new(array_test, array_test_size);
    assert(ll_remove_first_occurrence(rem_first_1, 69) == false);
    assert(ll_remove_first_occurrence(rem_first_1, -1) == true);
    assert(ll_contains(rem_first_1, -1) == true);
    assert(rem_first_1->head->val == 5);
    assert(rem_first_1->head->next->val == 2);
    assert(ll_remove_first_occurrence(rem_first_1, -1) == true);
    assert(ll_remove_first_occurrence(rem_first_1, -1) == false);
    assert(ll_contains(rem_first_1, -1) == false);
    assert(rem_first_1->tail->prev->prev->val == 3);

    /* free memory */
    ll_clear(rem_first_1);
    free(rem_first_1);
    return;
}

void ll_remove_index_tests()
{
    /* test 1 */
    int array_test[7] = { 8, 6, 7, 5, 3, 0, 9 };
    int array_test_size = 7;
    struct LL* remove_index_1 = ll_new(array_test, array_test_size);
    assert(ll_remove_index(remove_index_1, 7) == false);
    assert(ll_remove_index(remove_index_1, 6) == true);
    assert(remove_index_1->tail->val == 0);
    assert(ll_remove_index(remove_index_1, 6) == false);
    assert(ll_remove_index(remove_index_1, 0) == true);
    assert(ll_remove_index(remove_index_1, 2) == true);
    /* current state of ll: { 6, 7, 3, 0 } */
    assert(remove_index_1->head->val == 6);
    assert(remove_index_1->count == 4);
    assert(ll_remove_index(remove_index_1, 4) == false);

    /* free memory */
    ll_clear(remove_index_1);
    free(remove_index_1);
    return;
}

void ll_clear_tests()
{
    /* test 1 */
    int array_test[7] = { 8, 6, 7, 5, 3, 0, 9 };
    int array_test_size = 7;
    struct LL* clear_1 = ll_new(array_test, array_test_size);
    ll_clear(clear_1);
    assert(clear_1->count == 0);
    assert(clear_1->head == NULL);
    assert(clear_1->tail == NULL);

    /* test 2: attempting to clear an empty ll */
    struct LL* clear_2 = ll_new(0, 0);
    ll_clear(clear_2);
    assert(clear_1->count == 0);
    assert(clear_1->head == NULL);
    assert(clear_1->tail == NULL);

    /* free memory */
    free(clear_1);
    free(clear_2);
    return;
}

void ll_insert_before_tests()
{
    /* test 1 */
    int array_test[7] = { 8, 6, 7, 5, 3, 0, 9 };
    int array_test_size = 7;
    struct LL* insert_before_1 = ll_new(array_test, array_test_size);
    ll_insert_before(insert_before_1, 0, 69);
    assert(insert_before_1->head->val == 69);
    assert(insert_before_1->head->next->val == 8);
    assert(insert_before_1->count == 8);
    ll_insert_before(insert_before_1, 7, 69);
    assert(insert_before_1->tail->prev->val == 69);
    assert(insert_before_1->count == 9);
    assert(insert_before_1->tail->prev->next->val == 9);
    /* { 69, 8, 6, 7, 5, 3, 0, 69, 9 } */
    ll_insert_before(insert_before_1, 4, -69);
    assert(insert_before_1->head->next->next->next->next->val == -69);
    assert(insert_before_1->count == 10);

    /* free memory */
    ll_clear(insert_before_1);
    free(insert_before_1);
    return;
}

int main(void)
{
    ll_new_tests();
    printf("All ll_new tests pass!\n");
    ll_add_front_tests();
    printf("All ll_add_front tests pass!\n");
    ll_add_end_tests();
    printf("All ll_add_end tests pass!\n");
    ll_to_array_tests();
    printf("All ll_to_array tests pass!\n");
    ll_remove_end_tests();
    printf("All ll_remove_end tests pass!\n");
    ll_remove_front_tests();
    printf("All ll_remove_front tests pass!\n");
    ll_contains_tests();
    printf("All ll_contains tests pass!\n");
    ll_remove_first_occurrence_tests();
    printf("All ll_remove_first_occurrence tests pass!\n");
    ll_remove_index_tests();
    printf("All ll_remove_index tests pass!\n");
    ll_clear_tests();
    printf("All ll_clear tests pass!\n");
    ll_insert_before_tests();
    printf("All ll_insert_before tests pass!\n");
    return 0;
}
