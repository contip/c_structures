#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "gll.h"

struct TestStruct
{
    int property_1;
    double property_2;
};

void obj_tests()
{
    struct LL* test_1 = ll_init();
    int int_val = 69;

    struct TestStruct* obj = malloc(sizeof(struct TestStruct));
    obj->property_1 = 5;
    obj->property_2 = 10.324;
    void* obj_ptr = (void*)obj;

    struct TestStruct* obj_2 = malloc(sizeof(struct TestStruct));
    obj_2->property_1 = 222;
    obj_2->property_2 = 1.69;
    void* obj_2_ptr = (void*)obj_2;

    struct TestStruct* obj_3 = malloc(sizeof(struct TestStruct));
    obj_3->property_1 = 690;
    obj_3->property_2 = 10.69;
    void* obj_3_ptr = (void*)obj_3;

    struct TestStruct* obj_4 = malloc(sizeof(struct TestStruct));
    obj_4->property_1 = 119;
    obj_4->property_2 = 10.9;
    void* obj_4_ptr = (void*)obj_4;

    ll_append(test_1, obj_ptr, DATA);
    assert(test_1->count == 1);
    ll_append(test_1, &int_val, INT);
    ll_append(test_1, obj_2_ptr, DATA);
    ll_append(test_1, obj_3_ptr, DATA);
    ll_prepend(test_1, obj_4_ptr, DATA);
    assert(test_1->count == 5);

    /* { obj_4 -> obj_1 -> int_val -> obj_2 -> obj_3 } */
    assert(ll_contains(test_1, obj_ptr, DATA) == true);
    assert(ll_contains(test_1, obj_2_ptr, DATA) == true);
    assert(ll_contains(test_1, obj_3_ptr, DATA) == true);
    assert(ll_contains(test_1, obj_4_ptr, DATA) == true);

    void* result = ll_pop_end(test_1);
    assert(((struct TestStruct*)result)->property_1 == 690);
    assert(result == obj_3_ptr);
    assert(test_1->count == 4);

    result = ll_pop_front(test_1);
    assert(((struct TestStruct*)result)->property_2 == 10.9);
    assert(result == obj_4_ptr);
    assert(test_1->count == 3);

    /* { obj_1 -> int_val } */
    assert(ll_remove_first(test_1, obj_2_ptr, DATA) == true);
    /* { obj_1 -> int_val } */
    assert(ll_contains(test_1, obj_2_ptr, DATA) == false);
    assert(ll_remove_index(test_1, 0) == true);
    /* { int_val } */
    assert(ll_contains(test_1, obj_ptr, DATA) == false);
    assert(test_1->count == 1);
    assert((*(int*)test_1->head->data) == 69);

    /* free memory */
    ll_clear(test_1, true);
    free(test_1); 
    free(obj);
    free(obj_2);
    free(obj_3);
    free(obj_4);
}


int main(void)
{
    obj_tests();
    printf("all tests passed!\n");
    return 0;
}
