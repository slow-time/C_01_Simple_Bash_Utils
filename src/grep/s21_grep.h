#include <stdbool.h>

typedef struct Flags {
  bool e;
  bool i;
  bool v;
  bool c;
  bool l;
  bool n;
  bool h;
  bool o;
  bool s;
} Flags;

Flags change_flags(int argc, char *argv[]);
void open_flags(char *name, Flags flags, char *substring, int argc);
void print_string(char **string, int argc, char *name, int number, Flags flags);
void count_string(int argc, char *name, int counter_result_string, Flags flags);
void print_file_name(char *name);
void tolower_substring(char *substring);
void match_found(Flags flags, char *string, char *name, int number, int argc,
                 char *substring, int *counter_result_string,
                 bool *find_file_name);
