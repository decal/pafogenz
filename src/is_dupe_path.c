#include"pafogenz.h"

_Bool is_dupe_path(const char *astr) {
  register ASTRP apth = &head_ifile;

  if(!(astr && *astr && apth))
    return false;

  do {
    if(!apth->astr) {
      apth->astr = strdup(astr);

      if(!apth->astr)
        vexit("strdup", EX_TEMPFAIL);
    }
    
    if(!strcmp(astr, apth->astr))
      return true;

    apth = apth->next;
  } while(apth);

  return false;
}
