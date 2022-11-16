
CC = gcc
 
CFLAGS = -Wall -g -O2 -std=c89 -D_XOPEN_SOURCE=600 -pedantic-errors

TARGET = project1_jstrokus_205

LIBS = -lm

all: $(TARGET) 

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(LIBS)

clean: 
	rm $(TARGET)
