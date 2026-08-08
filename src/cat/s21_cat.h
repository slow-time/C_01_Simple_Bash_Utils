#include <stdbool.h>
#include <stdio.h>

typedef struct Flags {
  bool number_not_empty;
  bool mark_end;
  bool number_all;
  bool squeeze;
  bool tab;
  bool symbol_see;
} Flags;

Flags change_flags(int argc, char *argv[]);
void open_flags(char *name, Flags flags, int *counter);
void number_all(bool *first_symbol, int *counter, bool *print_counter, int c,
                int step_c);
void number_not_empty(bool *first_symbol, int c, int *counter,
                      bool *print_counter, int step_c);
void symbol_see(int *c);
void squeeze(int *c, int *step_c, int *step_c_two, FILE **f);
void tab(int *c);
void mark_end(int c);
