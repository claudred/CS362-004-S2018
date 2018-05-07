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
	printf("----STARTING RANDOM TESTS----\n\n\n");
	printf("----Welcome to randomtestcard1.c, home of Random Card Test 1----\n");
	printf("----This file facilitates random  tests for the Smithy Card ----\n");
	printf("-----Smithy is an Action card from the Base Set----\n");
	printf("-----Smithy's purpose is to increase the handside by drawing three cards----\n");
	printf("-----Smithy is a terminal card, meaning that it provides no +Action---\n");
	
	int card=smithy;
	int numPlayers=2;
	int seed=420;
	int handpos=0;
	int choice1=0;
	int choice2=0;
	int choice3=0;
	int bonus = 0;
	struct gameState *smithyTest=newGame();
	struct gameState *save=newGame();
	int *smithyTestKC=kingdomCards(adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy);
	initializeGame(numPlayers, smithyTestKC, seed, smithyTest);
	*save=*smithyTest;
	printf("TEST CASE PARAMETERS: %i players, ", smithyTest->numPlayers);
	//relevant player=rp
	int rp=smithyTest->whoseTurn;
	printf("testing with player %i.\n", rp+1);
	//placing Smithy in players hand
	printf("Placing Smithy (enum %i) in player %i's hand at position %i\n",smithy, rp, handpos);
	
	smithyTest->hand[rp][handpos]=smithy;
	//hcb=hand count before
	int hcb=smithyTest->handCount[rp];
	printf("Player %i's handcount before being run is %i", rp, hcb);
	
	//played card count before
	int pccb=smithyTest->playedCardCount;
	printf("The overall played card count before playing is %i", pccb);
	
	//pcsb=played card status before
	int pcsb=smithyTest->playedCards[pccb];
	
	//exPCCA=expected played card count after
	int exPCCA=pccb+1;
	//exHCA=expected hand count after: draw three, discard Cthis one; result in 2to more
	int exHCA=hcb+2;
	//exPCSA=expecte played card status after
	//int exPCSA=smithy;
	
	//actHCA=actual hand count after
	int actHCA=0;
	
	printf("Player %i's hand count before cardEffect is called with Smithy is: %i\n", rp+1, hcb);
	printf("Here is the deck state before\n");
//	printPlayerDeck(rp, smithyTest);
	printf("The games played card count before is %i\n", pccb);
	//printf("Games last played card is %i\n", pcsb);
	int randomCounter=0;//This keeps track of which random test case we are running. 
	//The first test randomizes the handpos of the smithy card i.e. the placement of the card
	//the lower boundary is -1 and the upper boundary is one plus the handcount. 
	int lowerBoundary=-1;
	int upperBoundary=smithyTest->handCount[rp]+1;
	int numRandCounter=upperBoundary*2;
	int i;
	for (i=0; i < numRandCounter; i++)
	{
		//add one to 
		handpos=rand() % (upperBoundary+1);
		handpos--;	
		printf("randomly generated %i\n", handpos);
		randomCounter=i;
		printf("--TEST CASE %i: calling with card:\n%i, choice1: %i, choice2: %i, choice3: %i, smithyTest: %p, handpos: %i, bonus: %p--\n",randomCounter,  card, choice1, choice2, choice3, smithyTest, handpos, &bonus);
		cardEffect(card, choice1, choice2, choice3, smithyTest, handpos, &bonus);
		actHCA=smithyTest->handCount[rp];
	
		printf("--STEP 1: Checking hand counts--\n");
		if (actHCA==exHCA)
		{
			printf("SUCCESS: new handcount is %i\n", smithyTest->handCount[rp]);
		}
		else
		{	
			printf("FAILURE: handcount has %i cards instead of required %i\n", smithyTest->handCount[rp], save->handCount[rp]+2);
		}
		//printPlayerHand(rp, smithyTest);
		printf("--STEP 2: Checking that expected played card count matches actual played card count--\n");
		if (exPCCA!=smithyTest->playedCardCount)
		{
			printf("FAILURE: Expeted %i, got %i\n", exPCCA, smithyTest->playedCardCount);
		}
		else if (exPCCA==smithyTest->playedCardCount)
		{	
			printf("SUCCESS: Expected %i, got %i\n", exPCCA, smithyTest->playedCardCount);
		}
		printf("--CHECKING DISCARD FUNCTION--\n");
	
		/*printf("Checking that expected card was removed to 'played cards' from the deck for 5 test cases of handPos being 0 through %i\n", save->handCount[rp]);
		int i;
		int firstHC=save->handCount[rp];
		struct gameState *saveTwo=newGame();
		*saveTwo=*smithyTest;
		for (i=0; i < firstHC; i++)
		{
			printf("--TEST CASE %i for handpost %i--\n", i+2, i);
			handpos=i;
			cardEffect(card, choice1, choice2, choice3, smithyTest, handpos, &bonus);
			if (smithyTest->playedCards[smithyTest->playedCardCount-1]==save->hand[rp][handpos])
			{
				printf("SUCCESS: last played card matches saved hand in position %i: %i==%i\n", handpos, smithyTest->playedCards[smithyTest->playedCardCount-1], save->hand[rp][handpos]);
			}
			else
			{	
				printf("FAILURE: last played card does NOT match saved hand in position %i: %i!=%i\n", handpos, smithyTest->playedCards[smithyTest->playedCardCount-1], save->hand[rp][handpos]);
			}
			*smithyTest=*save;
		}*/
		if (smithyTest->playedCards[smithyTest->playedCardCount-1]==save->hand[rp][handpos])
                {
			printf("SUCCESS: last played card matches saved hand in position %i: %i==%i\n", handpos, smithyTest->playedCards[smithyTest->playedCardCount-1], save->hand[rp][handpos]);
		}
		else
              	{
			printf("FAILURE: last played card does NOT match saved hand in position %i: %i!=%i\n", handpos, smithyTest->playedCards[smithyTest->playedCardCount-1], save->hand[rp][handpos]);
		}
		printf("---TEST CASE %i finished--- \n", randomCounter);
	}
	//*smithyTest=*saveTwo;
	printf("\n\n\n----FINISHED ALL TESTS--\n");
	
	
	return 0;
}
