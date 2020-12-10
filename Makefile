CC = gcc
CFLAGS = -pedantic -Wall -Wextra -O2

.PHONY: clean

solution: main.o TAvl.o TAvlQueue.o
	$(CC) $(CFLAGS) $^ -o $@
	
main.o: main.c TAvl.h
	$(CC) $(CFLAGS) -c $< -o $@
	
TAvl.o: TAvl.c TAvl.h
	$(CC) $(CFLAGS) -c $< -o $@

TAvlQueue.o: TAvlQueue.c TAvlQueue.h TAvl.h
	$(CC) $(CFLAGS) -c $< -o $@	

clean:
	rm -f solution *.o

