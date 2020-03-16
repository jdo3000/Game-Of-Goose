# A simple Makefile
# Jeffrey Do G01133170
# CS 262, Lab section 207
# Project 1
# The compiler: gcc for C programs, g++ for C++ programs, etc

CC = gcc

CFLAGS = -Wall -g -O2 -std=c89 -D_XOPEN_SOURCE=600 -pedantic-errors
TARGET = project1_jdo4_207

LIBS = -lm

all: $(TARGET) 

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	rm $(TARGET)

