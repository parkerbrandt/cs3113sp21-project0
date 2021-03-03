SRCS = project0.c
CC = g++
CFLAGS = -03 -I

all: $(SRCS)
	$(CC) $(SRCS) -o project0.o

clean:
	rm *.exe *.o *.out
