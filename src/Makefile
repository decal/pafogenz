CC = cc
RM = rm 
CFLAGS = -O3 -c -g -Wall -ansi -pedantic -std=c11 -I../inc # -DDEBUG
RMFLAGS = -f
OBJS = main.o cmd_usage.o copy_str.o verbose_exit.o is_dupe_path.o qsort_compares.o bsearch_compares.o list_size.o fputs_list.o reorder_list.o
EXE = pafogenz
HDRS = ../inc/$(EXE).h
JUNK = core *.swp

all: $(EXE)
	$(CC) -o $(EXE) $(OBJS)

$(EXE): $(OBJS)

main.o: main.c $(HDRS)
	$(CC) $(CFLAGS) main.c

cmd_usage.o: cmd_usage.c $(HDRS)
	$(CC) $(CFLAGS) cmd_usage.c 

copy_str.o: copy_str.c $(HDRS)
	$(CC) $(CFLAGS) copy_str.c

is_dupe_path.o: is_dupe_path.c $(HDRS)
	$(CC) $(CFLAGS) is_dupe_path.c

qsort_compares.o: qsort_compares.c $(HDRS)
	$(CC) $(CFLAGS) qsort_compares.c

bsearch_compares.o: bsearch_compares.c $(HDRS)
	$(CC) $(CFLAGS) bsearch_compares.c

list_size.o: list_size.c $(HDRS)
	$(CC) $(CFLAGS) list_size.c

fputs_list.o: fputs_list.c $(HDRS)
	$(CC) $(CFLAGS) fputs_list.c

reorder_list.o: reorder_list.c $(HDRS)
	$(CC) $(CFLAGS) reorder_list.c

verbose_exit.o: verbose_exit.c $(HDRS)
	$(CC) $(CFLAGS) verbose_exit.c

clean:
	$(RM) $(RMFLAGS) $(OBJS)

clobber: clean
	$(RM) $(RMFLAGS) $(EXE) $(JUNK)
