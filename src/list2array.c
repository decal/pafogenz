#include"pafogenz.h"

char **list2array(ASTRP *restrict head, const int pcnt) {
  register ASTRP *sp = head;
  register char **pp = istrv;
  
  for(pp = ipathv, sp = head;*pp && sp;sp = sp->next, pp++) {
    if(!(sp->str && *(sp->str)))
      continue;

    *pp = malloc(1 + strlen(sp->str));

    if(!*pp)
      vexit("malloc", EX_TEMPFAIL);

    strcpy(*pp, sp->str);
  }

  return istrv;
}
