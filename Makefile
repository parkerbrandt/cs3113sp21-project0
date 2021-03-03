SRCS = project0.c
CC = g++
CFLAGS = -03 -I

all: $(SRCS)
	$(CC) $(SRCS) -o project0.exe

clean:
	rm *.exe *.o *.out
