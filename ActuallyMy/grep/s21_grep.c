#include "s21_grep.h"

int main(int ac, char *av[]) {
    Letter_opt CmdFlags;
    Retrieval_Config GrepParams;
    char *pattern;

    initialize_and_process(ac, av, &CmdFlags, &GrepParams, &pattern);

    if (GrepParams.has_errors) {
        fprintf(stderr, "Распишите команду по структуре: grep [ПАРАМЕТР]… ШАБЛОНЫ [ФАЙЛ]…\n");
    }

    return GrepParams.has_errors;
}

void initialize_and_process(int ac, char *av[], Letter_opt *CmdFlags, Retrieval_Config *GrepParams, char **pattern) {
    *pattern = (char *)calloc(SIZE, sizeof(char));
    *CmdFlags = (Letter_opt){false};
    *GrepParams = (Retrieval_Config){false, false, 0, 0};
    if (ac < 2) {
        fprintf(stderr, "Укажите флаг\n");
        GrepParams->has_errors = true;
    } else {
        analyze_cmd_arg(ac, av, CmdFlags, GrepParams, pattern);
        if (!GrepParams->has_errors) {
            if (!CmdFlags->f_fl && !CmdFlags->e_fl) {
                prepare_and_add_pattern(pattern, av[optind++]);
            }
            if (ac - optind > 1) {
                GrepParams->processing_a_lot_of_files = true;
            }
            for (int i = optind; i < ac; i++) {
                scan_file(*CmdFlags, GrepParams, av[i], *pattern);
            }
        }
    }
    free(*pattern);
}


void initialize_flags(Letter_opt *CmdFlags) {
  *CmdFlags = (Letter_opt){false};
}

void process_flag_e(Letter_opt *CmdFlags, char **pattern, char *optarg) {
  CmdFlags->e_fl = true;
  prepare_and_add_pattern(pattern, optarg);
}

void process_flag_f(Letter_opt *CmdFlags, Retrieval_Config *settings, char **pattern, char *optarg) {
  CmdFlags->f_fl = true;
  settings->processed_document_count++;
  import_patterns_from_file(settings, pattern, optarg);
}

void set_flags(int option, Letter_opt *CmdFlags, Retrieval_Config *settings, char **pattern) {
  switch (option) {
    case 'e':
      process_flag_e(CmdFlags, pattern, optarg);
      break;
    case 'i':
      CmdFlags->i_fl = true;
      break;
    case 'v':
      CmdFlags->v_fl = true;
      break;
    case 'c':
      CmdFlags->c_fl = true;
      break;
    case 'l':
      CmdFlags->l_fl = true;
      break;
    case 'n':
      CmdFlags->n_fl = true;
      break;
    case 'h':
      CmdFlags->h_fl = true;
      break;
    case 's':
      CmdFlags->s_fl = true;
      break;
    case 'f':
      process_flag_f(CmdFlags, settings, pattern, optarg);
      break;
    case 'o':
      CmdFlags->o_fl = true;
      break;
    default:
      settings->has_errors = true;
  }
}

void finalize_flags(Letter_opt *CmdFlags) {
  if (CmdFlags->l_fl) {
    CmdFlags->c_fl = false;
    CmdFlags->n_fl = false;
    CmdFlags->o_fl = false;
  }

  if (CmdFlags->c_fl) {
    CmdFlags->n_fl = false;
    CmdFlags->o_fl = false;
  }
}

void check_for_errors(int ac, char *av[], Retrieval_Config *settings) {
  if (optind >= ac || av[optind][0] == '-' || strlen(av[optind]) == 0) {
    settings->has_errors = true;
  }
}

void analyze_cmd_arg(int ac, char *av[], Letter_opt *CmdFlags, Retrieval_Config *settings, char **pattern) {
  initialize_flags(CmdFlags);

  int option;
  while ((option = getopt(ac, av, "e:ivclnhsf:o")) != -1 && !(settings->has_errors)) {
    set_flags(option, CmdFlags, settings, pattern);
  }

  finalize_flags(CmdFlags);
  check_for_errors(ac, av, settings);
}

void import_patterns_from_file(Retrieval_Config *GrepParams, char **pattern, char *optarg) {
  FILE *file = fopen(optarg, "r");

  if (file != NULL) {
    char *line = NULL;
    size_t length = 0;

    while ((getline(&line, &length, file)) != -1) {
      prepare_and_add_pattern(pattern, line);
    }

    free(line);
    fclose(file);
  } else {
    GrepParams->has_errors = true;
    fprintf(stderr, "s21_grep: %s: Такого файла или каталога не существует\n", optarg);
  }
}

void prepare_and_add_pattern(char **pattern, char *line) {
  char *copy_line = malloc(strlen(line) + 10);
  strcpy(copy_line, line);

  if (copy_line[0] == '\0' || copy_line[0] == '\n') {
    strcpy(copy_line, "$");
  }

  remove_trailing_newline(&copy_line);

  static size_t buffer = SIZE;
  while (strlen(*pattern) + strlen(line) + 10 > buffer) {
    buffer *= 2;
    *pattern = (char *)realloc(*pattern, buffer * sizeof(char));
  }

  sprintf(*pattern + strlen(*pattern), "%s\\(%s\\)", *pattern[0] ? "\\|" : "", copy_line);

  free(copy_line);
}

void remove_trailing_newline(char **line) {
  int last_index = (int)strlen(*line) - 1;
  if ((*line)[last_index] == '\n') (*line)[last_index] = '\0';
}

void scan_file(Letter_opt CmdFlags, Retrieval_Config *GrepParams, const char *filename, char *pattern) {
  FILE *file = fopen(filename, "r");

  if (file != NULL) {
    regex_t regex;

    validate_and_compile_regex(CmdFlags, GrepParams, &regex, pattern);

    if (!GrepParams->has_errors && !(CmdFlags.o_fl && CmdFlags.v_fl)) {
      if (CmdFlags.o_fl) {
        handle_opt_o(CmdFlags, GrepParams, file, &regex, filename);
      } else {
        handle_matching_regex(CmdFlags, GrepParams, file, &regex, filename);
      }
    }

    regfree(&regex);
    fclose(file);
  } else if (!CmdFlags.s_fl) {
    fprintf(stderr, "s21_grep: %s: Такого файла или каталога не существует\n", filename);
  }
}

void validate_and_compile_regex(Letter_opt CmdFlags, Retrieval_Config *GrepParams, regex_t *regex, char *pattern) {
  if (regcomp(regex, pattern, CmdFlags.i_fl ? REG_ICASE : 0)) {
    GrepParams->has_errors = true;
    fprintf(stderr, "Ошибка при компиляции -- regex\n");
  }
}

void handle_opt_o(Letter_opt CmdFlags, Retrieval_Config *GrepParams, FILE *file, regex_t *regex, const char *filename) {
  regmatch_t match;
  char *line = NULL;
  size_t length = 0;
  int line_count = 0, status;

  while ((getline(&line, &length, file)) != -1) {
    line_count++;

    remove_trailing_newline(&line);

    char *copy_line = strdup(line);
    char *original_copy_line = copy_line;

    while (((status = regexec(regex, copy_line, 1, &match, REG_NOTEOL)) == 0) && strlen(copy_line)) {
      if (match.rm_so == match.rm_eo) {
        copy_line++;
        continue;
      }

      if (GrepParams->processing_a_lot_of_files && !CmdFlags.h_fl) printf("%s:", filename);
      if (CmdFlags.n_fl) printf("%d:", line_count);
      printf("%.*s\n", (int)match.rm_eo - (int)match.rm_so, copy_line + match.rm_so);

      copy_line += match.rm_eo;
    }

    free(original_copy_line);
    original_copy_line = NULL;
  }

  free(line);
  line = NULL;
}

void handle_matching_regex(Letter_opt CmdFlags, Retrieval_Config *GrepParams, FILE *file, regex_t *regex, const char *filename) {
  char *line = NULL;
  size_t length = 0;
  int line_count = 0, match_count = 0;

  while ((getline(&line, &length, file)) != -1) {
    line_count++;

    remove_trailing_newline(&line);

    int status = regexec(regex, line, 0, NULL, 0);

    if (!status ^ CmdFlags.v_fl) {
      if (CmdFlags.l_fl) {
        printf("%s\n", filename);
        break;
      }

      match_count++;

      if (!CmdFlags.c_fl) {
        if (GrepParams->processing_a_lot_of_files && !CmdFlags.h_fl) printf("%s:", filename);
        if (CmdFlags.n_fl) printf("%d:", line_count);
        printf("%s\n", line);
      }
    }
  }

  if (CmdFlags.c_fl) {
    if (GrepParams->processing_a_lot_of_files && !CmdFlags.h_fl) printf("%s:", filename);
    printf("%d\n", match_count);
  }

  free(line);
  line = NULL;
}