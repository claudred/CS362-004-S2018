#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>
void rv_shuffle_deckCount(int rv, int rp);
int check_shuffle(int player, struct gameState *one, struct gameState *two);
int main(int argc, char *argv[]) 
{
	printf("-------UNIT TEST 1------\n");
	printf("---Testing 'shuffle'---\n");
	struct gameState* testShuffle=newGame();
	struct gameState* save=newGame();
	int numPlayers=2;
	int* kc=kingdomCards(adventurer, baron, council_room, feast, gardens, remodel, smithy, village, great_hall, minion);
	int randomSeed=1000;
	initializeGame(numPlayers, kc, randomSeed, testShuffle);
	//return value=rv
	int rv=0;
	//save the state
	*save=*testShuffle;
	int rp=whoseTurn(testShuffle);
	//assume that all hands are now in deck array or hand or played and that the discard pile is empty
	printf("PRE-CONDITIONS: FOR TEST CASE 1:\n1.`shuffle()` is receiving an empty discard pile for player %i:\n ", rp);
	printf("testShuffle->discardCount[%i]:%i\n", rp, testShuffle->discardCount[rp]);
	
	rv=shuffle(rp, testShuffle);
	if (rv==0)
	{
		printf("shuffle returned 0, indicating success; checkign deck\n");
		if (check_shuffle(rp, save, testShuffle)>0)
		{
			printf("OVERALL: Success, at least one item changed in deck\n");
		}
		else 
		{
			printf("OVERALL: Failure, not even one item changed in deck\n");
		}
	}
	

	
	printf("\n\nPRE-CONDITIONS: FOR TEST CASE 2: Empty player deck for player %i.\nShuffle checks the state of the players deck; if it is less than  1, it should return -1\n", rp);
	*testShuffle=*save;
	testShuffle->deckCount[rp]=0;
	rv=shuffle(rp, testShuffle);
	
	rv_shuffle_deckCount(rv, rp);
	//after running rv_shuffle_deckCount with -1 and some rp, running the followign statement would give us 100% coverage for the rv_shuffle_deckount branches, but I don't know how to trick "shuffled" into ignoring an empty deck.
	//rv_shuffle_deckCount(0, rp);
	
	printf("-------FINISHED UNIT TEST 1------\n");
	return 0;
	
}
void rv_shuffle_deckCount(int rv, int rp)
{
	if (rv==-1)
	{
		printf("SUCCESS: noted that the deckCount for player %i is less than one\n", rp);
	}
	else if (rv!=-1)
	{
		printf("FAILURE: did not note that the deckCount for player %i is less than one, returned %i\n", rp, rv);
	}
}
int check_shuffle(int player, struct gameState *one, struct gameState *two)
{
	int n=one->deckCount[player];
	int i;
	int failureCount=0;
	int successCount=0;
	for (i=0; i < n; i++)
	{
		if (one->deck[player][i]==two->deck[player][i])
		{ 
			printf("FAILURE: card for player %i at %i the same as before: %i and %i\n", player,  i, one->deck[player][i], two->deck[player][i]);
			failureCount++;
		}
		else 
		{
			printf("SUCCESS: card for player %i at %i NOT the same as before: %i and %i\n", player,  i, one->deck[player][i], two->deck[player][i]);
			successCount++;
		}
	}
	return successCount;
}
/*
int shuffle(int player, struct gameState *state) {
 

	int newDeck[MAX_DECK];
	int newDeckPos = 0;
	int card;
	int i;

	if (state->deckCount[player] < 1)
		return -1;
	qsort ((void*)(state->deck[player]), state->deckCount[player], sizeof(int), compare); 
	//SORT CARDS IN DECK TO ENSURE DETERMINISM!

	while (state->deckCount[player] > 0) {
		card = floor(Random() * state->deckCount[player]);
		newDeck[newDeckPos] = state->deck[player][card];
		newDeckPos++;
		for (i = card; i < state->deckCount[player]-1; i++) {
			state->deck[player][i] = state->deck[player][i+1];
		}
		state->deckCount[player]--;
	}
	for (i = 0; i < newDeckPos; i++) {
		state->deck[player][i] = newDeck[i];
		state->deckCount[player]++;
	}

	return 0;
}

*/
