#include"pafogenz.h"

ASTR *reorder_list(ASTR *head, size_t elem) { /* this function doesn't have to change the.. */
  register ASTRP lptr = head; /* value of head in the caller */
  register size_t node = 0;              /* return new first node pointer */

  if(!(lptr && elem))
    return NULL;
  else if(!lptr->next)
    return head;
  else if(lptr == lptr->next) /* erroneous condition for singly linked list */
    exit(EX_DATAERR);

  do {
    if(node == elem) {
      char *atmp = lptr->astr;

      lptr->astr = head->astr;
      head->astr = atmp;

      break;
    }

    node++;

    lptr = lptr->next;
  } while(lptr);

  return head;
}
