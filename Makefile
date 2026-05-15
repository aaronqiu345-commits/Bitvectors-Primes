CFLAGS=-Wall -Wextra -Werror -pedantic 
CC=clang

all: primes

primes: primes.c bitvector.c
	$(CC) $(CFLAGS) primes.c bitvector.c -lm -o primes