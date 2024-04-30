#include <stdio.h>
#include <stddef.h>
#include <inttypes.h>
#include <stdbool.h>

#include "hash_table.h"
#include "util.h"
#include "macro.h"
#include "munit/munit.h"

static MunitResult
test_ht_insert_get(const MunitParameter params[], void * data)
{
	char* value_test;
    
    h_table* table = ht_create(4);
    munit_assert_true(table->capacity == 4);

    ht_insert(table, "Russia", "Moscow");
	value_test = ht_get(table, "Russia");
    munit_assert_string_equal(value_test, "Moscow");

	ht_insert(table, "Italy", "Rome");
	value_test = ht_get(table, "Italy");
    munit_assert_string_equal(value_test, "Rome");

	munit_assert_true(ht_size(table) == 2);

	ht_free(table);
    return MUNIT_OK;
}

static MunitResult
test_ht_delete(const MunitParameter params[], void * data) 
{
	h_table* table = ht_create(6);
    munit_assert_true(table->capacity == 6);

    ht_insert(table, "Russia", "Moscow");
	ht_insert(table, "Italy", "Rome");
	ht_insert(table, "UK", "London");

	munit_assert_true(ht_get(table, "Italy") == "Rome");
	munit_assert_true(ht_size(table) == 3);

	ht_delete(table, "Italy");
	munit_assert_true(ht_get(table, "Italy") == NULL);
	ht_delete(table, "UK");
	munit_assert_ptr(ht_get(table, "UK"), ==, NULL);

	munit_assert_true(ht_size(table) == 1);
	
	ht_free(table);
	return MUNIT_OK;
}

static MunitResult
test_ht_resize(const MunitParameter params[], void * data) 
{
	h_table* table = ht_create(4);
    munit_assert_true(table->capacity == 4);

    ht_insert(table, "Russia", "Moscow");
	ht_insert(table, "Italy", "Rome");
	printf("\n\nBefore resize:");
	ht_print(table);
	ht_insert(table, "UK", "London");
	ht_insert(table, "Spain", "Madrid");
	ht_insert(table, "Canada", "Ottawa");
	printf("After resize:");
	ht_print(table);

	munit_assert_true(table->capacity == 8);
	munit_assert_true(ht_size(table) == 5);
	
	ht_free(table);
	return MUNIT_OK;
}

static MunitResult
test_ht_ins_del(const MunitParameter params[], void * data) 
{
	char* value_test;

	h_table* table = ht_create(4);
    munit_assert_true(table->capacity == 4);

    ht_insert(table, "Russia", "Moscow");
	ht_insert(table, "Italy", "Rome");
	munit_assert_true(ht_size(table) == 2);

	value_test = ht_get(table, "Russia");
    munit_assert_string_equal(value_test, "Moscow");

	ht_delete(table, "Russia");
	ht_delete(table, "Italy");
	munit_assert_true(ht_size(table) == 0);

    munit_assert_true(ht_get(table, "Russia") == NULL);
	munit_assert_true(ht_get(table, "Italy") == NULL);

	ht_insert(table, "Russia", "Moscow");
	ht_insert(table, "Italy", "Rome");
	munit_assert_true(ht_size(table) == 2);
	munit_assert_string_equal(value_test, "Moscow");

	ht_free(table);
    return MUNIT_OK;
}

#define TEST_ITEM(func) {#func, func, NULL, NULL, MUNIT_TEST_OPTION_NONE }

static MunitTest test_suite_tests[] = {
	TEST_ITEM(test_ht_insert_get),
	TEST_ITEM(test_ht_delete),
	TEST_ITEM(test_ht_resize),
	TEST_ITEM(test_ht_ins_del),
	{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
	(char *) "",
	test_suite_tests,
	NULL,
	1,
	MUNIT_SUITE_OPTION_NONE
};
int
main(int argc, const char *argv[])
{
	munit_suite_main(&test_suite, (void *) "vector_test", argc, (char * const*) argv);
	return 0;
}