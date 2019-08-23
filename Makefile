GIT_VERSION := "$(shell git --version)"

CC=gcc
CFLAGS=-Wall -pedantic -DVERSION=\"$(GIT_VERSION)\"

#test: rdproc
	#./rdproc -ck

rdproc: main.o rdproc.o
	$(CC) $(CFLAGS) -o rdproc main.o rdproc.o

main.o: main.c rdproc.h
	$(CC) $(CFLAGS) -c main.c

rdproc.o: rdproc.c rdproc.h
	$(CC) $(CFLAGS) -c rdproc.c

clean:
	rm rdproc rdproc.o main.o
