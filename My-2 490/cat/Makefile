File_call = cat
Options = -Wall -Werror -Wextra -std=c11 -D_POSIX_C_SOURCE=200809L

all: s21_$(File_call)

s21_$(File_call): clean
	gcc $(Options) s21_$(File_call).c -o s21_$(File_call) -g -std=c11

clean:
	rm -rf *.out s21_$(File_call)

style:
	clang-format -style=google -n *.c *.h

format:
	clang-format -style=google -i *.c *.h
