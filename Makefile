#Dan-Dominic Staicu 311CA

CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -lm
FILES=$(wildcard *.c)

all: clean build run

build: my_av

my_av: my_av.c
	$(CC) -o my_av -g $(FILES) $(CFLAGS) -DVARIATION

my_av_var: my_av.c
	$(CC) -o my_av $(FILES) $(CFLAGS)

run:
	./my_av

pack:
	zip -9 -FSr 311CA_StaicuDan-Dominic.zip my_av.py *.c *.h Makefile README

clean:
	rm -f my_av
