#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "gll.h"

void init_tests()
{
    LL* init_1 = ll_init();
    assert(init_1->count == 0);
    assert(init_1->head == NULL);
    assert(init_1->tail == NULL);
    free(init_1);
}

void append_tests()
{
    /* test 1 - add integers */
    LL* append_1 = ll_init();
    assert(append_1->count == 0);
    int i, int_vals[5] = { 69, -1, 20, 15, 0 };
    ll_append(append_1, &int_vals[0], INT);
    assert(append_1->count == 1);
    assert(*(int*)append_1->head->data == 69);
    assert(*(int*)append_1->tail->data == 69);
    for (i = 1; i < 5; i ++)
    {
        ll_append(append_1, &int_vals[i], INT);
    }
    assert(*(int*)append_1->head->data == 69);
    assert(*(int*)append_1->tail->data == 0);
    assert(*(int*)append_1->tail->prev->data == 15);
    assert(*(int*)append_1->tail->prev->prev->data == 20);
    assert(*(int*)append_1->tail->prev->prev->prev->data == -1);
    assert(append_1->count == 5);

    /* test 2 - add floating point numbers */
    LL* append_2 = ll_init();
    double double_vals[5] = { 1.69, -2.22, 3.4, 300.1, 0.3432 };
    for (i = 0; i < 5; i ++)
    {
        ll_append(append_2, &double_vals[i], DOUBLE);
    }
    assert(*(double*)append_2->head->data == 1.69);
    assert(*(double*)append_2->head->next->data == -2.22);
    assert(*(double*)append_2->head->next->next->data == 3.4);
    assert(*(double*)append_2->head->next->next->next->data == 300.1);
    assert(*(double*)append_2->head->next->next->next->next->data == 0.3432);
    assert(append_2->count == 5);

    /* test 3 - add individual characters */
    LL* append_3 = ll_init();
    char char_vals[5] = "Abba!";
    for (i = 0; i < 5; i ++)
    {
        ll_append(append_3, &char_vals[i], CHAR);
    }
    assert(*(char*)append_3->head->data == 'A');
    assert(*(char*)append_3->tail->data == '!');
    assert(*(char*)append_3->tail->prev->data == 'a');
    assert(*(char*)append_3->tail->prev->prev->data == 'b');
    assert(*(char*)append_3->head->next->data == 'b');

    /* test 4 - add strings */
    LL* append_4 = ll_init();
    char string_vals[5][20] = { "dilaudid", "piano", "YAa", "marsu", "DzZy" };
    for (i = 0; i < 5; i ++)
    {
        ll_append(append_4, &string_vals[i], STRING);
    }
    assert(strcmp((char*)append_4->head->data, string_vals[0]) == 0);
    assert(strcmp((char*)append_4->head->next->data, string_vals[1]) == 0);
    assert(strcmp((char*)append_4->head->next->next->data,
                string_vals[2]) == 0);
    assert(strcmp((char*)append_4->head->next->next->next->data,
                string_vals[3]) == 0);
    assert(strcmp((char*)append_4->head->next->next->next->next->data,
                string_vals[4]) == 0);

    /* test 5 - add mixed data types */
    LL* append_5 = ll_init();
    int val_1 = 69;
    double val_2 = 69.69;
    char val_3 = 'z';
    char val_4[10] = "aaaaaaaaa";
    int val_5 = -30;
    ll_append(append_5, &val_1, INT);
    ll_append(append_5, &val_2, DOUBLE);
    ll_append(append_5, &val_3, CHAR);
    ll_append(append_5, &val_4, STRING);
    ll_append(append_5, &val_5, INT);
    assert(append_5->count == 5);
    assert(*(int*)append_5->head->data == 69);
    assert(*(double*)append_5->head->next->data == 69.69);
    assert(*(char*)append_5->head->next->next->data == 'z');
    assert(strcmp((char*)append_5->head->next->next->next->data, "aaaaaaaaa") == 0);
    assert(*(int*)append_5->tail->data == -30);

    /* free memory */
    ll_clear(append_1, true);
    ll_clear(append_2, true);
    ll_clear(append_3, true);
    ll_clear(append_4, true);
    ll_clear(append_5, true);
    free(append_1);
    free(append_2);
    free(append_3);
    free(append_4);
    free(append_5);
    return;
}

void prepend_tests()
{
    /* test 1 - add integers */
    LL* prepend_1 = ll_init();
    assert(prepend_1->count == 0);
    int i, int_vals[5] = { 69, -1, 20, 15, 0 };
    ll_prepend(prepend_1, &int_vals[0], INT);
    assert(prepend_1->count == 1);
    assert(*(int*)prepend_1->head->data == 69);
    assert(*(int*)prepend_1->tail->data == 69);
    for (i = 1; i < 5; i ++)
    {
        ll_prepend(prepend_1, &int_vals[i], INT);
    }
    assert(*(int*)prepend_1->head->data == 0);
    assert(*(int*)prepend_1->tail->data == 69);
    assert(*(int*)prepend_1->tail->prev->data == -1);
    assert(*(int*)prepend_1->tail->prev->prev->data == 20);
    assert(*(int*)prepend_1->tail->prev->prev->prev->data == 15);
    assert(prepend_1->count == 5);

    /* test 2 - add floating point numbers */
    LL* prepend_2 = ll_init();
    double double_vals[5] = { 1.69, -2.22, 3.4, 300.1, 0.3432 };
    for (i = 0; i < 5; i ++)
    {
        ll_prepend(prepend_2, &double_vals[i], DOUBLE);
    }
    assert(*(double*)prepend_2->head->data == 0.3432);
    assert(*(double*)prepend_2->head->next->data == 300.1);
    assert(*(double*)prepend_2->head->next->next->data == 3.4);
    assert(*(double*)prepend_2->head->next->next->next->data == -2.22);
    assert(*(double*)prepend_2->head->next->next->next->next->data == 1.69);
    assert(prepend_2->count == 5);

    /* test 3 - add individual characters */
    LL* prepend_3 = ll_init();
    char char_vals[5] = "Abba!";
    for (i = 0; i < 5; i ++)
    {
        ll_prepend(prepend_3, &char_vals[i], CHAR);
    }
    assert(*(char*)prepend_3->head->data == '!');
    assert(*(char*)prepend_3->tail->data == 'A');
    assert(*(char*)prepend_3->tail->prev->data == 'b');
    assert(*(char*)prepend_3->tail->prev->prev->data == 'b');
    assert(*(char*)prepend_3->head->next->data == 'a');

    /* test 4 - add strings */
    LL* prepend_4 = ll_init();
    char string_vals[5][20] = { "dilaudid", "piano", "YAa", "marsu", "DzZy" };
    for (i = 0; i < 5; i ++)
    {
        ll_prepend(prepend_4, &string_vals[i], STRING);
    }
    assert(strcmp((char*)prepend_4->head->data, string_vals[4]) == 0);
    assert(strcmp((char*)prepend_4->head->next->data, string_vals[3]) == 0);
    assert(strcmp((char*)prepend_4->head->next->next->data,
                string_vals[2]) == 0);
    assert(strcmp((char*)prepend_4->head->next->next->next->data,
                string_vals[1]) == 0);
    assert(strcmp((char*)prepend_4->head->next->next->next->next->data,
                string_vals[0]) == 0);

    /* test 5 - add mixed data types */
    LL* prepend_5 = ll_init();
    int val_1 = 69;
    double val_2 = 69.69;
    char val_3 = 'z';
    char val_4[10] = "aaaaaaaaa";
    int val_5 = -30;
    /* { -30, "aaaaaaaaa", 'z', 69.69, 69 } */
    ll_prepend(prepend_5, &val_1, INT);
    ll_prepend(prepend_5, &val_2, DOUBLE);
    ll_prepend(prepend_5, &val_3, CHAR);
    ll_prepend(prepend_5, &val_4, STRING);
    ll_prepend(prepend_5, &val_5, INT);
    assert(prepend_5->count == 5);
    assert(*(int*)prepend_5->head->data == -30);
    assert(strcmp((char*)prepend_5->head->next->data, "aaaaaaaaa") == 0);
    assert(*(char*)prepend_5->head->next->next->data == 'z');
    assert(*(double*)prepend_5->head->next->next->next->data == 69.69);
    assert(*(int*)prepend_5->tail->data == 69);

    /* free memory */
    ll_clear(prepend_1, true);
    ll_clear(prepend_2, true);
    ll_clear(prepend_3, true);
    ll_clear(prepend_4, true);
    ll_clear(prepend_5, true);
    free(prepend_1);
    free(prepend_2);
    free(prepend_3);
    free(prepend_4);
    free(prepend_5);
    return;
}

void pop_end_tests()
{
    /* test 1 - integers */
    LL* pop_end_1 = ll_init();
    int i, int_vals[5] = { 69, -1, 20, 15, 0 };
    for (i = 0; i < 5; i++)
    {
        ll_append(pop_end_1, &int_vals[i], INT);
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
    LL* pop_end_2 = ll_init();
    double double_vals[5] = { 1.69, -2.22, 3.4, 300.1, 0.3432 };
    for (i = 0; i < 5; i ++)
    {
        ll_append(pop_end_2, &double_vals[i], DOUBLE);
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
    LL* pop_end_3 = ll_init();
    char char_vals[5] = "Abba!";
    for (i = 0; i < 5; i ++)
    {
        ll_append(pop_end_3, &char_vals[i], CHAR);
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
    LL* pop_end_4 = ll_init();
    char string_vals[5][20] = { "dilaudid", "piano", "YAa", "marsu", "DzZy" };
    for (i = 0; i < 5; i ++)
    {
        ll_append(pop_end_4, &string_vals[i], STRING);
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
    LL* pop_end_5 = ll_init();
    int val_1 = 69;
    double val_2 = 69.69;
    char val_3 = 'z';
    char val_4[10] = "aaaaaaaaa";
    int val_5 = -30;
    ll_append(pop_end_5, &val_1, INT);
    ll_append(pop_end_5, &val_2, DOUBLE);
    ll_append(pop_end_5, &val_3, CHAR);
    ll_append(pop_end_5, &val_4, STRING);
    ll_append(pop_end_5, &val_5, INT);
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

    /* free memory */
    free(pop_end_1);
    free(pop_end_2);
    free(pop_end_3);
    free(pop_end_4);
    free(pop_end_5);
}

void pop_front_tests()
{
    /* test 1 - integers */
    LL* pop_front_1 = ll_init();
    int i, int_vals[5] = { 69, -1, 20, 15, 0 };
    for (i = 0; i < 5; i++)
    {
        ll_prepend(pop_front_1, &int_vals[i], INT);
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
    LL* pop_front_2 = ll_init();
    double double_vals[5] = { 1.69, -2.22, 3.4, 300.1, 0.3432 };
    for (i = 0; i < 5; i ++)
    {
        ll_prepend(pop_front_2, &double_vals[i], DOUBLE);
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
    LL* pop_front_3 = ll_init();
    char char_vals[5] = "Abba!";
    for (i = 0; i < 5; i ++)
    {
        ll_prepend(pop_front_3, &char_vals[i], CHAR);
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
    LL* pop_front_4 = ll_init();
    char string_vals[5][20] = { "dilaudid", "piano", "YAa", "marsu", "DzZy" };
    for (i = 0; i < 5; i ++)
    {
        ll_prepend(pop_front_4, &string_vals[i], STRING);
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
    LL* pop_front_5 = ll_init();
    int val_1 = 69;
    double val_2 = 69.69;
    char val_3 = 'z';
    char val_4[10] = "aaaaaaaaa";
    int val_5 = -30;
    ll_prepend(pop_front_5, &val_1, INT);
    ll_prepend(pop_front_5, &val_2, DOUBLE);
    ll_prepend(pop_front_5, &val_3, CHAR);
    ll_prepend(pop_front_5, &val_4, STRING);
    ll_prepend(pop_front_5, &val_5, INT);
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

    /* free memory */
    free(pop_front_1);
    free(pop_front_2);
    free(pop_front_3);
    free(pop_front_4);
    free(pop_front_5);
}

void clear_tests()
{
    /* test 1 */
    LL* clear_1 = ll_init();
    int i, int_vals[5] = { 69, -1, 20, 15, 0 };
    for (i = 0; i < 5; i++)
    {
        ll_append(clear_1, &int_vals[i], INT);
    }
    assert(clear_1->count == 5);
    ll_clear(clear_1, true);
    assert(clear_1->count == 0);
    assert(clear_1->head == NULL);
    assert(clear_1->tail == NULL);

    /* test 2 - clearing empty LL should not cause errors */
    LL* clear_2 = ll_init();
    ll_clear(clear_2, true);
    assert(clear_2->count == 0);
    assert(clear_2->head == NULL);
    assert(clear_2->tail == NULL);

    /* test 3 - clearing mixed LL with mixed datatypes */
    LL* clear_3 = ll_init();
    int val_1 = 69;
    double val_2 = 69.69;
    char val_3 = 'z';
    char val_4[10] = "aaaaaaaaa";
    int val_5 = -30;
    ll_prepend(clear_3, &val_1, INT);
    ll_prepend(clear_3, &val_2, DOUBLE);
    ll_prepend(clear_3, &val_3, CHAR);
    ll_prepend(clear_3, &val_4, STRING);
    ll_prepend(clear_3, &val_5, INT);
    assert(clear_3->count == 5);
    ll_clear(clear_3, true);
    assert(clear_3->count == 0);
    assert(clear_3->head == NULL);
    assert(clear_3->tail == NULL);

    /* free memory */
    free(clear_1);
    free(clear_2);
    free(clear_3);
}

void contains_tests()
{
    /* test 1 */
    LL* contains_1 = ll_init();
    int i, int_vals[5] = { 69, -1, 20, 15, 0 };
    for (i = 0; i < 5; i++)
    {
        ll_append(contains_1, &int_vals[i], INT);
    }
    assert(contains_1->count == 5);
    int bad_search_vals[5] = { 68, -2, 21, 14, 1 };
    for (i = 0; i < 5; i++)
    {
        assert(ll_contains(contains_1, &int_vals[i], INT) == true);
        assert(ll_contains(contains_1, &bad_search_vals[i], INT) == false);
    }

    /* test 2 searching empty LL should return false */
    LL* contains_2 = ll_init();
    for (i = 0; i < 5; i++)
    {
        assert(ll_contains(contains_2, &int_vals[i], INT) == false);
        assert(ll_contains(contains_2, &bad_search_vals[i], INT) == false);
    }

    /* test 3 searching for a value that has been removed */
    LL* contains_3 = ll_init();
    for (i = 0; i < 5; i++)
    {
        ll_append(contains_3, &int_vals[i], INT);
    }
    assert(ll_contains(contains_3, &int_vals[0], INT) == true);
    free(ll_pop_front(contains_3));
    assert(ll_contains(contains_3, &int_vals[0], INT) == false);
    
    /* test 4 mixed values */
    LL* contains_4 = ll_init();
    int val_1 = 69;
    double val_2 = 69.69;
    char val_3 = 'z';
    char val_4[10] = "aaaaaaaaa";
    int val_5 = -30;
    ll_append(contains_4, &val_1, INT);
    ll_append(contains_4, &val_2, DOUBLE);
    ll_append(contains_4, &val_3, CHAR);
    ll_append(contains_4, &val_4, STRING);
    ll_append(contains_4, &val_5, INT);
    assert(contains_4->count == 5);
    double bad_doubles[5] = { .2134, 324.3, 2342.22, 0.0034, 21.2 };
    char bad_chars[5] = "SLURM";
    char bad_strings[5][10] = { "dog", "cat", "bike", "guitar", "phone" };

    assert(ll_contains(contains_4, &val_2, DOUBLE) == true);
    for (i = 0; i < 5; i++)
    {
        
        assert(ll_contains(contains_4, &bad_doubles[i], DOUBLE) == false);
        assert(ll_contains(contains_4, &bad_chars[i], CHAR) == false);
        assert(ll_contains(contains_4, &bad_strings[i], STRING) == false);
    }

    /* free memory */
    ll_clear(contains_1, true);
    ll_clear(contains_2, true);
    ll_clear(contains_3, true);
    ll_clear(contains_4, true);
    free(contains_1);
    free(contains_2);
    free(contains_3);
    free(contains_4);
}

void remove_first_tests()
{
    /* test 1 - simple int removals until empty */
    LL* remove_first_1 = ll_init();
    int i, int_vals[5] = { 69, -1, 20, 15, 0 };
    int bad_values[5] = { 68, -2, 21, 14, 1 };
    for (i = 4; i > -1; i--)
    {
        ll_prepend(remove_first_1, &int_vals[i], INT);
    }
    for (i = 0; i < 5; i++)
    {
        assert(ll_remove_first(remove_first_1, &bad_values[i], INT) == false);
    }
    assert(remove_first_1->count == 5);
    assert(ll_remove_first(remove_first_1, &int_vals[2], INT) == true);
    /* LL: { 69, -1, 15, 0 } */
    assert(remove_first_1->count == 4);
    assert(*((int*)remove_first_1->head->next->next->data) == 15);
    assert(ll_remove_first(remove_first_1, &int_vals[4], INT) == true);
    /* LL: { 69, -1, 15 } */
    assert(remove_first_1->count == 3);
    assert(*((int*)remove_first_1->tail->data) == 15);
    assert(ll_remove_first(remove_first_1, &int_vals[1], INT) == true);
    /* LL: { 69, 15 } */
    assert(remove_first_1->count == 2);
    assert(*((int*)remove_first_1->tail->prev->data) == 69);
    assert(ll_remove_first(remove_first_1, &int_vals[3], INT) == true);
    /* LL: { 69 } */
    assert(remove_first_1->count == 1);
    assert(*((int*)remove_first_1->tail->data) == 69);
    assert(*((int*)remove_first_1->head->data) == 69);
    assert(ll_remove_first(remove_first_1, &int_vals[0], INT) == true);
    /* LL: { } */
    assert(remove_first_1->count == 0);
    assert(remove_first_1->head == NULL);
    assert(remove_first_1->tail == NULL);
    assert(ll_remove_first(remove_first_1, &int_vals[0], INT) == false);

    /* test 2 - duplicate values */
    LL* remove_first_2 = ll_init();
    double double_vals[5] = { 69.69, 1.2, 69.69, 69.69, 1.2 };
    double bad_doubles[5] = { 12.3, -34.2, 33.4, 66.4,  345.4 };
    for (i = 4; i > -1; i--)
    {
        ll_prepend(remove_first_2, &double_vals[i], DOUBLE);
    }
    for (i = 0; i < 5; i++)
    {
        assert(ll_remove_first(remove_first_2, &bad_doubles[i], DOUBLE) == false);
    }
    assert(ll_remove_first(remove_first_2, &double_vals[0], DOUBLE) == true);
    /* { 1.2, 69.69, 69.69, 1.2 } */
    assert(remove_first_2->count == 4);
    assert(*((double*)remove_first_2->head->data) == 1.2);
    assert(ll_remove_first(remove_first_2, &double_vals[0], DOUBLE) == true);
    assert(ll_remove_first(remove_first_2, &double_vals[0], DOUBLE) == true);
    assert(remove_first_2->count == 2);
    assert(*((double*)remove_first_2->head->next->data) == 1.2);
    assert(*((double*)remove_first_2->tail->prev->data) == 1.2);
    assert(ll_remove_first(remove_first_2, &double_vals[1], DOUBLE) == true);
    assert(ll_remove_first(remove_first_2, &double_vals[1], DOUBLE) == true);
    assert(remove_first_2->count == 0);
    assert(remove_first_2->head == NULL);
    assert(remove_first_2->tail == NULL);

    /* test 3 - mixed datatypes */
    LL* remove_first_3 = ll_init();
    char char_vals[5] = "Abba!";
    char string_vals[5][20] = { "dilaudid", "piano", "YAa", "marsu", "DzZy" };
    for (i = 0; i < 5; i++)
    {
        ll_append(remove_first_3, &int_vals[i], INT);
        ll_append(remove_first_3, &double_vals[i], DOUBLE);
        ll_append(remove_first_3, &char_vals[i], CHAR);
        ll_append(remove_first_3, &string_vals[i], STRING);
    }
    /* { 69, 69.69, 'A', "dilaudid", -1, 1.2, 'b', "piano", 20, 69.69, 'b',
     * "YAa", 15, 69.69, 'a', "marsu", 0, 1.2, '!', "DzZy" } */
    assert(remove_first_3->count == 20);
    assert(ll_remove_first(remove_first_3, &char_vals[1], CHAR) == true);
    assert(ll_contains(remove_first_3, &char_vals[1], CHAR) == true);
    assert(remove_first_3->count == 19);
    /* { 69, 69.69, 'A', "dilaudid", -1, 1.2, "piano", 20, 69.69, 'b',
     * "YAa", 15, 69.69, 'a', "marsu", 0, 1.2, '!', "DzZy" } */
    assert(ll_remove_first(remove_first_3, &char_vals[1], CHAR) == true);
    assert(remove_first_3->count == 18);
    /* { 69, 69.69, 'A', "dilaudid", -1, 1.2, "piano", 20, 69.69,
     * "YAa", 15, 69.69, 'a', "marsu", 0, 1.2, '!', "DzZy" } */
    assert(ll_contains(remove_first_3, &char_vals[1], CHAR) == false);
    assert(ll_remove_first(remove_first_3, &string_vals[4], STRING) == true);
    assert(remove_first_3->count == 17);
    /* { 69, 69.69, 'A', "dilaudid", -1, 1.2, "piano", 20, 69.69,
     * "YAa", 15, 69.69, 'a', "marsu", 0, 1.2, '!' } */
    assert(*((char*)remove_first_3->tail->data) == '!');
    assert(ll_remove_first(remove_first_3, &double_vals[1], DOUBLE) == true);
    assert(ll_remove_first(remove_first_3, &double_vals[1], DOUBLE) == true);
    assert(remove_first_3->count == 15);
    assert(ll_contains(remove_first_3, &double_vals[1], DOUBLE) == false);

    /* free memory */
    ll_clear(remove_first_1, true);
    ll_clear(remove_first_2, true);
    ll_clear(remove_first_3, true);
    free(remove_first_1);
    free(remove_first_2);
    free(remove_first_3);
}

void remove_index_tests()
{
    int i, int_vals[5] = { 69, -1, 20, 15, 0 };
    double double_vals[5] = { 69.69, 1.2, 69.69, 69.69, 1.2 };
    char char_vals[5] = "Abba!";
    char string_vals[5][20] = { "dilaudid", "piano", "YAa", "marsu", "DzZy" };

    /* test 1 - simple int removals */
    LL* remove_index_1 = ll_init();
    for (i = 0; i < 5; i++)
    {
        ll_append(remove_index_1, &int_vals[i], INT);
    }
    assert(ll_remove_index(remove_index_1, 2) == true);
    assert(*((int*)remove_index_1->head->next->next->data) == 15);
    assert(remove_index_1->count == 4);
    assert(ll_remove_index(remove_index_1, 0) == true);
    assert(remove_index_1->count == 3);
    assert(*((int*)remove_index_1->head->data) == -1);
    assert(ll_remove_index(remove_index_1, 0) == true);
    assert(ll_remove_index(remove_index_1, 0) == true);
    assert(remove_index_1->count == 1);
    assert(*((int*)remove_index_1->head->data) == 0);
    assert(*((int*)remove_index_1->tail->data) == 0);
    assert(ll_remove_index(remove_index_1, 0) == true);
    assert(ll_remove_index(remove_index_1, 0) == false);
    assert(remove_index_1->count == 0);

    /* test 2 - simple int removals */
    LL* remove_index_2 = ll_init();
    for (i = 0; i < 5; i++)
    {
        ll_append(remove_index_2, &int_vals[i], INT);
        ll_append(remove_index_2, &double_vals[i], DOUBLE);
        ll_append(remove_index_2, &char_vals[i], CHAR);
        ll_append(remove_index_2, &string_vals[i], STRING);
    }
    /* { 69, 69.69, 'A', "dilaudid", -1, 1.2, 'b', "piano", 20, 69.69, 'b',
     * "YAa", 15, 69.69, 'a', "marsu", 0, 1.2, '!', "DzZy" } */
    for (i = 0; i < 15; i++)
    {
        assert(ll_remove_index(remove_index_2, remove_index_2->count - 1)
                == true);
    }
    /* { 69, 69.69, 'A', "dilaudid", -1 } */
    assert(remove_index_2->count == 5);
    assert(*((int*)remove_index_2->head->data) == 69);
    assert(*((double*)remove_index_2->head->next->data) == 69.69);
    assert(*((char*)remove_index_2->head->next->next->data) == 'A');
    assert(strcmp(((char*)remove_index_2->tail->prev->data), "dilaudid") == 0);
    assert(*((int*)remove_index_2->tail->data) == -1);

    ll_clear(remove_index_1, true);
    ll_clear(remove_index_2, true);
    free(remove_index_1);
    free(remove_index_2);

}

void splice_tests()
{
    int i, int_vals[5] = { 69, -1, 20, 15, 0 };
    double double_vals[5] = { 69.69, 1.2, 69.69, 69.69, 1.2 };
    char char_vals[5] = "Abba!";
    char string_vals[5][20] = { "dilaudid", "piano", "YAa", "marsu", "DzZy" };

    /* test 1 */
    LL* splice_1 = ll_init();
    for (i = 0; i < 5; i++)
    {
        ll_append(splice_1, &char_vals[i], CHAR);
    }
    /* { 'A', 'b', 'b', 'a', '!' } */
    assert(ll_splice(splice_1, &int_vals[0], INT, 0) == true);
    /* { 69, 'A', 'b', 'b', 'a', '!' } */
    assert(splice_1->count == 6);
    assert(*((int*)splice_1->head->data) == 69);
    assert(ll_splice(splice_1, &double_vals[0], DOUBLE, 2) == true);
    /* { 69, 'A', 69.69, 'b', 'b', 'a', '!' } */
    assert(splice_1->count == 7);
    assert(*((double*)splice_1->head->next->next->data) == 69.69);
    assert(ll_splice(splice_1, &string_vals[0], STRING, 6) == true);
    /* { 69, 'A', 69.69, 'b', 'b', 'a', "dilaudid", '!' } */
    assert(splice_1->count == 8);
    assert(strcmp(((char*)splice_1->tail->prev->data), "dilaudid") == 0);
    assert(ll_splice(splice_1, &string_vals[0], STRING, 8) == false);
    
    /* test 2 */
    LL* splice_2 = ll_init();
    assert(ll_splice(splice_2, &string_vals[0], STRING, 0) == true);
    /* { "dilaudid" } */
    assert(ll_splice(splice_2, &double_vals[0], DOUBLE, 0) == true);
    /* { 69.69, "dilaudid" } */
    assert(ll_splice(splice_2, &int_vals[0], INT, 1) == true);
    /* { 69.69, 69, "dilaudid" } */
    assert(ll_splice(splice_2, &int_vals[0], INT, 0) == true);
    /* { 69, 69.69, 69, "dilaudid" } */
    assert(ll_splice(splice_2, &string_vals[0], STRING, 0) == true);
    /* { "dilaudid", 69, 69.69, 69, "dilaudid" } */
    assert(splice_2->count == 5);
    assert(strcmp(((char*)splice_2->tail->data), "dilaudid") == 0);
    assert(strcmp(((char*)splice_2->head->data), "dilaudid") == 0);
    assert(*((int*)splice_2->head->next->data) == 69);
    assert(*((int*)splice_2->tail->prev->data) == 69);
    assert(*((double*)splice_2->tail->prev->prev->data) == 69.69);
    
    /* free memory */
    ll_clear(splice_1, true);
    ll_clear(splice_2, true);
    free(splice_1);
    free(splice_2);
}

void get_tests()
{
    int i, int_vals[5] = { 69, -1, 20, 15, 0 };
    double double_vals[5] = { 69.69, 1.2, 69.69, 69.69, 1.2 };
    char char_vals[5] = "Abba!";
    char string_vals[5][20] = { "dilaudid", "piano", "YAa", "marsu", "DzZy" };

    LL* get_1 = ll_init();
    for (i = 0; i < 5; i++)
    {
        ll_append(get_1, &int_vals[i], INT);
        ll_append(get_1, &double_vals[i], DOUBLE);
        ll_append(get_1, &char_vals[i], CHAR);
        ll_append(get_1, &string_vals[i], STRING);
    }
    /* { 69, 69.69, 'A', "dilaudid", -1, 1.2, 'b', "piano", 20, 69.69, 'b',
     * "YAa", 15, 69.69, 'a', "marsu", 0, 1.2, '!', "DzZy" } */
    assert(*((int*)ll_get(get_1, 0)) == 69);
    assert(*((double*)ll_get(get_1, 1)) == 69.69);
    assert(*((char*)ll_get(get_1, 2)) == 'A');
    assert(strcmp(((char*)ll_get(get_1, 3)), "dilaudid") == 0);
    assert(strcmp(((char*)ll_get(get_1, 19)), "DzZy") == 0);
    assert(*((char*)ll_get(get_1, 18)) == '!');
    assert(ll_get(get_1, 20) == NULL);

    ll_clear(get_1, true);
    free(get_1);
}

int main(void)
{
    init_tests();
    printf("All gll_init tests passed!\n");
    append_tests();
    printf("All gll_append tests passed!\n");
    prepend_tests();
    printf("All gll_prepend tests passed!\n");
    pop_end_tests();
    printf("All gll_pop_end tests passed!\n");
    pop_front_tests();
    printf("All gll_pop_front tests passed!\n");
    clear_tests();
    printf("All gll_clear tests passed!\n");
    contains_tests();
    printf("All gll_contains tests passed!\n");
    remove_first_tests();
    printf("All gll_remove_first tests passed!\n");
    remove_index_tests();
    printf("All gll_remove_index tests passed!\n");
    splice_tests();
    printf("All gll_splice tests passed!\n");
    get_tests();
    printf("All gll_get tests passed!\n");
    return 0;
}
