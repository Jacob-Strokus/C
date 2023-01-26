CC = gcc

CFLAGS = -Wall -g -std=c89 -D_XOPEN_SOURCE=700 -pedantic-errors

TARGET = radix

LIBS = -lm

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(LIBS)

clean:
	rm $(TARGET)
