#Copyright by Ana Stanciulescu 312CA 30.11.2023

CC= gcc
CFLAGS= -g -Wall -Wextra -std=c99 -pedantic -ggdb3

TARGETS = my_octave

build: $(TARGETS)

my_octave: my_octave.c
	$(CC) $(CFLAGS) my_octave.c -o my_octave

pack:
	zip -FSr 312CA_StanciulescuAna_Tema2.zip README Makefile *.c *.h

clean: 
	rm -f $(TARGETS)

.PHONY: pack clean