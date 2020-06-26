CC		= gcc
TARGETS = read_n_write read_only write_only

all: $(TARGETS)

read_n_write: rnw_main.o rnw1.o rnw2.o readA.o writeB.o
	$(CC) -o read_n_write rnw_main.o rnw1.o rnw2.o readA.o writeB.o

read_only: readA.o readB.o
	$(CC) -o read_only readA.o readB.o

write_only: writeA.o writeB.o
	$(CC) -o write_only writeA.o writeB.o

rnw_main.o: rnw.h rnw_main.c
	$(CC) -c -o rnw_main.o rnw_main.c

rnw1.o: rnw.h rnw1.c
	$(CC) -c -o rnw1.o rnw1.c

rnw2.o: rnw.h rnw2.c
	$(CC) -c -o rnw2.o rnw2.c

readA.o: read.h readA.c
	$(CC) -c -o readA.o readA.c

readB.o: read.h readB.c
	$(CC) -c -o readB.o readB.c

writeA.o: write.h writeA.c
	$(CC) -c -o writeA.o writeA.c

writeB.o: write.h writeB.c
	$(CC) -c -o writeB.o writeB.c

clean:
	rm *.o $(TARGETS)
