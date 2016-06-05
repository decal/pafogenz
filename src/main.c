#include"pafogenz.h"

ASTR head_ifile;
ASTR head_dname;
ASTR head_fname;
ASTR head_query;
ASTR head_anchr;

char *xstr, **ipathv, **dnamev, **inamev, **fnamev, **qnamev, **anamev;

int main(int argc, char *argv[], char *envp[]) {
  static char ibuf[BUFSIZ] = { 0x00, };
  register unsigned int pcnt = 0u, dcnt = 0u, fcnt = 0u, icnt = 0u, qcnt = 0u, acnt = 0u, zcnt = 0u;
  register ASTRP ap = &head_ifile, ad = &head_dname, af = &head_fname, aq = &head_query, aa = &head_anchr;
  register char *restrict *restrict pp = 0x0, *restrict *pp2 = 0x0;
  register FILE *restrict path_fp = NULL, *restrict file_fp = NULL, *restrict qrry_fp = NULL, *restrict anch_fp = NULL;

  file_fp = fopen(DATA_FILES_TXT, "r");

  if(!file_fp)
    vexit("fopen", EX_IOERR);

  while(fgets(ibuf, sizeof ibuf, file_fp)) {
    auto char *crlf = strchr(ibuf, '\n');

    if(!crlf)
      continue;

    *crlf = '\0';

    af->astr = strdup(ibuf);

#ifdef DEBUG
  fprintf(stderr, "af->astr: strdup(%s)\n", ibuf);
#endif

    if(!af->astr)
      vexit("strdup", EX_TEMPFAIL);

    af->next = calloc(1, sizeof*(af->next));

    if(!af->next)
      vexit("calloc", EX_TEMPFAIL);

    af = af->next;

    fcnt++;
  }

  path_fp = fopen(DATA_PATHS_TXT, "r");

  if(!path_fp)
    vexit("fopen", EX_IOERR);

  ap->astr = malloc(2);
  ap->astr = "/\x00";
  ap->next = NULL;

  pcnt = 1;
  
  while(fgets(ibuf, sizeof ibuf, path_fp)) {
    register ASTRP ad = &head_dname;
    register char *restrict p = ibuf;
    

    if(!(p && *p))
      break;
  
    p = strchr(ibuf, '\n');

    if(p) {
      *p = '\0';
    } else {
      p = strchr(ibuf, '\n');

      if(p)
        *p = '\0';
    }

#ifdef DEBUG
  fprintf(stderr, "is_dupe_path(%s)\n", ibuf);
#endif

    if(is_dupe_path(ibuf)) {
      continue;
    }
    else {
      register char *sp = strrchr(ibuf, '/');

      puts(ibuf); zcnt++;

      pcnt++;

      if(sp && !strchr(++sp, '.')) {
        /* 2 bytes = 1 for delimiting slash plus 1 for null terminator */
        xstr = malloc(2 + strlen(ibuf) + strlen("README"));

        if(!xstr)
          vexit("malloc", EX_TEMPFAIL);

        sprintf(xstr, "%s/%s", ibuf, "README");

        if(!is_dupe_path(xstr)) {
          puts(xstr); zcnt++;

          pcnt++;
        }

        free(xstr);
      }
    } 

    do {
      register char *restrict p2 = strchr(ibuf, '/');

      if(!p2)
        break; 

      p = p2;
      *p = '\0';

      for(p2 = --p;p2 != ibuf && *p2 && *p2 != '/';p2--);

      if(*p2 == '/')
        *p2 = '\0';

      if(!*++p2)
         continue;

      ad->astr = strdup(p2);

      if(!ad->astr)
        vexit("strdup", EX_TEMPFAIL);

      ad->next = calloc(1, sizeof*(ad->next));

      if(!ad->next)
        vexit("calloc", EX_TEMPFAIL);

      ad = ad->next;

      if((p2 - 1) != ibuf) 
        *--p2 = '/';
      else 
        *(p2 - 1) = '/';

      if(is_dupe_path(ibuf))
        continue;

      puts(ibuf); ++zcnt;

      qrry_fp = fopen(DATA_QUERY_TXT, "r");

      if(qrry_fp) {
        char qbuf[BUFSIZ] = { 0x00, };

        while(fgets(qbuf, sizeof qbuf, qrry_fp)) {
          qbuf[strlen(qbuf) - 1] = '\0';

          printf("%s%s\n", ibuf, qbuf); ++zcnt;

          qcnt++;
        }

        fclose(qrry_fp);

        anch_fp = fopen(DATA_ANCHOR_TXT, "r");

        if(anch_fp) {
          char abuf[BUFSIZ] = { 00 };

          while(fgets(abuf, sizeof abuf, anch_fp)) {
            abuf[strlen(abuf) - 1] = '\0';

            printf("%s%s%s\n", ibuf, qbuf, abuf); ++zcnt;

            acnt++;
          }

          fclose(anch_fp);
        }
      }

      puts(ibuf); ++zcnt;

      pcnt++;

      /* 2 bytes = 1 for delimiting slash plus 1 for null terminator */
      xstr = malloc(2 + strlen(ibuf) + strlen("README"));

      if(!xstr)
        vexit("malloc", EX_TEMPFAIL);

      sprintf(xstr, "%s/%s", ibuf, "README");

      if(!is_dupe_path(xstr)) {
        puts(xstr); 
        ++zcnt;
        pcnt++;
      }

      free(xstr);

      ap->next = calloc(1, sizeof*(ap->next));

      if(!ap->next)
        vexit("calloc", EX_TEMPFAIL);

      ap = ap->next;
      ap->astr = strdup(ibuf);

#ifdef DEBUG
  fprintf(stderr, "ap->astr = srtdup(%s)\n", ibuf);
#endif

      if(!ap->astr)
        vexit("strdup", EX_TEMPFAIL);
    } while(true); 
  }

#ifdef DEBUG
  fputc('\n', stderr);
#endif

  ipathv = calloc(++pcnt, sizeof*ipathv);

  if(!ipathv)
    vexit("calloc", EX_TEMPFAIL);

  for(pp = ipathv, ap = &head_ifile;*pp && ap;ap = ap->next, pp++) {
    if(!(ap->astr && *(ap->astr)))
      continue;

    *pp = strdup(ap->astr);

    if(!*pp)
      vexit("strdup", EX_TEMPFAIL);
  }

/** COMPLETELY WRONG HERE **/
  /* list_size is counting full paths with many slashes within them, 
   * as opposed to individual directory names */

  register size_t ls_xx = 0;
  size_t ls_sz  = list_size(&head_ifile);

#ifdef DEBUG
  printf("Size: %u Head: %x\n", ls_sz, head_ifile);
#endif

  for(ls_xx = 1;ls_xx < ls_sz;++ls_xx) {
    register ASTR *p = reorder_list(&head_ifile, ls_xx);

    if(p && p->astr)
      do {
        putchar('/');
        fputs(p->astr, stdout);

        p = p->next;
      } while(p && p->astr);

    putchar('\n');
  }

  for(ad = &head_dname;ad;ad = ad->next) {
    if(!(ad->astr && *(ad->astr)))
      continue;
    else
      dcnt++;

#ifdef DEBUG
    fprintf(stderr, "ad->astr: %s ", ad->astr);
#endif
  }

#ifdef DEBUG
  fputc('\n', stderr);
#endif
  
  fnamev = calloc(++fcnt, sizeof*fnamev);

  if(!fnamev)
    vexit("calloc", EX_TEMPFAIL);

  for(pp = fnamev, af = &head_fname;*pp && af;af = af->next, pp++) {
    if(!(af->astr && *(af->astr)))
      continue;

#ifdef DEBUG
    fprintf(stderr, "af->astr: %s ", af->astr);
#endif

    *pp = malloc(1 + strlen(af->astr));

    if(!*pp)
      vexit("malloc", EX_TEMPFAIL);

    strcpy(*pp, af->astr);
  }

#ifdef DEBUG
  fputc('\n', stderr);
#endif

  dnamev = calloc(++dcnt, sizeof*dnamev);

  if(!dnamev)
    vexit("calloc", EX_TEMPFAIL);

  for(pp = dnamev, ad = &head_dname;*pp && ad;ad = ad->next, pp++) {
    if(!(ad->astr && *(ad->astr)))
      continue;

    puts(ad->astr);

    *pp = malloc(1 + strlen(ad->astr));

    if(!*pp)
      vexit("malloc", EX_TEMPFAIL);

    strcpy(*pp, ad->astr);
  }

  *pp = NULL;

  if(getenv("SORTBY_RAND")) {
    qsort(fnamev, fcnt, sizeof*fnamev, qs_randcmp);
    qsort(ipathv, icnt, sizeof*inamev, qs_randcmp);
    qsort(dnamev, dcnt, sizeof*dnamev, qs_randcmp);
    /* qsort(qnamev, qcnt, sizeof*qnamev, qs_randcmp); */
    /* qsort(anamev, acnt, sizeof*anamev, qs_randcmp); */
  } else {
    qsort(fnamev, fcnt, sizeof*fnamev, getenv("SORTBY_CASE") ? qs_strcasecmp : qs_strcmp);
    qsort(ipathv, pcnt, sizeof*ipathv, getenv("SORTBY_CASE") ? qs_strcasecmp : qs_strcmp);
    qsort(dnamev, dcnt, sizeof*dnamev, getenv("SORTBY_CASE") ? qs_strcasecmp : qs_strcmp);
    /* qsort(qnamev, qcnt, sizeof*qnamev, getenv("SORTBY_CASE") ? qs_strcasecmp : qs_strcmp); */
    /* qsort(anamev, qcnt, sizeof*anamev, getenv("SORTBY_CASE") ? qs_strcasecmp : qs_strcmp); */
  }

  rewind(path_fp);

  for(pp = ipathv;*pp;pp++) {
    if(bsearch(*pp, ipathv, pcnt, sizeof*ipathv, getenv("SORTBY_CASE") ? bs_strcasecmp : bs_strcmp)) {
      continue;
    } else {
      if(is_dupe_path(*pp))
        continue;

      puts(*pp); ++zcnt;

      pcnt++;
    }
  }

  *pp = NULL;

  for(pp2 = fnamev, pp = ipathv;*pp && *pp2;pp++, pp2++) {
    /* register signed int xflag = (int)*pp2; */

    fputs(*pp2, stdout);
    putchar('/');
    puts(*pp2); 
  }

  *pp2 = NULL;

  /* do {
    
  } while(true); */

  putc('\n', stderr);

  fprintf(stderr, "*** The total path string count is now: %u\n", pcnt);
  fprintf(stderr, "*** The total number of unique directory names: %u\n", dcnt);
  fprintf(stderr, "*** The total number of unique file names: %u\n", fcnt);
  fprintf(stderr, "*** The total number of unique CGI query strings: %u\n", qcnt);
  fprintf(stderr, "*** The total number of unique HTML anchors: %u\n", acnt);
  fprintf(stderr, "*** The displayed path names sum to a GRAND TOTAL: %u\n", zcnt);

  exit(EXIT_SUCCESS);
}
