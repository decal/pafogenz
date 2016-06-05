#include"pafogenz.h"

size_t list_size(ASTR* head) {
  register size_t rsz = 0;
  register ASTR* ptr = head;

  if(!ptr)
    return rsz;
  
  if(!ptr->next)
    return ++rsz;

  do rsz++; while((ptr = ptr->next));

  return rsz;
}
