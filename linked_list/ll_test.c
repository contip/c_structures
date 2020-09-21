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
    int ll_array[5] = { 15, 0, 1, 2, 7 };
    int ll_array_size = 5;
    struct LL* ll_new_1 = ll_new(ll_array, ll_array_size);
    assert(ll_new_1->head->val == 15);
    assert(ll_new_1->tail->val == 7);
    assert(ll_new_1->count == 5);
    assert(ll_new_1->head->next->val == 0);
    assert(ll_new_1->head->next->next->val == 1);
    assert(ll_new_1->head->next->next->next->val == 2);
    assert(ll_new_1->head->next->next->next->next->val == 7);

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

    return;
}

void ll_add_end_tests()
{
    /* test 1: initialize empty ll and build by adding values to rear */
    struct LL* add_end_1 = ll_new(0, 0);
    ll_add_end(add_end_1, 1);
    ll_add_end(add_end_1, 2);
    ll_add_end(add_end_1, 3);
    ll_add_end(add_end_1, 4);
    ll_add_end(add_end_1, 5);
    assert(add_end_1->head->val == 1);
    assert(add_end_1->tail->val == 5);
    assert(add_end_1->count == 5);

    return;
}

void ll_to_array_tests()
{
    int array_test[7] = { 8, 6, 7, 5, 3, 0, 9 };
    int i, array_test_size = 7;
    struct LL* to_array_1 = ll_new(array_test, array_test_size);
    int* result = ll_to_array(to_array_1);
    assert(!memcmp(array_test, result, sizeof(array_test)));
    
    return;
}

void ll_remove_end_tests()
{
    int array_test[7] = { 8, 6, 7, 5, 3, 0, 9 };
    int i, array_test_size = 7;
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
    return;
}

void ll_remove_front_tests()
{
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
    return;
}

void ll_contains_tests()
{
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

    return;
}

void ll_remove_first_occurrence_tests()
{
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
    return;
}

void ll_remove_index_tests()
{
    int array_test[7] = { 8, 6, 7, 5, 3, 0, 9 };
    int array_test_size = 7;
    struct LL* remove_index_1 = ll_new(array_test, array_test_size);
    assert(ll_remove_index(remove_index_1, 7) == false);
    assert(ll_remove_index(remove_index_1, 6) == true);
    assert(remove_index_1->tail->val == 0);
    assert(ll_remove_index(remove_index_1, 6) == false);
    assert(ll_remove_index(remove_index_1, 0) == true);
    assert(ll_remove_index(remove_index_1, 2) == true);
    /* { 6, 7, 3, 0 } */
    assert(remove_index_1->head->val == 6);
    assert(remove_index_1->count == 4);
    assert(ll_remove_index(remove_index_1, 4) == false);
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
    return 0;
}
