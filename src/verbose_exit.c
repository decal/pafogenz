#include"pafogenz.h"

void verbose_exit(const char *fn, const int st, const char *fl, const int ln) {
  fprintf(stderr, "%s:%u %s => %s\n", fl, ln, fn, strerror(errno));

  exit(st);
}
