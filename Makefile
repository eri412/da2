CC = gcc
CFLAGS = -pedantic -Wall -Wextra -pg

.PHONY: clean

solution: main.o TAvl.o TAvlStack.o
	$(CC) $(CFLAGS) $^ -o $@
	
main.o: main.c TAvl.h
	$(CC) $(CFLAGS) -c $< -o $@
	
TAvl.o: TAvl.c TAvl.h
	$(CC) $(CFLAGS) -c $< -o $@

TAvlStack.o: TAvlStack.c TAvlStack.h TAvl.h
	$(CC) $(CFLAGS) -c $< -o $@	

clean:
	rm -f solution *.o

