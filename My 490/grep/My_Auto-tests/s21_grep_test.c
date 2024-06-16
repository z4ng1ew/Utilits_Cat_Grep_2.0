#include "s21_grep_test.h"


int calculate_tests_count(int max_flags);
int run_test(int test_id, int tests_count, int valgrind);
void clean_up();
int generate_line_flags(int test_id, int* prev_flag, int* param, int* skip_test, char* line_flags);
void add_random_chars(char* line_flags, int count);
int check_for_errors(const char* line_flags, int valgrind);




int main(int argc, char* argv[]) {
  int valid_input = (argc == 3);

  if (valid_input) {
    char flag = argv[1][0];
    char v_flag = argv[2][0];
    valid_input = (flag >= '0' && flag <= '5' && (v_flag == 'v' || v_flag == '0'));
  }

  if (valid_input) {
    create_tests();
    start_testing(argv[1][0] - '0', argv[2][0] == 'v' ? 1 : 0);
  } else {
    printf("Usage: ./s21_grep_test [flag 0-5] [valgrind v or 0]\n");
  }

  return 0;
}


void start_testing(int max_flags, int valgrind) {
  int tests_count = calculate_tests_count(max_flags);

  for (int test_id = -1; test_id < tests_count - 1; test_id++) {
    if (run_test(test_id, tests_count, valgrind)) {
      break;
    }
  }

  clean_up();
}






int calculate_tests_count(int max_flags) {
  int tests_count = 1;
  for (int i = 0, j = FLAGS_COUNT; i < max_flags; i++, j *= FLAGS_COUNT) {
    tests_count += j;
  }
  return tests_count;
}


int run_test(int test_id, int tests_count, int valgrind) {
  srand(test_id);
  int param = 1, prev_flag = FLAGS_COUNT, skip_test = 0;
  char line_flags[200] = {0};
  int result = 0;

  if (generate_line_flags(test_id, &prev_flag, &param, &skip_test, line_flags)) {
    if (!skip_test) {
      printf("\033[   CCase_input --- %3d ------ %3d: \033[0m", test_id + 2, tests_count);

      add_random_chars(line_flags, param);
      strcat(line_flags, " ");
      system_call(line_flags, valgrind);

      if (check_for_errors(line_flags, valgrind)) {
        result = 1;
      } else {
        printf(OK);
      }
    }
  }

  return result;
}




int check_flag_order(int flag_id, int* prev_flag, int* skip_test) {
  int result = (flag_id <= *prev_flag); 
  
  *prev_flag = flag_id; 
  *skip_test = result ? 0 : 1; 
  
  return result; 
}




int generate_line_flags(int test_id, int* prev_flag, int* param, int* skip_test, char* line_flags) {
  int success = 1;
  int continue_processing = 1; 

  for (int copy_id = test_id; copy_id >= 0 && continue_processing; copy_id = copy_id / FLAGS_COUNT - 1) {
    int flag_id = copy_id % FLAGS_COUNT;

    if (!check_flag_order(flag_id, prev_flag, skip_test)) {
      success = 0;
      continue_processing = 0; 
    } else {
      strcat(line_flags, flags[flag_id]);

      if (flag_id == 8) {
        add_random_chars(line_flags, 1);
        strcat(line_flags, " ");
        *param = 0;
      }

      if (flag_id == 9) {
        sprintf(line_flags + strlen(line_flags), PATH "test_%d.txt ", rand() % 5 + 1);
        *param = 0;
      }
    }
  }

  return success;
}





int check_for_errors(const char* line_flags, int valgrind) {
  int error = file_compare(valgrind);

  if (error) {
    printf("\033[1;37mWrong flag: %s\033[0m\n", line_flags);
    printf("Сравнение утилит: %s\n", error & 1 ? Not_correct : OK);
    printf("Проверка на утечку: %s\n", error & 2 ? Not_correct : OK);
  } else {
    printf(OK);
  }

  return error != 0; 
}





void clean_up() {
  system("rm -rf My_Auto-tests/test-samples/");
}






void add_random_chars(char* line_flags, int count) {
  char ch[2] = "0";

  for (int i = rand() % 3 + 1; count && i > 0; i--) {
    do {
      ch[0] = rand() % 128;
    } while (!isalnum(ch[0]));
    strcat(line_flags, ch);
  }
}





















void system_call(char* line_flags, int valgrind) {
  char command[BUFSIZ] = {0};

  sprintf(command, "./s21_grep %s %s > %s", line_flags, TEST_FILES, S21_OUTPUT);
  printf("%s\n", command);
  system(command);

  sprintf(command, "grep %s %s > %s", line_flags, TEST_FILES, GREP_OUTPUT);
  printf("%s\n", command);
  system(command);

  if (valgrind) {
    sprintf(command, VALGRIND "./s21_grep %s %s > %s 2>&1", line_flags,
            TEST_FILES, VALGRIND_OUTPUT);
    printf("%s\n", command);
    system(command);
  }
}

















int file_compare(int valgrind) {
  int error = 0;

  FILE* s21_file = fopen(S21_OUTPUT, "r");
  FILE* grep_file = fopen(GREP_OUTPUT, "r");

  while (1) {
    int ch1 = fgetc(s21_file);
    int ch2 = fgetc(grep_file);

    if (ch1 == EOF && ch2 == EOF) break;
    if (ch1 != ch2) {
      error = 1;
      break;
    }
  }

  fclose(s21_file);
  fclose(grep_file);

  if (valgrind) {
    FILE* valgrind_file = fopen(VALGRIND_OUTPUT, "r");

    const char noleaks[100] =
        "All heap blocks were freed -- no leaks are possible";
    char line[100] = {0};
    int no_leaks = 0;

    while (fgets(line, 100, valgrind_file) != NULL && !no_leaks)
      if (strstr(line, noleaks) != NULL) no_leaks = 1;

    if (!no_leaks) error += 2;

    fclose(valgrind_file);
  }

  return error;
}