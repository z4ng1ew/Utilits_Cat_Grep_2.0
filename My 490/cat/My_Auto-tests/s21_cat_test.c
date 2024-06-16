#include "s21_cat_test.h"

const char flag_options[11][30] = {
    "-b ", "-e ", "-E ", "-n ", "-s ", "-t ", "-T ", "-v ", "--number-nonblank ", "--number ", "--squeeze-blank "
};

int main(int argument_count, char* options[]) {
  if (argument_count == 2 && options[1][0] >= '0' && options[1][0] <= '3') {
    create_test_cases();
    launch_testing(options[1][0]);
  } else {
    printf("Usage: ./s21_cat_test [flag 0-3]\n");
  }

  return 0;
}

void launch_testing(int option) {
  for (int flags_count = 0; flags_count <= option - '0'; flags_count++) {
    int tests_count = 1;

    for (int i = 0; i < flags_count; i++) tests_count *= 11;

    for (int test_id = 0; test_id < tests_count; test_id++) {
      char line_flags[200] = {0};
      int copy_id = test_id;
      for (int j = 0; j < flags_count; j++) {
        strcat(line_flags, flag_options[copy_id % 11]);
        copy_id /= 11;
      }

      perform_system_call(line_flags);

      if (compare_output_files()) {
        printf("Case input %3d --- %3d Not correct with flags: %s\n", test_id + 1, tests_count, line_flags);
      } else {
        printf("Test %3d --- %3d Correct\n", test_id + 1, tests_count);
      }
    }
  }

  system("rm -rf " TESTING_PATH);
}

void perform_system_call(char* line_flags) {
  char command[BUFSIZ] = {0};

  sprintf(command, "./s21_cat %s %s > %s", line_flags, TEST_FILES, S21_OUTPUT);
  system(command);

  sprintf(command, "cat %s %s > %s", line_flags, TEST_FILES, CAT_OUTPUT);
  system(command);
}

int compare_output_files() {
  FILE* s21_cat_file = fopen(S21_OUTPUT, "r");
  FILE* cat_file = fopen(CAT_OUTPUT, "r");

  int ch1, ch2;
  int error = 0;

  while ((ch1 = fgetc(s21_cat_file)) != EOF && (ch2 = fgetc(cat_file)) != EOF) {
    if (ch1 != ch2) {
      error = 1;
    }
  }

  fclose(s21_cat_file);
  fclose(cat_file);

  return error;
}

void create_test_cases() {
  create_directory();

  create_test_case_1();
  create_test_case_2();
  create_test_case_3();
  create_test_case_4();
  create_test_case_5();
}

void create_directory() {
  mkdir("My_Auto-tests", 0777);
  mkdir("My_Auto-tests/test-samples", 0777);
}

void create_test_case_1() {
  FILE* f = fopen(TESTING_PATH "test_1.txt", "w");
  fprintf(f, "\nabc end\n\n\nabcabcabc end\n\n\n\nabcabcabcabc end\n\n");
  fclose(f);
}

void create_test_case_2() {
  FILE* f = fopen(TESTING_PATH "test_2.txt", "w");
  fprintf(f, "tab\ttab\tend\n\nabc tab\t1abc end\nabc end\n\n");
  fclose(f);
}

void create_test_case_3() {
  FILE* f = fopen(TESTING_PATH "test_3.txt", "w");

  for (int ch = 0; ch < 128; ch++) {
    fprintf(f, "%c", ch);
  }

  fclose(f);
}

void create_test_case_4() {
  FILE* f = fopen(TESTING_PATH "test_4.txt", "w");
  fprintf(f, "\t\n    \n            \n            \n                    \n                    ");
  fclose(f);
}

void create_test_case_5() {
  FILE* f = fopen(TESTING_PATH "test_5.txt", "w");
  fclose(f);
}
