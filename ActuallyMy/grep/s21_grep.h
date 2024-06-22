#define _GNU_SOURCE
#include <stdbool.h>
#include <regex.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 400

typedef struct {
  bool e_fl; 
  bool i_fl; 
  bool v_fl; 
  bool c_fl; 
  bool l_fl; 
  bool n_fl; 
  bool h_fl; 
  bool s_fl; 
  bool f_fl; 
  bool o_fl;
} Letter_opt;

typedef struct {
  bool processing_a_lot_of_files;
  bool has_errors;
  int retrieval_query; 
  int processed_document_count;
} Retrieval_Config;

void analyze_cmd_arg(int ac, char *av[], Letter_opt *CmdFlags, Retrieval_Config *params, char **pattern);
void import_patterns_from_file(Retrieval_Config *params, char **pattern, char *optarg);
void prepare_and_add_pattern(char **pattern, char *line);
void remove_trailing_newline(char **line);
void scan_file(Letter_opt CmdFlags, Retrieval_Config *params, const char *filename, char *pattern);
void validate_and_compile_regex(Letter_opt CmdFlags, Retrieval_Config *params, regex_t *regex, char *pattern);
void handle_opt_o(Letter_opt CmdFlags, Retrieval_Config *params, FILE *file, regex_t *regex, const char *filename);
void handle_matching_regex(Letter_opt CmdFlags, Retrieval_Config *params, FILE *file, regex_t *regex, const char *filename);