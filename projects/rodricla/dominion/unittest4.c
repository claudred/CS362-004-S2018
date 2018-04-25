#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
int main(int argc, char *argv[]) 
{
	printf("testing function `buyCard`, which takes parameters 'int supplyPos', and 'struct gameState *state'\n");
	printf("-----START: TEST CASES 1 to 27------\n\n");
	//printf("%i", treasure_map);
	int all_cards[27]={0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26};
	int i=0; 
	struct gameState *testGame=newGame();
	int *kc1=kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);
	initializeGame(2, kc1, 3, testGame);
	printf("You start the game with %i coins\n", testGame->coins);
	int returnVal=0;
	int num_buys_before=0;
	int num_buys_after=0;
	int coins_before=0;
	int coins_after=0;
	int card_cost=0;
	int num_card_before=0;
	
	for (i=0; i < 27; i++)
	{
		coins_before=testGame->coins;
		num_buys_before=testGame->numBuys;
		num_card_before=testGame->supplyCount[i];
		printf("STATUS BEFORE: coins: %i, buys: %i, number of %i card left: %i\n", coins_before, num_buys_before, i, num_card_before);
		printf("TESTING BUYCARD with card %i\n", i);
		returnVal=buyCard(i, testGame);
		card_cost=getCost(i);
		if (num_card_before<=0)
		{
			if (returnVal==-1)
			{
				printf("SUCCESS: registered that the number of cards was not enough to buy\n");
			}
			else {
				printf("FAILURE: did not register that the number of cards was not enough to buy\n");
			}

		}
		if (card_cost>coins_before)
		{
			if (returnVal==-1)
			{
				if (coins_after==coins_before)
				{
					printf("SUCCESS: registered that did not have enough money to buy cards and did not charge\n");
					
				}
			}
			else 
			{
				printf("FAILURE: did not register that did not have enough money to buy cards.\n");
			}
				
		}
		else if (card_cost<coins_before)
		{
			if (returnVal==-1)
				printf("FAILURE: had enough money to buy cards but some issue occurred; or SUCCESS if other issue shown\n");
			else if (coins_after==coins_before-card_cost)
				printf("SUCCESS: coins after are equal to coins before minus the coin cost\n");
		}
		
		
	
		printf("STATUS AFTER:  coins: %i, buys: %i, number of %i card left: %i\n", testGame->coins, testGame->numBuys, i, testGame->supplyCount[i]);
		printf("%i\n", returnVal);
		printf("RE-ADDING COINS, CARDs AND NUM BUYS TO KEEP TESTING\n");
		testGame->coins=coins_before;
		testGame->numBuys=num_buys_before;
		testGame->supplyCount[i]=num_card_before;
		
		
	}
	printf("-----FINISHED: TEST CASE 1-27------\n\n");

}