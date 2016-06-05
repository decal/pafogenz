#include"pafogenz.h"

int bs_strcmp(const void *s1, const void *s2) {
  return strcmp(s1, s2);
}

int bs_strcasecmp(const void *s1, const void *s2) {
  return strcasecmp(s1, s2);
}

int bs_randcmp(const void *s1, const void *s2) {
  static int vals[] = { -1, 0, 1 };

  return vals[rand() % (1 + sizeof vals)];
}
