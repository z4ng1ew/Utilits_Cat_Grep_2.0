EXIT_COMMAND=gcc
FL=-Wall -Wextra -Werror -std=c17 -g -D_POSIX_C_SOURCE=200809L

all: rebuild

s21_grep:
	$(EXIT_COMMAND) $(FL) s21_grep.c -o s21_grep

test:
	./Auto_tests_for_grep_s21.sh

style:
	clang-format -style=google -n *.c *.h

format:
	clang-format -style=google -i *.c *.h
	
rebuild: clean s21_grep 

clean:
	rm -rf s21_grep 
