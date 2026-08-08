#include "s21_grep.h"

Flags change_flags(int argc, char *argv[]);
void open_flags(char *name, Flags flags, char *substring, int argc);

int main(int argc, char *argv[]) {
  Flags flags = change_flags(argc, argv);
  for (int i = 3; i < argc; i++) {
    open_flags(argv[i], flags, argv[2], argc);
  }
  return 0;
}
