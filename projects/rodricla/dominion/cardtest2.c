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
	printf("----STARTING TESTS----\n\n\n");
	printf("----Welcome to cardtest2.c----\n");
	printf("----We will test the Adventurer card in this unit test----\n");
	printf("----Adventurer is an Action card from the Base Set----\n");
	printf("-----It is a terminal Action card that digs for Treasure cards in the deck-----\n");
	printf("----TEST 1: If there is treasure in the players deck it should draw it-----\n");
	
	struct gameState *testAdventurer=newGame();
	
	int* kc_ac=kingdomCards(adventurer, smithy, embargo, village, minion, mine, cutpurse, sea_hag, tribute, baron);
	int numPlayers=2;
	int randomSeed=random();
	int card=adventurer;
	int choice1=0;
	int choice2=0; 
	int choice3=0;
	int handPos=0;
	int bonus=0;
	//relevant player we're testing.
	int rp=-1;	
	initializeGame(numPlayers, kc_ac, randomSeed, testAdventurer);
	testAdventurer->hand[rp][handPos]=adventurer;
	printSupplyCount(testAdventurer);
	
	struct gameState *save=newGame();
	*save=*testAdventurer;
	rp=whoseTurn(testAdventurer);
	printPlayerDeck(rp, testAdventurer);
	printf("PLAYER: %i\n", rp);
	printf("At this point, we know that the player should have only treasure in the deck; so we expect that the hand count before and after should differ by two counts\n");
	printf("Player's hand count before: %i\n", testAdventurer->handCount[rp]);
	printPlayerDeck(rp, testAdventurer);
	cardEffect(card, choice1, choice2, choice3, testAdventurer, handPos, &bonus);	
	/*if (checkLastPlayed(adventurer, testAdventurer)==1)
	{
		printf("SUCCESS: Last played card was adventurer\n");
	}
	else {
		printf("FAILURE: last played card was: %i\n", testAdventurer->playedCards[testAdventurer->playedCardCount]);
	}
	if (checkLastDiscard(rp, card, testAdventurer)==1)
	{
		printf("LAST DISCARDED CARD IS %i\n", testAdventurer->discard[rp][testAdventurer->discardCount[rp]]);
	}*/

	printf("Player's hand count after: %i\n", testAdventurer->handCount[rp]);
	if (save->handCount[rp]+2==testAdventurer->handCount[rp])
	{
		printf("SUCCESS: correct number of items incremented from the count\n");
		
	}
	else 
	{
		printf("FAILURE: incorrect number of items incremented from the count\n");
	}
	printf("Checking player deck count\n");
	if (save->deckCount[rp]-2==testAdventurer->deckCount[rp])
	{
		printf("SUCCESS: correct number of treasure cards mined\n");
	}
	else 
	{
		printf("FAILURE: incorrect number of treasure cards mined\n");
	}
	printPlayerDeck(rp, testAdventurer);
	printf("TEST CASE 2: No treasure in deck; \n");
	*testAdventurer=*save;
	rp=whoseTurn(testAdventurer);
	printf("Setting all cards for player %i's deck to curse\n", rp);
	int i=0;
	for (i=0; i < testAdventurer->deckCount[rp]+1; i++)
	{
		testAdventurer->deck[rp][i]=0;
	}
	printPlayerDeck(rp, testAdventurer);
	printf("Discard count before call %i\n", testAdventurer->discardCount[rp]);
	printf("Testing card effect with only curse cards in deck; expecting discard count to increment by 5\n");
	cardEffect(card, choice1, choice2, choice3, testAdventurer, handPos, &bonus);
	printPlayerDeck(rp, testAdventurer);
	printPlayerHand(rp, testAdventurer);
	if (save->discardCount[rp]+5==testAdventurer->discardCount[rp])
	{
		printf("SUCCESS: discard count is %i\n", testAdventurer->discardCount[rp]);
	}
	else 
	{
		printf("FAILURE: discard count is %i\n", testAdventurer->discardCount[rp]);
	}
	printDiscard(rp, testAdventurer);
	/*
	cardEffect(card, choice1, choice2, choice3, testAdventurer, handPos, &bonus);	
	printPlayerDeck(rp, testAdventurer);
	cardEffect(card, choice1, choice2, choice3, testAdventurer, handPos, &bonus);	
	printPlayerDeck(rp, testAdventurer);*/
	printf("\n\n\n----FINISHED ALL TESTS--\n");

}

/*

//ADVENTURE CARD

*/

/**************

		

**************/