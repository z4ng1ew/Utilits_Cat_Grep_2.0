COMPILE=gcc
COPT=-Wall -Wextra -Werror -std=c11 -g
DIR=My_Auto-tests

all: rebuild

s21_grep:
	$(COMPILE) $(COPT) s21_grep.c -o s21_grep

test:
	$(COMPILE) $(COPT) $(DIR)/s21_grep_test.c $(DIR)/test_utils.c -o s21_grep_test

run:
	./s21_grep_test 2 v

rebuild: clean s21_grep test

clean:
	rm -rf s21_grep test
