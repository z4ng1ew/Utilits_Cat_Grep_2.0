Some_File = grep
Opt = -Wall -Werror -Wextra -std=c11 -D_POSIX_C_SOURCE=200809L

all: s21_$(Some_File)

s21_$(Some_File): clean
	gcc $(Opt) s21_$(Some_File).c -o s21_$(Some_File) -g -std=c11

clean:
	rm -rf *.out s21_$(Some_File)

style:
	clang-format -style=google -n *.c *.h

format:
	clang-format -style=google -i *.c *.h

