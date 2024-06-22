#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


typedef struct {
    bool fl_b;
    bool fl_e;
    bool fl_n;
    bool fl_s;
    bool fl_t;
    bool fl_v;
} Struct_singl_lett_opt;


const struct option long_options[] = {
    {"number-nonblank", no_argument, NULL, 'b'},
    {"number", no_argument, NULL, 'n'},
    {"squeeze-blank", no_argument, NULL, 's'},  
    {NULL, 0, NULL, 0}  
};



void handle_file(Struct_singl_lett_opt single_letter_opt, const char* filename);
void print_file_with_options(FILE* file, const Struct_singl_lett_opt single_letter_opt);
bool check_options(int num_args, char* av[], Struct_singl_lett_opt* single_letter_opt); 



