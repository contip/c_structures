#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "gll.h"

void init_tests()
{
    struct LL* init_1 = ll_init();
    assert(init_1->count == 0);
    assert(init_1->head == NULL);
    assert(init_1->tail == NULL);
    free(init_1);
}

void add_end_tests()
{
    /* test 1 - add integers */
    struct LL* add_end_1 = ll_init();
    assert(add_end_1->count == 0);
    int i, int_vals[5] = { 69, -1, 20, 15, 0 };
    ll_add_end(add_end_1, &int_vals[0], INT);
    assert(add_end_1->count == 1);
    assert(*(int*)add_end_1->head->data == 69);
    assert(*(int*)add_end_1->tail->data == 69);
    for (i = 1; i < 5; i ++)
    {
        ll_add_end(add_end_1, &int_vals[i], INT);
    }
    assert(*(int*)add_end_1->head->data == 69);
    assert(*(int*)add_end_1->tail->data == 0);
    assert(*(int*)add_end_1->tail->prev->data == 15);
    assert(*(int*)add_end_1->tail->prev->prev->data == 20);
    assert(*(int*)add_end_1->tail->prev->prev->prev->data == -1);
    assert(add_end_1->count == 5);

    /* test 2 - add floating point numbers */
    struct LL* add_end_2 = ll_init();
    double double_vals[5] = { 1.69, -2.22, 3.4, 300.1, 0.3432 };
    for (i = 0; i < 5; i ++)
    {
        ll_add_end(add_end_2, &double_vals[i], DOUBLE);
    }
    assert(*(double*)add_end_2->head->data == 1.69);
    assert(*(double*)add_end_2->head->next->data == -2.22);
    assert(*(double*)add_end_2->head->next->next->data == 3.4);
    assert(*(double*)add_end_2->head->next->next->next->data == 300.1);
    assert(*(double*)add_end_2->head->next->next->next->next->data == 0.3432);
    assert(add_end_2->count == 5);

    /* test 3 - add individual characters */
    struct LL* add_end_3 = ll_init();
    char char_vals[5] = "Abba!";
    for (i = 0; i < 5; i ++)
    {
        ll_add_end(add_end_3, &char_vals[i], CHAR);
    }
    assert(*(char*)add_end_3->head->data == 'A');
    assert(*(char*)add_end_3->tail->data == '!');
    assert(*(char*)add_end_3->tail->prev->data == 'a');
    assert(*(char*)add_end_3->tail->prev->prev->data == 'b');
    assert(*(char*)add_end_3->head->next->data == 'b');

    /* test 4 - add strings */
    struct LL* add_end_4 = ll_init();
    char string_vals[5][20] = { "dilaudid", "opana", "oxy", "hydro", "dope" };
    for (i = 0; i < 5; i ++)
    {
        ll_add_end(add_end_4, &string_vals[i], STRING);
    }
    assert(strcmp((char*)add_end_4->head->data, string_vals[0]) == 0);
    assert(strcmp((char*)add_end_4->head->next->data, string_vals[1]) == 0);
    assert(strcmp((char*)add_end_4->head->next->next->data,
                string_vals[2]) == 0);
    assert(strcmp((char*)add_end_4->head->next->next->next->data,
                string_vals[3]) == 0);
    assert(strcmp((char*)add_end_4->head->next->next->next->next->data,
                string_vals[4]) == 0);

    /* test 5 - add mixed data types */
    struct LL* add_end_5 = ll_init();
    int val_1 = 69;
    double val_2 = 69.69;
    char val_3 = 'z';
    char val_4[10] = "aaaaaaaaa";
    int val_5 = -30;
    ll_add_end(add_end_5, &val_1, INT);
    ll_add_end(add_end_5, &val_2, DOUBLE);
    ll_add_end(add_end_5, &val_3, CHAR);
    ll_add_end(add_end_5, &val_4, STRING);
    ll_add_end(add_end_5, &val_5, INT);
    assert(add_end_5->count == 5);
    assert(*(int*)add_end_5->head->data == 69);
    assert(*(double*)add_end_5->head->next->data == 69.69);
    assert(*(char*)add_end_5->head->next->next->data == 'z');
    assert(strcmp((char*)add_end_5->head->next->next->next->data, "aaaaaaaaa") == 0);
    assert(*(int*)add_end_5->tail->data == -30);

    /* free memory */

    return;
}

void add_front_tests()
{
    /* test 1 - add integers */
    struct LL* add_front_1 = ll_init();
    assert(add_front_1->count == 0);
    int i, int_vals[5] = { 69, -1, 20, 15, 0 };
    ll_add_front(add_front_1, &int_vals[0], INT);
    assert(add_front_1->count == 1);
    assert(*(int*)add_front_1->head->data == 69);
    assert(*(int*)add_front_1->tail->data == 69);
    for (i = 1; i < 5; i ++)
    {
        ll_add_front(add_front_1, &int_vals[i], INT);
    }
    assert(*(int*)add_front_1->head->data == 0);
    assert(*(int*)add_front_1->tail->data == 69);
    assert(*(int*)add_front_1->tail->prev->data == -1);
    assert(*(int*)add_front_1->tail->prev->prev->data == 20);
    assert(*(int*)add_front_1->tail->prev->prev->prev->data == 15);
    assert(add_front_1->count == 5);

    /* test 2 - add floating point numbers */
    struct LL* add_front_2 = ll_init();
    double double_vals[5] = { 1.69, -2.22, 3.4, 300.1, 0.3432 };
    for (i = 0; i < 5; i ++)
    {
        ll_add_front(add_front_2, &double_vals[i], DOUBLE);
    }
    assert(*(double*)add_front_2->head->data == 0.3432);
    assert(*(double*)add_front_2->head->next->data == 300.1);
    assert(*(double*)add_front_2->head->next->next->data == 3.4);
    assert(*(double*)add_front_2->head->next->next->next->data == -2.22);
    assert(*(double*)add_front_2->head->next->next->next->next->data == 1.69);
    assert(add_front_2->count == 5);

    /* test 3 - add individual characters */
    struct LL* add_front_3 = ll_init();
    char char_vals[5] = "Abba!";
    for (i = 0; i < 5; i ++)
    {
        ll_add_front(add_front_3, &char_vals[i], CHAR);
    }
    assert(*(char*)add_front_3->head->data == '!');
    assert(*(char*)add_front_3->tail->data == 'A');
    assert(*(char*)add_front_3->tail->prev->data == 'b');
    assert(*(char*)add_front_3->tail->prev->prev->data == 'b');
    assert(*(char*)add_front_3->head->next->data == 'a');

    /* test 4 - add strings */
    struct LL* add_front_4 = ll_init();
    char string_vals[5][20] = { "dilaudid", "opana", "oxy", "hydro", "dope" };
    for (i = 0; i < 5; i ++)
    {
        ll_add_front(add_front_4, &string_vals[i], STRING);
    }
    assert(strcmp((char*)add_front_4->head->data, string_vals[4]) == 0);
    assert(strcmp((char*)add_front_4->head->next->data, string_vals[3]) == 0);
    assert(strcmp((char*)add_front_4->head->next->next->data,
                string_vals[2]) == 0);
    assert(strcmp((char*)add_front_4->head->next->next->next->data,
                string_vals[1]) == 0);
    assert(strcmp((char*)add_front_4->head->next->next->next->next->data,
                string_vals[0]) == 0);

    /* test 5 - add mixed data types */
    struct LL* add_front_5 = ll_init();
    int val_1 = 69;
    double val_2 = 69.69;
    char val_3 = 'z';
    char val_4[10] = "aaaaaaaaa";
    int val_5 = -30;
    /* { -30, "aaaaaaaaa", 'z', 69.69, 69 } */
    ll_add_front(add_front_5, &val_1, INT);
    ll_add_front(add_front_5, &val_2, DOUBLE);
    ll_add_front(add_front_5, &val_3, CHAR);
    ll_add_front(add_front_5, &val_4, STRING);
    ll_add_front(add_front_5, &val_5, INT);
    assert(add_front_5->count == 5);
    assert(*(int*)add_front_5->head->data == -30);
    assert(strcmp((char*)add_front_5->head->next->data, "aaaaaaaaa") == 0);
    assert(*(char*)add_front_5->head->next->next->data == 'z');
    assert(*(double*)add_front_5->head->next->next->next->data == 69.69);
    assert(*(int*)add_front_5->tail->data == 69);

    /* free memory */

    return;
}

void pop_end_tests()
{
    /* test 1 - integers */
    struct LL* pop_end_1 = ll_init();
    int i, int_vals[5] = { 69, -1, 20, 15, 0 };
    for (i = 0; i < 5; i++)
    {
        ll_add_end(pop_end_1, &int_vals[i], INT);
    }
    for (i = 4; i > -1; i--)
    {
        void* result = ll_pop_end(pop_end_1);
        assert(*(int*)result == int_vals[i]);
        free(result);
    }
    assert(pop_end_1->count == 0);
    assert(ll_pop_end(pop_end_1) == NULL);

    /* test 2 - doubles */
    struct LL* pop_end_2 = ll_init();
    double double_vals[5] = { 1.69, -2.22, 3.4, 300.1, 0.3432 };
    for (i = 0; i < 5; i ++)
    {
        ll_add_end(pop_end_2, &double_vals[i], DOUBLE);
    }
    for (i = 4; i > -1; i--)
    {
        void* result = ll_pop_end(pop_end_2);
        assert(*(double*)result == double_vals[i]);
        free(result);
    }
    assert(pop_end_2->count == 0);
    assert(ll_pop_end(pop_end_2) == NULL);

    /* test 3 - chars */
    struct LL* pop_end_3 = ll_init();
    char char_vals[5] = "Abba!";
    for (i = 0; i < 5; i ++)
    {
        ll_add_end(pop_end_3, &char_vals[i], CHAR);
    }
    for (i = 4; i > -1; i--)
    {
        void* result = ll_pop_end(pop_end_3);
        assert(*(char*)result == char_vals[i]);
        free(result);
    }
    assert(pop_end_3->count == 0);
    assert(ll_pop_end(pop_end_3) == NULL);

    /* test 4 - strings */
    struct LL* pop_end_4 = ll_init();
    char string_vals[5][20] = { "dilaudid", "opana", "oxy", "hydro", "dope" };
    for (i = 0; i < 5; i ++)
    {
        ll_add_end(pop_end_4, &string_vals[i], STRING);
    }
    for (i = 4; i > -1; i--)
    {
        void* result = ll_pop_end(pop_end_4);
        assert(strcmp((char*)result, string_vals[i]) == 0);
        free(result);
    }
    assert(pop_end_4->count == 0);
    assert(ll_pop_end(pop_end_4) == NULL);

    /* test 5 - mixed data types */
    struct LL* pop_end_5 = ll_init();
    int val_1 = 69;
    double val_2 = 69.69;
    char val_3 = 'z';
    char val_4[10] = "aaaaaaaaa";
    int val_5 = -30;
    ll_add_end(pop_end_5, &val_1, INT);
    ll_add_end(pop_end_5, &val_2, DOUBLE);
    ll_add_end(pop_end_5, &val_3, CHAR);
    ll_add_end(pop_end_5, &val_4, STRING);
    ll_add_end(pop_end_5, &val_5, INT);
    assert(pop_end_5->count == 5);
    void* result = ll_pop_end(pop_end_5);
    assert(*(int*)result == -30);
    free(result);
    result = ll_pop_end(pop_end_5);
    assert(strcmp((char*)result, "aaaaaaaaa") == 0);
    free(result);
    result = ll_pop_end(pop_end_5);
    assert(*(char*)result == 'z');
    free(result);
    result = ll_pop_end(pop_end_5);
    assert(*(double*)result == 69.69);
    free(result);
    result = ll_pop_end(pop_end_5);
    assert(*(int*)result == 69);
    free(result);
    assert(pop_end_5->count == 0);
    assert(ll_pop_end(pop_end_5) == NULL);
}

void pop_front_tests()
{
    /* test 1 - integers */
    struct LL* pop_front_1 = ll_init();
    int i, int_vals[5] = { 69, -1, 20, 15, 0 };
    for (i = 0; i < 5; i++)
    {
        ll_add_front(pop_front_1, &int_vals[i], INT);
    }
    /* { 0, 15, 20, -1, 69 } */
    for (i = 4; i > -1; i--)
    {
        void* result = ll_pop_front(pop_front_1);
        assert(*(int*)result == int_vals[i]);
        free(result);
    }
    assert(pop_front_1->count == 0);
    assert(ll_pop_front(pop_front_1) == NULL);

    /* test 2 - doubles */
    struct LL* pop_front_2 = ll_init();
    double double_vals[5] = { 1.69, -2.22, 3.4, 300.1, 0.3432 };
    for (i = 0; i < 5; i ++)
    {
        ll_add_front(pop_front_2, &double_vals[i], DOUBLE);
    }
    for (i = 4; i > -1; i--)
    {
        void* result = ll_pop_front(pop_front_2);
        assert(*(double*)result == double_vals[i]);
        free(result);
    }
    assert(pop_front_2->count == 0);
    assert(ll_pop_front(pop_front_2) == NULL);

    /* test 3 - chars */
    struct LL* pop_front_3 = ll_init();
    char char_vals[5] = "Abba!";
    for (i = 0; i < 5; i ++)
    {
        ll_add_front(pop_front_3, &char_vals[i], CHAR);
    }
    for (i = 4; i > -1; i--)
    {
        void* result = ll_pop_front(pop_front_3);
        assert(*(char*)result == char_vals[i]);
        free(result);
    }
    assert(pop_front_3->count == 0);
    assert(ll_pop_front(pop_front_3) == NULL);

    /* test 4 - strings */
    struct LL* pop_front_4 = ll_init();
    char string_vals[5][20] = { "dilaudid", "opana", "oxy", "hydro", "dope" };
    for (i = 0; i < 5; i ++)
    {
        ll_add_front(pop_front_4, &string_vals[i], STRING);
    }
    for (i = 4; i > -1; i--)
    {
        void* result = ll_pop_front(pop_front_4);
        assert(strcmp((char*)result, string_vals[i]) == 0);
        free(result);
    }
    assert(pop_front_4->count == 0);
    assert(ll_pop_front(pop_front_4) == NULL);

    /* test 5 - mixed data types */
    struct LL* pop_front_5 = ll_init();
    int val_1 = 69;
    double val_2 = 69.69;
    char val_3 = 'z';
    char val_4[10] = "aaaaaaaaa";
    int val_5 = -30;
    ll_add_front(pop_front_5, &val_1, INT);
    ll_add_front(pop_front_5, &val_2, DOUBLE);
    ll_add_front(pop_front_5, &val_3, CHAR);
    ll_add_front(pop_front_5, &val_4, STRING);
    ll_add_front(pop_front_5, &val_5, INT);
    assert(pop_front_5->count == 5);
    void* result = ll_pop_front(pop_front_5);
    assert(*(int*)result == -30);
    free(result);
    result = ll_pop_front(pop_front_5);
    assert(strcmp((char*)result, "aaaaaaaaa") == 0);
    free(result);
    result = ll_pop_front(pop_front_5);
    assert(*(char*)result == 'z');
    free(result);
    result = ll_pop_front(pop_front_5);
    assert(*(double*)result == 69.69);
    free(result);
    result = ll_pop_front(pop_front_5);
    assert(*(int*)result == 69);
    free(result);
    assert(pop_front_5->count == 0);
    assert(ll_pop_front(pop_front_5) == NULL);
}

int main(void)
{
    init_tests();
    printf("All initialization tests passed!\n");
    add_end_tests();
    printf("All add_end tests passed!\n");
    add_front_tests();
    printf("All add_front tests passed!\n");
    pop_end_tests();
    printf("All pop_end tests passed!\n");
    pop_front_tests();
    printf("All pop_front tests passed!\n");
    return 0;
}
