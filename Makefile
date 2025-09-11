CC = gcc
CFLAGS = -Wall -Wextra -g
INCLUDES = -Iinclude

SRCS = src/main.c src/print.c src/dir.c src/fileinfo.c src/globals.c
OBJS = $(SRCS:.c=.o)

TARGET = bls

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

