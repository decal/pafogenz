#include"pafogenz.h"

char **split_dir(char *adir) {
  register char *aptr = adir;
  char *ptrs[BUFSIZ] = { 00, }, **sdir = NULL;
  register size_t slash_cnt = 0, loop_ctr = 0;

  assert(*adir == '/');
  memset(ptrs, 0, BUFSIZ);

  for(aptr = adir;*aptr;aptr++) {
    *aptr = '\0';
    ptrs[slash_cnt] = aptr + 1;
    aptr = strchr(ptrs[slash_cnt] '/');
    slash_cnt++;
  }

  ptrs[slash_cnt] = NULL;

 sdir = malloc(++slash_cnt * sizeof*sdir);

 if(!sdir)
  vexit("malloc", EX_TEMPFAIL);

 for(loop_ctr = 0;loop_ctr < slash_cnt;++loop_ctr) {
   sdir[loop_ctr] = strdup(ptrs[loop_ctr]);

   if(!sdir[loop_ctr])
     vexit("strdup", EX_TEMPFAIL);

   /* if(loop_ctr)
     *ptrs[loop_ctr] = '/'; */
 }

 sdir[loop_ctr] = NULL;

 return sdir;
}

size_t slash_count(char *dname) {
  register size_t r = 0;
  register char *p = dname;

  if(p)
    do 
      if(*p == '/')
        r++;
    while(*++p);

  return r;
}

char **unique_dirs(char **dstrs) {
  char *ud[BUFSIZ] = { 0x00 };
  register char **pp = dstrs, **words = NULL, **pw = NULL, **up = ud, **uc = NULL;
  size_t full_dir_cnt = 0, uniq_dir_cnt = 0;

  memset(ud, 0x00, sizeof ud);

  if(pp)
    do {
      full_dir_cnt += slash_count(*pp);
      words = split_dir(*pp);

      for(pw = words;*pw;++pw) {
        register char **ae = ud;
        int flag = 1;

        for(++ae;*ae;++ae)
          if(!strcmp(*ae, *pw))
            flag = 0;

        if(flag)
          *up++ = strdup(*pw);
      } 
    } while(*++pp);

  *up = NULL;
  up = ud;

  /* for(up = ud;*up;++up)
      for(pw = ud;*pw;++pw)
        if(up != pw && strcmp((const char*)*pw, (const char*)*up)) {
          puts(*up);

          break;
        } */

  /* for(pw = ud;*pw;++pw)
    puts(*pw); */

  return up;
}

#if 1
int main(void) {
  char *dirs[4];
  dirs[0] = strdup("/a/b/c.html");
  dirs[1] = strdup("/cgi-bin/server-status"); 
  dirs[2] = strdup("/usr/local/share/doc");
  dirs[3] = NULL;

  register char **sptr = NULL;
  char **udirs = unique_dirs(dirs);

  for(sptr = udirs;*sptr;++sptr)
    puts(*sptr);

  return 0;
}
#endif
