COMPILE=gcc
COPT=-Wall -Wextra -Werror -std=c11 -g


all: rebuild

s21_cat:
	$(COMPILE) $(COPT) s21_cat.c -o s21_cat


test:
	./сat_check.sh

rebuild: clean s21_cat

clean:
	rm -rf s21_cat



style:
	clang-format -style=google -n *.c *.h



format:
	clang-format -style=google -i *.c *.h
