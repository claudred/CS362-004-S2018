#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
void rv_shuffle_deckCount(int rv, int rp);
int main(int argc, char *argv[]) 
{
	printf("Testing 'shuffle'\n");
	struct gameState* testShuffle=newGame();
	struct gameState* save=newGame();
	int numPlayers=2;
	int* kc=kingdomCards(adventurer, baron, council_room, feast, gardens, remodel, smithy, village, great_hall, minion);
	int randomSeed=1000;
	initializeGame(numPlayers, kc, randomSeed, testShuffle);
	//return value=rv;
	int rv=0;
	//save the state
	*save=*testShuffle;
	//relevant player=rp
	int rp=whoseTurn(testShuffle);
	//assume that all hands are now in deck array or hand or played and that the discard pile is empty
	printf("PRE-CONDITIONS: FOR TEST CASE 1:\n1.`shuffle()` is receiving an empty discard pile for player %i: ", rp);
	printf("testShuffle->discardCount[%i]:%i\n", rp, testShuffle->discardCount[rp]);
	shuffle(rp, testShuffle);
	printf("\n\nPRE-CONDITIONS: FOR TEST CASE 2: Empty player deck for player %i.\nShuffle checks the state of the players deck; if it is less than  1, it should return -1\n", rp);
	*testShuffle=*save;
	testShuffle->deckCount[rp]=0;
	rv=shuffle(rp, testShuffle);
	rv_shuffle_deckCount(rv, rp);
	//Running the following  statement would give us 100% in terms of "branches taken at least once"
	//but it does not make sense in this context
	//rv_shuffl_deckCount(0, rp);
	return 0;
}
void rv_shuffle_deckCount(int rv, int rp)
{
	if (rv==-1)
	{
		printf("SUCCESS: noted that the deckCount for player %i is less than one\n", rp);
	}
}
