#include "queue.h"
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

void queue_tests()
{
    int i;
    TestStruct* my_obj = malloc(sizeof(TestStruct));
    my_obj->property_1 = 69;
    my_obj->property_2 = 69.69;
    Queue* test_queue = queue_init();
    for (i = 0; i < 5; i++)
    {
        assert(queue_enqueue(test_queue, &int_values[i], INT));
    }
    //queue_print(test_queue);
    int* int_result;
    int_result = queue_dequeue(test_queue);
    assert(*int_result == 10);
    free(int_result);
    int_result = queue_dequeue(test_queue);
    assert(*int_result == 5);
    free(int_result);
    int_result = queue_dequeue(test_queue);
    assert(*int_result == -3);
    free(int_result);
    int_result = queue_dequeue(test_queue);
    assert(*int_result == 22);
    free(int_result);
    int_result = queue_dequeue(test_queue);
    assert(*int_result == 9);
    free(int_result);
    int_result = queue_dequeue(test_queue);
    assert(queue_dequeue(test_queue) == NULL);
    assert(test_queue->count == 0);

    for (i = 0; i < 5; i++)
    {
        assert(queue_enqueue(test_queue, &dbl_values[i], DOUBLE));
    }
    double* double_result;
    assert(test_queue->count == 5);
    assert(*(double*)queue_front(test_queue) == 0.12);
    assert(test_queue->count == 5);
    double_result = queue_dequeue(test_queue);
    assert(*double_result == 0.12);
    free(double_result);
    assert(test_queue->count == 4);

    assert(queue_enqueue(test_queue, (void*)my_obj, DATA));
    //queue_print(test_queue);

    double_result = queue_dequeue(test_queue);
    assert(*double_result == 2.3);
    free(double_result);
    double_result = queue_dequeue(test_queue);
    assert(*double_result == 4.44);
    free(double_result);
    double_result = queue_dequeue(test_queue);
    assert(*double_result == 433.1);
    free(double_result);
    double_result = queue_dequeue(test_queue);
    assert(*double_result == 9.2);
    free(double_result);

    void* result = queue_dequeue(test_queue);
    assert(result == (void*)my_obj);
    assert(((TestStruct*)result)->property_1 == 69);
    assert(((TestStruct*)result)->property_2 == 69.69);

    assert(queue_dequeue(test_queue) == NULL);
    assert(test_queue->count == 0);

    queue_clear(test_queue, true);
    free(test_queue);
    free(my_obj);
}

int main(void)
{
    queue_tests();
    printf("all queue tests passed!\n");
    return 0;
}
