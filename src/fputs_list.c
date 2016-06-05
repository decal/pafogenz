#include"pafogenz.h"

void fputs_list(ASTR *head, FILE *fptr) {
  register ASTRP restrict aele = head;

  if(aele && aele->astr)
    do {
      if(!(aele && aele->astr))
          break;

      fputs(aele->astr, fptr);

      aele = aele->next;
    } while(aele);

  return;    
}
