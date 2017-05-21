CFLAGS = -Wall -std=c99 -fpic -coverage -fprofile-arcs -lm

default: unittestresults.out

unittestresults.out: cardtest1.c rngs.c dominion.c
	gcc -o cardtest1 cardtest1.c dominion.c rngs.c $(CFLAGS)
	cardtest1 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
clean:
	rm -f *.o unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 *.gcov *.gcda *.gcno *.so *.out
