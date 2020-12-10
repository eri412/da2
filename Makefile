CC = gcc
CFLAGS = -pedantic -Wall -Wextra -Wno-unused-but-set-variable -O2

.PHONY: clean

solution: main.c TAvl.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f solution

