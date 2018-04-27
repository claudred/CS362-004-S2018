CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
	
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)
	
test_helpers.o: test_helpers.h test_helpers.c
	gcc -c test_helpers.c -g $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
	./unittest1

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
	./unittest2

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
	./unittest3

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
	./unittest4

cardtest1: cardtest1.c dominion.o rngs.o test_helpers.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o test_helpers.o $(CFLAGS)
	./cardtest1

cardtest2: cardtest2.c dominion.o rngs.o test_helpers.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o test_helpers.o $(CFLAGS)
	./cardtest2

cardtest3: cardtest3.c dominion.o rngs.o test_helpers.o
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o test_helpers.o $(CFLAGS)		
	./cardtest3

cardtest4: cardtest4.c dominion.o rngs.o test_helpers.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o test_helpers.o $(CFLAGS)
	./cardtest4
mytests: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 dominion.o

unittestresults.out: mytests
	
	gcov unittest1.c -b > unittestresults.out
	gcov unittest2.c -b>> unittestresults.out
	gcov unittest3.c -b>> unittestresults.out
	gcov unittest4.c -b>> unittestresults.out
	gcov cardtest1.c -b>> unittestresults.out
	gcov cardtest2.c -b>> unittestresults.out
	gcov cardtest3.c -b>> unittestresults.out
	gcov cardtest4.c -b>> unittestresults.out
	gcov dominion.c -b>> unittestresults.out
	
	cat unittest1.c.gcov >> unittestresults.out 
	cat unittest2.c.gcov >> unittestresults.out 
	cat unittest3.c.gcov >> unittestresults.out 
	cat unittest4.c.gcov >> unittestresults.out 
	cat cardtest1.c.gcov >> unittestresults.out 
	cat cardtest2.c.gcov >> unittestresults.out 
	cat cardtest3.c.gcov >> unittestresults.out 
	cat cardtest4.c.gcov >> unittestresults.out 
	cat dominion.c.gcov >> unittestresults.out
	
	./unittest1 >> unittestresults.out 
	./unittest2 >> unittestresults.out 
	./unittest3 >> unittestresults.out 
	./unittest4 >> unittestresults.out 
	./cardtest1 >> cardtestresults.out 
	./cardtest2 >> cardtestresults.out 
	./cardtest3 >> cardtestresults.out 
	./cardtest4 >> cardtestresults.out 
	
	
all: playdom player



clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
