CC = gcc
CFLAGS = -Wall -Wextra
TARGET = rr sjf fcfs priority priority_rr
SRC = driver.c list.c cpu.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

rr: $(OBJ) schedule_rr.o
	$(CC) $(CFLAGS) -o $@ $^

sjf: $(OBJ) schedule_sjf.o
	$(CC) $(CFLAGS) -o $@ $^

fcfs: $(OBJ) schedule_fcfs.o
	$(CC) $(CFLAGS) -o $@ $^

priority: $(OBJ) schedule_priority.o
	$(CC) $(CFLAGS) -o $@ $^

priority_rr: $(OBJ) schedule_priority_rr.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) schedule_*.o

.PHONY: all clean
