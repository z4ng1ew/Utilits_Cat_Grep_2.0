#ifndef S21_CAT_H
#define S21_CAT_H


#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    bool b;
    bool e;
    bool n;
    bool s;
    bool t;
    bool v;
} Opt;

const struct option long_options[] = {
    {"number-nonblank", 0, 0, 'b'},
    {"number", 0, 0, 'n'},
    {"squeeze-blank", 0, 0, 's'},
    {0, 0, 0, 0}
};

void open_and_read_file(const Opt short_opt, const char* filename);
void display_file_with_flags(FILE* file, const Opt short_opt);
bool verify_options(int num_comd_line_arg, char* array_strings_comd[], Opt* short_opt);



#endif  // S21_CAT_H
