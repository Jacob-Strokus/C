# Makefile for bucket_sort program

CC = gcc

CFLAGS = -Wall -g -std=c89 -D_XOPEN_SOURCE=700 -pedantic-errors

TARGET = project3_jstrokus_003

LIBS = -lm

all: $(TARGET)

$(TARGET): $(TARGET).c
        $(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(LIBS)

clean:
        rm $(TARGET)
