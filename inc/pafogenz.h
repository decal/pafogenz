#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<strings.h>
#include<sysexits.h>
#include<assert.h>
#include<errno.h>

typedef struct _ASTR {
  char *astr;
  struct _ASTR *next;
} ASTR, *ASTRP, **ASTRPP;

#define DATA_FILES_TXT "data/files.txt"
#define DATA_PATHS_TXT "data/paths.txt"
#define DATA_QUERY_TXT "data/query.txt"
#define DATA_ANCHOR_TXT "data/anchor.txt"

#define vexit(F, S) verbose_exit(F, S, __FILE__, __LINE__)

extern ASTR head_ifile;
extern ASTR head_dname;
extern ASTR head_fname;
extern char *xstr, **ipathv, **dnamev, **fnamev;

ASTRP *copy_vtx(const ASTRP*, const char*);
void verbose_exit(const char *, const int, const char *, const int);
ASTR *reorder_list(ASTR*, size_t);
_Noreturn void cmd_usage(const char *const);
_Bool is_dupe_path(const char *);
char **list2array(ASTRP *restrict, const int);
char *copy_str(const char *);
ASTRP *copy_vtx(const ASTRP *, const char *);
_Bool is_dupe_path(const char *);
size_t list_size(ASTR*);
void fputs_list(ASTR*, FILE*);

int qs_randcmp(const void*, const void*);
int qs_strcmp(const void*, const void*);
int qs_strcasecmp(const void*, const void*);
int bs_strcmp(const void*, const void*);
int bs_strcasecmp(const void*, const void*);
int bs_randcmp(const void*, const void*);
