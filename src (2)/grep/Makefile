COMPILE=gcc
COPT=-Wall -Wextra -Werror -std=c11 -g

all: rebuild

s21_grep:
	$(COMPILE) $(COPT) s21_grep.c -o s21_grep

test:
	./run_tests.sh
	
	
rebuild: clean s21_grep 

clean:
	rm -rf s21_grep 


style:
	clang-format -style=google -n *.c *.h

format:
	clang-format -style=google -i *.c *.h
