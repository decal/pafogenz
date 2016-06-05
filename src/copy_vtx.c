#include"pafogenz.h"

/*
   @file copy_vtx.c
   @fn copy_vtx
   @brief copy vertex 
   @param[in] vtex The vertex to copy a string into
   @param[in] pstr The string to copy into the vertex
   @returns pointer to the next vertex in the linked list
   @cite ASTRP
   @see hyper_pathogen.h
*/

ASTRP copy_vtx(const ASTR *vtex, const char *pstr) {
  if(!(pstr && vtex && *vtex))
    vexit("!(astr && vtex && *vtex)", EX_SOFTWARE);

  vtex->astr = strdup(pstr);

  if(!vtex->astr)
    vexit("strdup", EX_TEMPFAIL);

  vtex->next = calloc(1, sizeof*(vtex->next));
  
  if(!vtex->next)
    vexit("calloc", EX_TEMPFAIL);

  return vtex->next;
}
