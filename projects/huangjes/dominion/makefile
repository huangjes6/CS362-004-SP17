CFLAGS = -Wall -fpic -coverage -fprofile-arcs -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g #(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g $(CFLAGS)

unittest1: dominion.o unittest1.c
	gcc -o unittest1 unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: dominion.o unittest2.c
	gcc -o unittest2 unittest2.c dominion.o rngs.o $(CFLAGS)

runtests: unittest1 unittest2
	./unittest1 &> unittestresults.out
	./unittest2 &> unittestresults.out
	gcov -b -f dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

all: unittest1 unittest2

clean:
	rm -f *.o unittest1.exe unittest1 unittest2 *.gcov *.gcda *.gcno *.so *.out
