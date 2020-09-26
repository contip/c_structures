#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct 
{
    int property_1;
    double property_2;
}
TestStruct;

int int_values[5] = { 10, 5, -3, 22, 9 };
double dbl_values[5] = { 0.12, 2.3, 4.44, 433.1, 9.2 };

void stack_tests()
{
    int i;
    TestStruct* my_obj = malloc(sizeof(TestStruct));
    my_obj->property_1 = 69;
    my_obj->property_2 = 69.69;
    Stack* test_stack = stack_init();
    for (i = 0; i < 5; i++)
    {
        assert(stack_push(test_stack, &int_values[i], INT));
    }
    //stack_print(test_stack);
    int* int_result;
    int_result = stack_pop(test_stack);
    assert(*int_result == 9);
    free(int_result);
    int_result = stack_pop(test_stack);
    assert(*int_result == 22);
    free(int_result);
    int_result = stack_pop(test_stack);
    assert(*int_result == -3);
    free(int_result);
    int_result = stack_pop(test_stack);
    assert(*int_result == 5);
    free(int_result);
    int_result = stack_pop(test_stack);
    assert(*int_result == 10);
    free(int_result);
    int_result = stack_pop(test_stack);
    assert(stack_pop(test_stack) == NULL);
    assert(test_stack->count == 0);

    for (i = 0; i < 5; i++)
    {
        assert(stack_push(test_stack, &dbl_values[i], DOUBLE));
    }
    double* double_result;
    assert(test_stack->count == 5);
    assert(*(double*)stack_peek(test_stack) == 9.2);
    assert(test_stack->count == 5);
    double_result = stack_pop(test_stack);
    assert(*double_result == 9.2);
    free(double_result);
    assert(test_stack->count == 4);

    assert(stack_push(test_stack, (void*)my_obj, DATA));
    //stack_print(test_stack);
    void* result = stack_pop(test_stack);
    assert(result == (void*)my_obj);
    assert(((TestStruct*)result)->property_1 == 69);
    assert(((TestStruct*)result)->property_2 == 69.69);

    double_result = stack_pop(test_stack);
    assert(*double_result == 433.1);
    free(double_result);
    double_result = stack_pop(test_stack);
    assert(*double_result == 4.44);
    free(double_result);
    double_result = stack_pop(test_stack);
    assert(*double_result == 2.3);
    free(double_result);
    double_result = stack_pop(test_stack);
    assert(*double_result == 0.12);
    free(double_result);
    assert(stack_pop(test_stack) == NULL);
    assert(test_stack->count == 0);

    stack_clear(test_stack, true);
    free(test_stack);
    free(my_obj);
}

int main(void)
{
    stack_tests();
    printf("all stack tests passed!\n");
    return 0;
}
