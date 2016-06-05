#include"pafogenz.h"

_Noreturn void cmd_usage(const char *const av0) {
  fprintf(stderr, "usage: %s\n", av0);

  exit(EX_USAGE);
} 
