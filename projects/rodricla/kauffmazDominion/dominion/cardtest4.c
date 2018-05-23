#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "test_helpers.h"

int main(int argc, char *argv[]) 
{

	//an introduction
	printf("----Welcome to cardtest4.c-----\n");
	printf("----This file facilitates unit tests for the Baron Card---\n");
	printf("----Baron is an Action card from the Intigue Set----\n");
	printf("----To run, we need to have a current player, a game state, and a parameter called 'choice1' which tells us whether or not to 'discard' the estate card, which is enumerated in the CARD enum by '1'.\n");
	//end introduction
	//THING TO NOTE:
		//1. If estate exists, it is in testBaron->hand[rp][0...n] where n is the size of the hand i.e. testBaron->handCount[rp]
	//THINGS TO TEST:
		//1. Number of buys before and after should increase by 1
		//2. That baron works and does NOT discard estate when choice1 is 0
		//3. That baron works and DOES discard estate when choice1 is 1
			//3.1. If estate is found, that coins have 4 added to them
			//3.2 That discard pile has item added and that the discard count has gone up

		//4. That the state doesn't change if estate does not exist to be discarded.
		//initialize necessary items:
	int numPlayers=3;
	int kingdomCards[10]={adventurer, smithy, embargo, village, minion, mine, cutpurse, sea_hag, tribute, baron};
	int randomSeed=69;
	struct gameState *testBaron=newGame();
	int card=baron;
	int choice1=0;
	int choice2=0;
	int choice3=0;
	int handPos=0;
	int bonus=0;
	int rp=0;
	initializeGame(numPlayers, kingdomCards, randomSeed, testBaron);
	rp=whoseTurn(testBaron);
	testBaron->hand[rp][handPos]=baron;
	int rpHandCountBefore=testBaron->handCount[rp];
	int rpHandCountAfter=0;
	int i;
	for (i=0; i <rpHandCountBefore; i++)
	{
		printf("Before card %i is %i\n", i, testBaron->hand[rp][i]);
	}
	int numCoinsBefore=testBaron->coins;
	int numCoinsAfter=0;
	int discardPileBefore=testBaron->discardCount[rp];
	int discardPileAfter=0;
	printf("--TESTING THAT: 1. Number of buys before and after should increase by 1----\n");
	int prevNumBuys=testBaron->numBuys;
	int expNumBuys=prevNumBuys+1;
	int aftNumBuys=0;
	cardEffect(card, choice1, choice2, choice3, testBaron, handPos, &bonus);
	aftNumBuys=testBaron->numBuys;
	printf("Number of Buys Before: %i\n", prevNumBuys);
	printf("Number of Buys After: %i\n", aftNumBuys);
	printf("Expected Num Buys After: %i\n", expNumBuys);
	if (expNumBuys!=aftNumBuys)
	{
		printf("FAILURE: expected and actual number of buys don't match\n");
	}
	else 
	{
		printf("SUCCESS: expected and actual number of buys match\n");		
	}
	printf("TESTING THAT: 2.That baron works and does NOT discard estate when choice1 is 0\n");
	rpHandCountAfter=testBaron->handCount[rp];
	if (rpHandCountAfter==rpHandCountBefore)
	{
		printf("SUCCESS: handcount is the same before and after\n");
		for (i=0; i <rpHandCountAfter; i++)
		{
			printf("After card %i is %i\n", i, testBaron->hand[rp][i]);
		}

	}
	else if (rpHandCountAfter!=rpHandCountBefore)
	{
		printf("FAILURE: handcount is NOT the same before and after\n");
		for (i=0; i <rpHandCountAfter; i++)
		{
			printf("After card %i is %i\n", i, testBaron->hand[rp][i]);
		}

	}
	printf("TESTING THAT: 3.That baron works and DOES discard estate when choice1 is 1\n");
	choice1=1;
	discardPileBefore=testBaron->discardCount[rp];
	cardEffect(card, choice1, choice2, choice3, testBaron, handPos, &bonus);
	rpHandCountAfter=testBaron->handCount[rp];
	if (rpHandCountAfter!=rpHandCountBefore)
	{
		printf("SUCCESS: handcount is different efore and after\n");
		for (i=0; i <rpHandCountAfter; i++)
		{
			printf("After card %i is %i\n", i, testBaron->hand[rp][i]);
		}
		printf("TESTING THAT: 3.1. If estate is found, that coins have 4 added to them\n");
		numCoinsAfter=testBaron->coins;
		if (numCoinsAfter==numCoinsBefore)
		{
			printf("FAILURE: number of coins unchanged\n");
		}
		else if (numCoinsAfter==numCoinsBefore+4)
		{
			printf("SUCCESS: number of coins incremented by 4\n");
		}
		else
		{
			printf("FAILURE: number of coins differs but not by correct fator\n");
		}

	}
	else if (rpHandCountAfter==rpHandCountBefore)
	{
		printf("FAILURE: handcount is NOT different before and after\n");
		for (i=0; i <rpHandCountAfter; i++)
		{
			printf("After card %i is %i\n", i, testBaron->hand[rp][i]);
		}
	
	}
	printf("TESTING THAT: 3.2 That discard pile has item added and that the discard count has gone up\n");
	discardPileAfter=testBaron->discardCount[rp];
	if (discardPileAfter==discardPileBefore)
	{
		printf("FAILURE: discard count unchanged\n");
	}
	else if (discardPileAfter==discardPileBefore+1)
	{
		printf("SUCCESS: discard count incremented by one\n");
	}
	else 
	{
		printf("FAILURE discard counts differ but by incorrect factor: before %i, after %i\n", discardPileBefore, discardPileAfter);
	}
	printf("TESTING THAT: 4. That the state doesn't change if estate does not exist to be discarded.\n");
	printf("SETTING ALL CARDS TO CURSE CARDS\n");
	rp=whoseTurn(testBaron);
	rpHandCountBefore=testBaron->handCount[rp];
	for (i=0; i <rpHandCountBefore; i++)
	{
		testBaron->hand[rp][i]=0;
	}
	cardEffect(card, choice1, choice2, choice3, testBaron, handPos, &bonus);
	rpHandCountAfter=testBaron->handCount[rp];
	
	rpHandCountAfter=testBaron->handCount[rp];
	if (rpHandCountAfter==rpHandCountBefore)
	{
		printf("SUCCESS: handcount is the same before and after\n");
		for (i=0; i <rpHandCountAfter; i++)
		{
			printf("After card %i is %i\n", i, testBaron->hand[rp][i]);
		}

		}
		else if (rpHandCountAfter!=rpHandCountBefore)
		{
			printf("FAILURE: handcount is NOT the same before and after\n");
			for (i=0; i <rpHandCountAfter; i++)
			{
				printf("After card %i is %i\n", i, testBaron->hand[rp][i]);
			}

		}
	printf("---All tests finished---\n\n");
	return 0;
	
	
}
