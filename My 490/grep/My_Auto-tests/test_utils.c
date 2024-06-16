#include "test_utils.h"

void create_tests() {
  create_dir();

  create_test_1();
  create_test_2();
  create_test_3();
  create_test_4();
  create_test_5();
}

void create_dir() {
  mkdir("My_Auto-tests", 0777);
  if (mkdir("My_Auto-tests/test-samples", 0777) == 0) {
    printf("Тесты были успешно запущены!\n");
  }
}

void create_test_1() {
  FILE* f = fopen(PATH "test_1.txt", "w");
  fprintf(f, "\nabc end\n\n\nabcabcabc end\n\n\n\nabcabcabcabc end\n\n");
  fclose(f);
}

void create_test_2() {
  FILE* f = fopen(PATH "test_2.txt", "w");
  fprintf(f, "tab	tab	end\n\nabc tab	1abc end\nabc end\n\n");
  fclose(f);
}

void create_test_3() {
  FILE* f = fopen(PATH "test_3.txt", "w");

  for (int i = 0; i < 2000; i++) {
    int ch = rand() % 128;
    while (!isalnum(ch)) ch = rand() % 128;

    fprintf(f, "%c", ch);
    if (i % 10 == 9) fprintf(f, "\n");
  }

  fclose(f);
}

void create_test_4() {
  FILE* f = fopen(PATH "test_4.txt", "w");
  fprintf(f,
          "	\n    		\n            			\n             "
          "           				\n                             "
          "           					");
  fclose(f);
}

void create_test_5() {
  FILE* f = fopen(PATH "test_5.txt", "w");
  fprintf(f, " ");
  fclose(f);
}


