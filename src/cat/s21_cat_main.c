#include <stdio.h>

#include "s21_cat.h"

int main(int argc, char *argv[]) {
  Flags flag = change_flags(argc, argv);
  int counter = 1;
  for (int i = 1; i < argc; i++) {
    open_flags(argv[i], flag, &counter);
  }
  return 0;
}
