#define _GNU_SOURCE
#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 370

typedef struct {
  bool e;
  bool i;
  bool v;
  bool c;
  bool l;
  bool n;
  bool h;
  bool s;
  bool f;
  bool o;
} Opt;

typedef struct {
  bool many_files;
  bool bug;
  int search_word;
  int number_of_documents;
} SearchSettings;

void verify_options(int num_comd_line_arg, char *array_strings_comd[], Opt *fl,
                    SearchSettings *params, char **pattern);
void read_patterns_from_file(SearchSettings *params, char **pattern,
                             char *optarg);
void format_and_append_pattern(char **pattern, char *line);
void delete_newline_character(char **line);
void search_in_file(Opt fl, SearchSettings *params, const char *filename,
                    char *pattern);
void regex_compile(Opt fl, SearchSettings *params, regex_t *regex,
                   char *pattern);
void process_flag_o(Opt fl, SearchSettings *params, FILE *file, regex_t *regex,
                    const char *filename);
void process_file_lines(Opt fl, SearchSettings *params, FILE *file,
                        regex_t *regex, const char *filename);