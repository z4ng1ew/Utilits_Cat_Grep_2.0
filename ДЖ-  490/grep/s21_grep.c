#include "s21_grep.h"

void initialize(Opt *fl, SearchSettings *ExamplSearchSettings, char **pattern) {
  *pattern = (char *)calloc(SIZE, sizeof(char));
  *fl = (Opt){false};
  *ExamplSearchSettings = (SearchSettings){false, false, 0, 0};
}

void check_arguments(int num_comd_line_arg, SearchSettings *ExamplSearchSettings) {
  if (num_comd_line_arg < 2) {
    fprintf(stderr, "Не указаны опции\n");
    ExamplSearchSettings->bug = true;
  }
}

void handle_pattern(char **array_strings_comd, Opt *fl, char **pattern) {
  if (!fl->f && !fl->e) {
    format_and_append_pattern(pattern, array_strings_comd[optind++]);
  }
}

void process_files(int num_comd_line_arg, char **array_strings_comd, Opt fl, SearchSettings *ExamplSearchSettings, char *pattern) {
  if (num_comd_line_arg - optind > 1) ExamplSearchSettings->many_files = true;

  for (int i = optind; i < num_comd_line_arg; i++) {
    search_in_file(fl, ExamplSearchSettings, array_strings_comd[i], pattern);
  }
}

int main(int num_comd_line_arg, char *array_strings_comd[]) {
  Opt fl;
  SearchSettings ExamplSearchSettings;
  char *pattern;

  initialize(&fl, &ExamplSearchSettings, &pattern);
  check_arguments(num_comd_line_arg, &ExamplSearchSettings);

  if (!ExamplSearchSettings.bug) {
    verify_options(num_comd_line_arg, array_strings_comd, &fl, &ExamplSearchSettings, &pattern);
  }

  if (!ExamplSearchSettings.bug) {
    handle_pattern(array_strings_comd, &fl, &pattern);
    process_files(num_comd_line_arg, array_strings_comd, fl, &ExamplSearchSettings, pattern);
  } else {
    fprintf(stderr, "Использование: grep [ПАРАМЕТР]… ШАБЛОНЫ [ФАЙЛ]…\n");
  }

  free(pattern);
  return ExamplSearchSettings.bug;
}

void initialize_flags(Opt *fl) {
  *fl = (Opt){false};
}

void process_flag_e(Opt *fl, char **pattern, char *optarg) {
  fl->e = true;
  format_and_append_pattern(pattern, optarg);
}

void process_flag_f(Opt *fl, SearchSettings *settings, char **pattern, char *optarg) {
  fl->f = true;
  settings->number_of_documents++;
  read_patterns_from_file(settings, pattern, optarg);
}

void set_flags(int option, Opt *fl, SearchSettings *settings, char **pattern) {
  switch (option) {
    case 'e':
      process_flag_e(fl, pattern, optarg);
      break;
    case 'i':
      fl->i = true;
      break;
    case 'v':
      fl->v = true;
      break;
    case 'c':
      fl->c = true;
      break;
    case 'l':
      fl->l = true;
      break;
    case 'n':
      fl->n = true;
      break;
    case 'h':
      fl->h = true;
      break;
    case 's':
      fl->s = true;
      break;
    case 'f':
      process_flag_f(fl, settings, pattern, optarg);
      break;
    case 'o':
      fl->o = true;
      break;
    default:
      settings->bug = true;
  }
}

void finalize_flags(Opt *fl) {
  if (fl->l) {
    fl->c = false;
    fl->n = false;
    fl->o = false;
  }

  if (fl->c) {
    fl->n = false;
    fl->o = false;
  }
}

void check_for_errors(int num_comd_line_arg, char *array_strings_comd[], SearchSettings *settings) {
  if (optind >= num_comd_line_arg || array_strings_comd[optind][0] == '-' || strlen(array_strings_comd[optind]) == 0) {
    settings->bug = true;
  }
}

void verify_options(int num_comd_line_arg, char *array_strings_comd[], Opt *fl, SearchSettings *settings, char **pattern) {
  initialize_flags(fl);

  int option;
  while ((option = getopt(num_comd_line_arg, array_strings_comd, "e:ivclnhsf:o")) != -1 && !(settings->bug)) {
    set_flags(option, fl, settings, pattern);
  }

  finalize_flags(fl);
  check_for_errors(num_comd_line_arg, array_strings_comd, settings);
}

void read_patterns_from_file(SearchSettings *ExamplSearchSettings, char **pattern, char *optarg) {
  FILE *file = fopen(optarg, "r");

  if (file != NULL) {
    char *line = NULL;
    size_t length = 0;

    while ((getline(&line, &length, file)) != -1) {
      format_and_append_pattern(pattern, line);
    }

    free(line);
    fclose(file);
  } else {
    ExamplSearchSettings->bug = true;
    fprintf(stderr, "s21_grep: %s: Нет такого файла или каталога\n", optarg);
  }
}

void format_and_append_pattern(char **pattern, char *line) {
  char *copy_line = malloc(strlen(line) + 10);
  strcpy(copy_line, line);

  if (copy_line[0] == '\0' || copy_line[0] == '\n') {
    strcpy(copy_line, "$");
  }

  delete_newline_character(&copy_line);

  static size_t buffer = SIZE;
  while (strlen(*pattern) + strlen(line) + 10 > buffer) {
    buffer *= 2;
    *pattern = (char *)realloc(*pattern, buffer * sizeof(char));
  }

  sprintf(*pattern + strlen(*pattern), "%s\\(%s\\)", *pattern[0] ? "\\|" : "", copy_line);

  free(copy_line);
}

void delete_newline_character(char **line) {
  int last_index = (int)strlen(*line) - 1;
  if ((*line)[last_index] == '\n') (*line)[last_index] = '\0';
}

void search_in_file(Opt fl, SearchSettings *ExamplSearchSettings, const char *filename, char *pattern) {
  FILE *file = fopen(filename, "r");

  if (file != NULL) {
    regex_t regex;

    regex_compile(fl, ExamplSearchSettings, &regex, pattern);

    if (!ExamplSearchSettings->bug && !(fl.o && fl.v)) {
      if (fl.o) {
        process_flag_o(fl, ExamplSearchSettings, file, &regex, filename);
      } else {
        process_file_lines(fl, ExamplSearchSettings, file, &regex, filename);
      }
    }

    regfree(&regex);
    fclose(file);
  } else if (!fl.s) {
    fprintf(stderr, "s21_grep: %s: Нет такого файла или каталога\n", filename);
  }
}

void regex_compile(Opt fl, SearchSettings *ExamplSearchSettings, regex_t *regex, char *pattern) {
  if (regcomp(regex, pattern, fl.i ? REG_ICASE : 0)) {
    ExamplSearchSettings->bug = true;
    fprintf(stderr, "Error compiling regex\n");
  }
}

void process_flag_o(Opt fl, SearchSettings *ExamplSearchSettings, FILE *file, regex_t *regex, const char *filename) {
  regmatch_t match;
  char *line = NULL;
  size_t length = 0;
  int line_count = 0, status;

  while ((getline(&line, &length, file)) != -1) {
    line_count++;

    delete_newline_character(&line);

    char *copy_line = strdup(line);
    char *original_copy_line = copy_line;

    while (((status = regexec(regex, copy_line, 1, &match, REG_NOTEOL)) == 0) && strlen(copy_line)) {
      if (match.rm_so == match.rm_eo) {
        copy_line++;
        continue;
      }

      if (ExamplSearchSettings->many_files && !fl.h) printf("%s:", filename);
      if (fl.n) printf("%d:", line_count);
      printf("%.*s\n", (int)match.rm_eo - (int)match.rm_so, copy_line + match.rm_so);

      copy_line += match.rm_eo;
    }

    free(original_copy_line);
    original_copy_line = NULL;
  }

  free(line);
  line = NULL;
}

void process_file_lines(Opt fl, SearchSettings *ExamplSearchSettings, FILE *file, regex_t *regex, const char *filename) {
  char *line = NULL;
  size_t length = 0;
  int line_count = 0, match_count = 0;

  while ((getline(&line, &length, file)) != -1) {
    line_count++;

    delete_newline_character(&line);

    int status = regexec(regex, line, 0, NULL, 0);

    if (!status ^ fl.v) {
      if (fl.l) {
        printf("%s\n", filename);
        break;
      }

      match_count++;

      if (!fl.c) {
        if (ExamplSearchSettings->many_files && !fl.h) printf("%s:", filename);
        if (fl.n) printf("%d:", line_count);
        printf("%s\n", line);
      }
    }
  }

  if (fl.c) {
    if (ExamplSearchSettings->many_files && !fl.h) printf("%s:", filename);
    printf("%d\n", match_count);
  }

  free(line);
  line = NULL;
}