#ifndef S21_CAT_TEST_H
#define S21_CAT_TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define TESTING_PATH "My_Auto-tests/test-samples/"
#define S21_OUTPUT (TESTING_PATH "s21_output.txt")
#define CAT_OUTPUT (TESTING_PATH "cat_output.txt")
#define TEST_FILES                                                    \
  TESTING_PATH "test_1.txt " TESTING_PATH "test_2.txt " TESTING_PATH \
       "test_3.txt " TESTING_PATH "test_4.txt " TESTING_PATH "test_5.txt "

extern const char flag_options[11][30];

void launch_testing(int param);
void perform_system_call(char* line_flags);
int compare_output_files();
void create_directory();
void create_test_cases();
void create_test_case_1();
void create_test_case_2();
void create_test_case_3();
void create_test_case_4();
void create_test_case_5();

#endif /* S21_CAT_TEST_H */


