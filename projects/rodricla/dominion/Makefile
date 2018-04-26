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
	
unittest1: unittest1.c dominion.c rngs.c
	gcc unittest1.c dominion.c rngs.c test_helpers.c -o unittest1 $(CFLAGS)
	gcc unittest1.c dominion.c rngs.c test_helpers.c -o unittest1 -coverage -fpic -lm
	./unittest1
	
unittest2: unittest2.c dominion.c rngs.c
	gcc unittest2.c dominion.c rngs.c test_helpers.c -o unittest2 $(CFLAGS)
	gcc unittest2.c dominion.c rngs.c test_helpers.c -o unittest2 -coverage -fpic -lm
	./unittest2

unittest3: unittest3.c dominion.c rngs.c
	gcc unittest3.c dominion.c rngs.c test_helpers.c -o unittest3 $(CFLAGS)
	gcc unittest3.c dominion.c rngs.c test_helpers.c -o unittest3 -coverage -fpic -lm
	./unittest3
	
unittest4: unittest4.c dominion.c rngs.c		
	gcc unittest4.c dominion.c rngs.c test_helpers.c -o unittest4 $(CFLAGS)
	gcc unittest4.c dominion.c rngs.c test_helpers.c -o unittest4 -coverage -fpic -lm
	./unittest4
	
cardtest1: cardtest1.c dominion.c rngs.c
	gcc cardtest1.c dominion.c rngs.c test_helpers.c -o cardtest1 $(CFLAGS)
	gcc cardtest1.c dominion.c rngs.c test_helpers.c -o cardtest1 -coverage -fpic -lm
	./cardtest1
		
cardtest2: cardtest2.c dominion.c rngs.c
	gcc cardtest2.c dominion.c rngs.c test_helpers.c -o cardtest2 $(CFLAGS)
	gcc cardtest2.c dominion.c rngs.c test_helpers.c -o cardtest2 -coverage -fpic -lm
	./cardtest2

cardtest3: cardtest3.c dominion.c rngs.c
	gcc cardtest3.c dominion.c rngs.c test_helpers.c -o cardtest3 $(CFLAGS)
	gcc cardtest3.c dominion.c rngs.c test_helpers.c -o cardtest3 -coverage -fpic -lm
	./cardtest3
		
cardtest4: cardtest4.c dominion.c rngs.c 		
	gcc cardtest4.c dominion.c rngs.c test_helpers.c -o cardtest4 $(CFLAGS)
	gcc cardtest4.c dominion.c rngs.c test_helpers.c -o cardtest4 -coverage -fpic -lm
	./cardtest4

mytests: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 dominion.o

unittestresults.out: mytests
	gcov unittest1.c -b>> unittestresults.out
	gcov unittest2.c -b>> unittestresults.out
	gcov unittest3.c -b>> unittestresults.out
	gcov unittest4.c -b>> unittestresults.out
	gcov cardtest1.c -b>> unittestresults.out
	gcov cardtest2.c -b>> unittestresults.out
	gcov cardtest3.c -b>> unittestresults.out
	gcov cardtest4.c -b>> unittestresults.out
	
	cat unittest1.c.gcov >> unittestresults.out 
	cat unittest2.c.gcov >> unittestresults.out 
	cat unittest3.c.gcov >> unittestresults.out 
	cat unittest4.c.gcov >> unittestresults.out 
	cat cardtest1.c.gcov >> unittestresults.out 
	cat cardtest2.c.gcov >> unittestresults.out 
	cat cardtest3.c.gcov >> unittestresults.out 
	cat cardtest4.c.gcov >> unittestresults.out 
	
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
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 unittestresults.out
