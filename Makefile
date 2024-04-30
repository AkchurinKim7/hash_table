unittest_obj=munit/munit.o

CFLAGS=-Wall -ggdb

hash_table_test: util.o hash_table.o hash_table_test.o $(unittest_obj)
	$(CC) $^ -o $@

clean:
	rm hash_table_test $(unittest_obj) *.o

test: hash_table_test
	./hash_table_test