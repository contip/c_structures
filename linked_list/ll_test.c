#include "ll.h"
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


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

void add_front_tests()
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

void add_end_tests()
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

int main(void)
{
    ll_new_tests();
    add_front_tests();
    add_end_tests();
    printf("All tests pass!\n");
    return 0;
}
