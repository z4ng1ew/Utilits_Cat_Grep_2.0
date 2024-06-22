EXIT_COMMAND=gcc
FL=-Wall -Wextra -Werror -std=c17 -g -D_POSIX_C_SOURCE=200809L

all: rebuild

s21_cat:
	$(EXIT_COMMAND) $(FL) s21_cat.c -o s21_cat

style:
	clang-format -style=google -n *.c *.h


format:
	clang-format -style=google -i *.c *.h

test:
	./Auto_tests_for_cat_s21.sh

rebuild: clean s21_cat

clean:
	rm -rf s21_cat
