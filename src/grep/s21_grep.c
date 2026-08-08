#include "s21_grep.h"

#include <ctype.h>
#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Flags change_flags(int argc, char *argv[]) {
  int flag_open = getopt(argc, argv, "eivcslnho");
  Flags flags_struct = {false, false, false, false, false,
                        false, false, false, false};
  for (; flag_open != -1; flag_open = getopt(argc, argv, "eivcslnho")) {
    switch (flag_open) {
      case 'e':
        flags_struct.e = true;
        break;
      case 'i':
        flags_struct.i = true;
        break;
      case 'v':
        flags_struct.v = true;
        break;
      case 'c':
        flags_struct.c = true;
        break;
      case 'l':
        flags_struct.l = true;
        break;
      case 'n':
        flags_struct.n = true;
        break;
      case 'o':
        flags_struct.o = true;
        break;
      case 'h':
        flags_struct.h = true;
        break;
      case 's':
        flags_struct.s = true;
        break;
    }
  }
  return flags_struct;
}

void open_flags(char *name, Flags flags, char *substring, int argc) {
  FILE *f = fopen(name, "rt");
  char *string = NULL;
  if (f != NULL) {
    regex_t regex;
    if (flags.i) tolower_substring(substring);
    regcomp(&regex, substring, REG_EXTENDED);
    int c = fgetc(f);
    int step_c = fgetc(f);
    int counter_string = 0;
    int size = 0;
    int counter_result_string = 0;
    bool find_file_name = true;
    int number = 0;
    while (c != EOF) {
      if ((c != '\n') || ((c != '\n') && (step_c == EOF))) {
        string = realloc(string, (size + 1) * sizeof(char));
        size++;
        string[counter_string] = c;
        counter_string++;
      }
      if (c == '\n' || (c != '\n' && step_c == EOF)) {
        number++;
        string = realloc(string, (size + 1) * sizeof(char));
        string[counter_string] = '\0';
        char test_string[3000];
        int result;
        if (flags.i) {
          strcpy(test_string, string);
          tolower_substring(string);
        }
        result = regexec(&regex, string, 0, NULL, 0);
        if (flags.i) strcpy(string, test_string);
        if (result == 0)
          match_found(flags, string, name, number, argc, substring,
                      &counter_result_string, &find_file_name);
        if (result != 0 && flags.v && !flags.c && !flags.l)
          print_string(&string, argc, name, number, flags);
        if (result != 0 && flags.v && flags.l && find_file_name) {
          print_file_name(name);
          find_file_name = false;
        }
        if (result != 0 && flags.c && flags.v) counter_result_string++;

        free(string);
        string = NULL;
        counter_string = 0;
      }
      c = step_c;
      step_c = fgetc(f);
    }
    if (flags.c) count_string(argc, name, counter_result_string, flags);
    regfree(&regex);
    fclose(f);
  } else if (!flags.s)
    printf("grep: %s: No such file or directory\n", name);
  if (string != NULL) free(string);
}

void print_string(char **string, int argc, char *name, int number,
                  Flags flags) {
  if (argc == 4) {
    if (flags.n) printf("%d:", number);
    printf("%s\n", *string);
  }
  if (argc > 4) {
    if (!flags.n && !flags.h) printf("%s:%s\n", name, *string);
    if (!flags.n && flags.h) printf("%s\n", *string);
    if (flags.n && !flags.h) printf("%s:%d:%s\n", name, number, *string);
    if (flags.n && flags.h) printf("%d:%s\n", number, *string);
  }
}

void count_string(int argc, char *name, int counter_result_string,
                  Flags flags) {
  if (argc == 4) {
    printf("%d\n", counter_result_string);
  }
  if (argc > 4) {
    if (!flags.h)
      printf("%s:%d\n", name, counter_result_string);
    else
      printf("%d\n", counter_result_string);
  }
}

void print_file_name(char *name) { printf("%s\n", name); }

void tolower_substring(char *substring) {
  int length = strlen(substring);
  while (length != 0) {
    substring[length - 1] = tolower(substring[length - 1]);
    length--;
  }
}

void match_found(Flags flags, char *string, char *name, int number, int argc,
                 char *substring, int *counter_result_string,
                 bool *find_file_name) {
  if (flags.e && !flags.c && !flags.l && !flags.i && !flags.n && !flags.v &&
      !flags.o)
    print_string(&string, argc, name, number, flags);
  if (flags.c && !flags.v) {
    (*counter_result_string)++;
  }
  if (flags.l && *find_file_name && !flags.v) {
    print_file_name(name);
    *find_file_name = false;
  }
  if (flags.i && !flags.l && !flags.c && !flags.v && !flags.o)
    print_string(&string, argc, name, number, flags);
  if (flags.n && !flags.c && !flags.l && !flags.i && !flags.o)
    print_string(&string, argc, name, number, flags);
  if (flags.o && !flags.c && !flags.l && !flags.v)
    print_string(&substring, argc, name, number, flags);
  if (flags.h && !flags.c && !flags.l && !flags.v && !flags.n && !flags.i &&
      !flags.o && !flags.e)
    print_string(&string, argc, name, number, flags);
}
