#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
//function that tests the rv=return value of a shuffle deck and compares it to the deckCount of a specific player
void rv_shuffle_deckCount(int rv, int rp);
int main()
{
	struct gameState* testShuffle=newGame();
	struct gameState* save=newGame();
	int numPlayers=2;
	int* kc=kingdomCards(adventurer, baron, council_room, feast, gardens, remodel, smithy, village, great_hall, minion);
	int randomSeed=1000;
	initializeGame(numPlayers, kc, randomSeed, testShuffle);
	//rv=relevant player
	int rv=0;
	//save the state of the game
	*save=*testShuffle;
	int rp=whoseTurn(testShuffle);
	//assume that all hands are now in deck array or hand or played and that the discard pile is empty
	printf("PRE-CONDITIONS: FOR TEST CASE 1:\n1.`shuffle()` is receiving an empty discard pile for player %i: ", rp);
	printf("testShuffle->discardCount[%i]:%i\n", rp, testShuffle->discardCount[rp]);
	shuffle(rp, testShuffle);
	printf("\n\nPRE-CONDITIONS: FOR TEST CASE 2: Empty player deck for player %i.\nShuffle checks the state of the players deck; if it is less than  1, it should return -1\n", rp);
	*testShuffle=*save;
	testShuffle->deckCount[rp]=0;
	rv=shuffle(rp, testShuffle);
	//Running the followign statement would give us 100% 
	//rv_shuffle_deckCount(0, rp);
	rv_shuffle_deckCount(rv, rp);
	
	return 0;
}
void rv_shuffle_deckCount(int rv, int rp)
{
	
	if (rv==-1)
	{
		printf("SUCCESS: function noted that player %i deck was empty, and returned %i\n", rp, rv);
	}
	else if (rv!=-1)
	{
		printf("FAILURE: did not note that the deckCount for player %i is less than one, returned %i\n", rp, rv);
	}
	
}

