#include"pafogenz.h"

char *copy_str(const char *ostr) {
  auto char *cstr = NULL;

  if(!ostr)
    vexit("!ostr", EX_SOFTWARE);

  cstr = malloc(1 + strlen(ostr));

  strcpy(cstr, ostr);

  return cstr;
}
