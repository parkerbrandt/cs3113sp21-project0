SRCS = project0.c
CC = g++

all: $(SRCS)
	$(CC) $(SRCS) -o project0

clean:
	rm project0
