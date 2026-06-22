CC      = gcc
CFLAGS  = -Wall -std=c99 -lm
INCLUDE = -Iinclude/
TARGET  = main

all:
	$(CC) $(CFLAGS) $(INCLUDE) src/main.c -o $(TARGET)

clean:
	rm $(TARGET)