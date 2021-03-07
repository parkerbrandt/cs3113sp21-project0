SRCS = project0.c
CC = g++

all: $(SRCS)
	$(CC) $(SRCS) -o project0.exe

clean:
	rm *.exe *.o *.out
