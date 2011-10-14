CC=gcc44
CFLAGS=$(ACMLCFLAGS)

zgesv: zgesv.o
	$(CC) zgesv.o $(ACMLLIBPATH) $(ACMLLIBS) -lm -o zgesv
