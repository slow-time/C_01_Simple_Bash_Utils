#include "s21_cat.h"

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>

Flags change_flags(int argc, char *argv[]) {
  struct option longopts[] = {{"number-nonblank", 0, NULL, 'b'},
                              {"number", 0, NULL, 'n'},
                              {"squeeze-blank", 0, NULL, 's'},
                              {NULL, 0, NULL, 0}};

  int flag_open = getopt_long(argc, argv, "benstTEv", longopts, NULL);
  Flags flags_struct = {false, false, false, false, false, false};
  for (; flag_open != -1;
       flag_open = getopt_long(argc, argv, "benstTEv", longopts, NULL)) {
    switch (flag_open) {
      case 'b':
        flags_struct.number_not_empty = true;
        break;
      case 'e':
        flags_struct.mark_end = true;
        flags_struct.symbol_see = true;
        break;
      case 'n':
        flags_struct.number_all = true;
        break;
      case 's':
        flags_struct.squeeze = true;
        break;
      case 't':
        flags_struct.tab = true;
        flags_struct.symbol_see = true;
        break;
      case 'T':
        flags_struct.tab = true;
        break;
      case 'E':
        flags_struct.mark_end = true;
        break;
      case 'v':
        flags_struct.symbol_see = true;
        break;
    }
  }
  return flags_struct;
}

void open_flags(char *name, Flags flags, int *counter) {
  FILE *f = fopen(name, "r");
  if (f != NULL) {
    int c = fgetc(f);
    int step_c = fgetc(f);
    int step_c_two = fgetc(f);
    bool first_symbol = true;
    bool print_counter = false;
    int end = false;
    while (c != EOF) {
      if ((flags.number_all && flags.number_not_empty) ||
          (!flags.number_all && flags.number_not_empty)) {
        number_not_empty(&first_symbol, c, counter, &print_counter, step_c);
      }

      if (flags.number_all && !flags.number_not_empty) {
        number_all(&first_symbol, counter, &print_counter, c, step_c);
      }

      if (flags.mark_end) {
        mark_end(c);
      }

      if (flags.squeeze) {
        squeeze(&c, &step_c, &step_c_two, &f);
      }

      if (flags.symbol_see) {
        symbol_see(&c);
      }

      if (flags.tab) {
        tab(&c);
      }

      if (!end) putc(c, stdout);
      c = step_c;
      step_c = step_c_two;
      step_c_two = fgetc(f);
    }
    fclose(f);
  }
}

void number_all(bool *first_symbol, int *counter, bool *print_counter, int c,
                int step_c) {
  if (*first_symbol) {
    printf("%6d\t", *counter);
    (*counter)++;
    *first_symbol = false;
  }

  if (*print_counter) {
    printf("%6d\t", *counter);
    (*counter)++;
    *print_counter = false;
  }
  if (c == '\n' && step_c != EOF) *print_counter = true;
}

void number_not_empty(bool *first_symbol, int c, int *counter,
                      bool *print_counter, int step_c) {
  if (*first_symbol && c != '\n') {
    printf("%6d\t", *counter);
    (*counter)++;
    *first_symbol = false;
  }
  if (*print_counter) {
    printf("%6d\t", *counter);
    (*counter)++;
    *print_counter = false;
  }

  if (step_c != '\n' && c == '\n' && !*first_symbol && step_c != EOF) {
    *print_counter = true;
  }
}

void symbol_see(int *c) {
  if (*c != '\n' && *c != '\t') {
    if (*c >= 1 && *c <= 31) {
      printf("^");
      *c += 64;
    } else if (*c == 127) {
      printf("^");
      *c = 63;
    } else if (*c >= 128 && *c <= 159) {
      printf("M-^");
      *c -= 64;
    } else if (*c == 0) {
      printf("^");
      *c += 64;
    }
  }
}

void squeeze(int *c, int *step_c, int *step_c_two, FILE **f) {
  while ((*step_c == '\n') && (*c == '\n') && (*step_c_two == '\n')) {
    *c = *step_c;
    *step_c = *step_c_two;
    *step_c_two = fgetc(*f);
  }
}

void tab(int *c) {
  if (*c == '\t') {
    printf("^");
    *c += 64;
  }
}

void mark_end(int c) {
  if (c == '\n') {
    printf("$");
  }
}