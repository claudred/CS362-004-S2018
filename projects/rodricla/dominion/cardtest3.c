#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "test_helpers.h"

void testBuys(struct gameState *prev, struct gameState *after, int incBy);
int main(int argc, char *argv[]) 
{
	printf("----STARTING TESTS----\n\n\n");
	printf("----Welcome to cardtest3.c----\n");
	printf("----We will test the Council card in this unit test---\n");
	printf("---Council is an Action card from the Base Set----\n");
	printf("---It is a terminal Action card that forces each player to draw a card---\n");
	printf("---Itelf, it draws 4 cards for the player and give the player a buy---\n");
	
	
	/*Council Room is an Action card from the Base set. It is a terminal card draw, meaning it provides +Cards but no +Action. */
	//printf("Checks current hand count: TRUE\n");
	//printf("Checks other players card drawn: TRUE\n");
	//printf("Checks played card pile: TRUE\n");
	
	int card=council_room;
	int choice1=0;
	int choice2=0;
	int choice3=0;
	int handPos=0;
	int bonus=0;
	int numPlayers=3;
	int randomSeed=666;
	int *kc_cc=kingdomCards(council_room, adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, adventurer);
	struct gameState *council_roomTest=newGame();
	struct gameState *saveState=newGame();
	//rp=relevant player
	int rp=council_roomTest->whoseTurn;
	
	initializeGame(numPlayers, kc_cc, randomSeed, council_roomTest);
	printf("---TEST CASE 1: Inserting a council_room card into player %i's deck at hand position %i---\n", rp+1, handPos);
	
	printf("----TESTING WITH A DECK COUNT OF 10 COPPERS FOR EACH PLAYER---\n");
	int i=0;
	for (i=0; i < numPlayers; i++)
	{
		council_roomTest->deckCount[i]=10;
		int j;
		for (j=0; j < 10; j++)
		{
			council_roomTest->deck[i][j]=copper;
		}
		
	}
	int expected_hand_count_after=4;//draw 4
	int actual_hand_count_after=0;
	council_roomTest->hand[rp][handPos]=card;
	council_roomTest->handCount[rp]=1;
	printf("Player %i hand count before running council_case: %i\n", rp+1, council_roomTest->handCount[rp]);
	printf("Player %i hand at handPos %i before running council_case: %i\n", rp+1, handPos, council_roomTest->hand[rp][handPos]);
	
	*saveState=*council_roomTest;
	//council_roomTest->handCount[rp]=1;
	//council_roomTest->hand[rp][council_room]=1;

	//printf("player hand count before is: %i, hand is %i\n", council_roomTest->handCount[rp], council_roomTest->hand[rp][council_room]);
	
	cardEffect(card, choice1, choice2, choice3, council_roomTest, handPos, &bonus);
	printf("Player %i hand count after running council_case: %i\n", rp+1, council_roomTest->handCount[rp]);
	printf("New played card count is %i\n", council_roomTest->playedCardCount);
	
	printf("Played card is %i, should be %i\n", council_roomTest->playedCards[council_roomTest->playedCardCount-1], card);
	actual_hand_count_after=council_roomTest->handCount[rp];
	

	if (saveState->deckCount[rp]<council_roomTest->deckCount[rp])
	{
		printf("SUCCESS deck count is decremented: %i\n", council_roomTest->deckCount[rp]);
		if (saveState->deckCount[rp]-4==council_roomTest->deckCount[rp])
		{
			printf("SUCCESS deck count is decremented correctly by 4: %i\n", council_roomTest->deckCount[rp]);
		}
		else 
		{
			printf("FAILURE deck count is decremented incorrectly by another factor: %i\n", council_roomTest->deckCount[rp]);
		}
	}
	
	
	//TEST HAND COUNT AFTER:
	if (expected_hand_count_after==actual_hand_count_after)
	{
		printf("SUCCESS: Hand count after, %i, matches expected hand count, %i\n", actual_hand_count_after, expected_hand_count_after);
	}
	else if (expected_hand_count_after!=actual_hand_count_after)
	{
		printf("FAILURE: Hand count after, %i, does NOT match expected hand count, %i\n", actual_hand_count_after, expected_hand_count_after);
	}

	//printf("")

	//printf("INTERNAL RULES FOR COUNCIL CASE\n");
	//printf("BUSINESS RULES FOR COUNCIL CASE\n");
	//cost: 5 coins
	
	//type: action 
	//set: base
	//Rule1: other players 
	//Rule2: other players draw a card
	//Rule3: discard the card
	//attributes; terminal card draw
	
	printf("----STEP 3: CHECKING THAT OTHER PLAYERS DREW CARDS---\n");

	printf(" PREV HAND COUNT FOR PLAYER 1 %i\n", saveState->handCount[1]);
	for (i=0; i < numPlayers; i++)
	{
		if (i!=rp)
		{
			if (saveState->handCount[i]+1==council_roomTest->handCount[i])
			{
				printf("SUCCESS: player %i hand incremented by one: %i\n", i, council_roomTest->handCount[i]);
			}
			else if (saveState->handCount[i]!=council_roomTest->handCount[i]+1)
			{
				printf("FAILURE: player %i hand NOT incremented by one:  %i\n", i, council_roomTest->handCount[i]);			
			}
		}
	}
	if (checkLastPlayed(council_room, council_roomTest)==1)
	{
		printf("SUCCESS: last played card is council_room\n");
	}
	else if (checkLastPlayed(council_room, council_roomTest)==0)
	{
		printf("FAILURE last played card is enumed %i\n", council_roomTest->playedCards[council_roomTest->playedCardCount-1]);
	}
	testBuys(saveState, council_roomTest, 1);

	printf("\n\n\n----FINISHED ALL TESTS--\n");
	return 0;	
}
void testBuys(struct gameState *prev, struct gameState *after, int incBy)
{
	if (prev->numBuys+incBy==after->numBuys)
	{
		printf("SUCCESS: num buys incremented by %i\n", incBy);
	}
	else 
	{
		printf("FAILURE: num buys not incremented by %i; prev numbuys=%i, current numBuys=%i\n", incBy, prev->numBuys, after->numBuys);
	}
	
}
