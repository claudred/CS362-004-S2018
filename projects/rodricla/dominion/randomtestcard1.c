#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "test_helpers.h"
#include <string.h>

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
	int seed=450;
	int handpos=0;
	int choice1=0;
	int choice2=0;
	int choice3=0;
	int bonus = 0;
	struct gameState *smithyTest=newGame();
	struct gameState *save=newGame();
	
	struct gameState *blankSave=newGame();
	int *smithyTestKC=kingdomCards(adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy);
	initializeGame(numPlayers, smithyTestKC, seed, smithyTest);
	*blankSave=*smithyTest;
	*save=*smithyTest;
	printf("TEST CASE PARAMETERS: %i players, ", smithyTest->numPlayers);
	//relevant player=rp
	int rp=smithyTest->whoseTurn;
	printf("testing with player %i.\n", rp+1);
	//hcb=hand count before
	int hcb=smithyTest->handCount[rp];
	printf("Player %i's handcount before being run is %i\n", rp, hcb);
	//played card count before
	int pccb=smithyTest->playedCardCount;
	printf("The overall played card count before playing is %i\n", pccb);
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
	printf("The games played card count before is %i\n", pccb);
	//printf("Games last played card is %i\n", pcsb);
	int randomCounter=0;//This keeps track of which random test case we are running. 
	//The first test randomizes the handpos of the smithy card i.e. the placement of the card
	//the lower boundary is -1 and the upper boundary is one plus the handcount. 
	int lowerBoundary=-1;
	int upperBoundary=smithyTest->handCount[rp]+1;
	int numRandCounter=upperBoundary*2;
	int handPosSuccessCount=0;
	int handPosFailureCount=0;
	int totalHandPosTests=3;
	int i;
	for (i=0; i < numRandCounter; i++)
	{
		//add one to upperBoundary so that when we decrement it later it still goes up to the
		//upper boundary
		handpos=rand() % (upperBoundary+1);
		//decrement so that chance of zero exists.
		handpos--;	
		printf("randomly generated %i from range of %i to %i in valid options of %i to %i\n", handpos, -1, upperBoundary, 0, smithyTest->handCount[rp]-1);
		randomCounter=i;
		printf("Placing Smithy (enum %i) in player %i's hand at position %i\n",smithy, rp, handpos);
	
		smithyTest->hand[rp][handpos]=smithy;
		
		printf("--TEST CASE %i: calling with card:\n%i, choice1: %i, choice2: %i, choice3: %i, smithyTest: %p, handpos: %i, bonus: %p--\n",randomCounter,  card, choice1, choice2, choice3, smithyTest, handpos, &bonus);
		*save=*smithyTest;
		cardEffect(card, choice1, choice2, choice3, smithyTest, handpos, &bonus);
		actHCA=smithyTest->handCount[rp];
	
		printf("--STEP 1: Checking hand counts--\n");
		if (actHCA==exHCA)
		{
			printf("SUCCESS: new handcount is %i\n", smithyTest->handCount[rp]);
			handPosSuccessCount++;
		}
		else
		{	
			printf("FAILURE: handcount has %i cards instead of required %i\n", smithyTest->handCount[rp], save->handCount[rp]+2);
			 handPosFailureCount++;
		}
		printf("--STEP 2: Checking that expected played card count matches actual played card count--\n");
		if (exPCCA!=smithyTest->playedCardCount)
		{
			printf("FAILURE: Expected %i, got %i\n", exPCCA, smithyTest->playedCardCount);
			handPosFailureCount++;
		}
		else if (exPCCA==smithyTest->playedCardCount)
		{	
			
			printf("SUCCESS: Expected %i, got %i\n", exPCCA, smithyTest->playedCardCount);
			handPosSuccessCount++;
		}
		printf("--STEP 3: Checking that corect card is discarded---\n");
		if (smithyTest->playedCards[save->playedCardCount]==save->hand[rp][handpos])
        {
			printf("SUCCESS: last played card matches saved hand in position %i: the %ith played card is  %i which matches the card formerly in the player hand, %i\n", handpos, save->playedCardCount,  smithyTest->playedCards[save->playedCardCount], save->hand[rp][handpos]);
			handPosSuccessCount++;
			
		}	
		else
       {
			printf("FAILURE; last played card DOES NOT  match saved hand in position %i:th %i the played card is  %i which does NOT match the card formerly in the player hand, %i\n", handpos, save->playedCardCount,  smithyTest->playedCards[save->playedCardCount], save->hand[rp][handpos]);
			handPosFailureCount++;
		}
		printf("---TEST CASE %i finished, resetting game state to original--- \n", randomCounter);
		*smithyTest=*blankSave;
	}
	printf("\n---------$$$-----------\n%i ot of %i tests passed, \n%i failed, in total\n---------$$$-----------\n", handPosSuccessCount, 3*numRandCounter, handPosFailureCount);

	//a second set of tests for random testing regarding the players that we choose
	printf("\n\n########### STARTING SECOND SET OF TESTS WITH RANDOM VARIABLE: PLAYERS ###########\n\n\n");
	handpos=0;
	int j=0;
	for (j=0; j < MAX_PLAYERS*2; j++)
	{
		printf("\n-----Running outer loop random test number %i-----\n", j); 
		numPlayers=rand() % (MAX_PLAYERS-1);
		numPlayers=numPlayers+2;
		printf("Randomly selected to play with %i players\n", numPlayers);
		printf("Initializing Game with %i players\n", numPlayers);
		smithyTest=newGame();
		struct gameState* outerSave=newGame();
		initializeGame(numPlayers, smithyTestKC, seed, smithyTest);
		*outerSave=*smithyTest;
		
		numRandCounter=smithyTest->numPlayers;
		upperBoundary=smithyTest->numPlayers;
		//upperBoundary--;
		for (i=0; i < numRandCounter; i++)
		{
	
			
			rp=rand() % upperBoundary;
			printf("randomly generated %i from range of 0 to %i; testing with this player\n\n", rp, upperBoundary);
			randomCounter=i;
			
			//placing Smithy in players hand
			printf("Placing Smithy (enum %i) in player %i's hand at position %i\n",smithy, rp, handpos);
			smithyTest->hand[rp][handpos]=smithy;
			printf("Setting player turn\n");
			smithyTest->whoseTurn=rp;
			printf("It is %i's turn now\n",whoseTurn(smithyTest));
			//draw carsds if cards not initialized
			if (smithyTest->handCount[rp]==0)
			{
				int x=0;
				for (x=0; x < 5; x++)
				{
					drawCard(rp, smithyTest);
				}
				
			}
			//printPlayerHand(rp, smithyTest);
			printf("--TEST CASE %i: calling with card:\n%i, choice1: %i, choice2: %i, choice3: %i, smithyTest: %p, handpos: %i, bonus: %p--\n",randomCounter,  card, choice1, choice2, choice3, smithyTest, handpos, &bonus);
			
			printf("saving smithyTest to save before running cardeffect");
			save=newGame();
			*save=*smithyTest;
			
			cardEffect(card, choice1, choice2, choice3, smithyTest, handpos, &bonus);
			actHCA=smithyTest->handCount[rp];
	
			printf("--STEP 1: Checking hand counts--\n");
			if (actHCA==save->handCount[rp]+2)
			{
				printf("SUCCESS: new handcount is %i\n", smithyTest->handCount[rp]);
			}
			else
			{	
				printf("FAILURE: handcount has %i cards instead of required %i\n", smithyTest->handCount[rp], save->handCount[rp]+2);
			}
			//printPlayerHand(rp, smithyTest);
			printf("--STEP 2: Checking that expected played card count matches actual played card count--\n");
			if (save->playedCardCount+1!=smithyTest->playedCardCount)
			{
				printf("FAILURE: Expeted %i, got %i\n", save->playedCardCount+1, smithyTest->playedCardCount);
			}
			else if (save->playedCardCount+1==smithyTest->playedCardCount)
			{		
				printf("SUCCESS: Expected %i, got %i\n", save->playedCardCount+1, smithyTest->playedCardCount);
			}
			printf("--Step 3: Checking that correct hard is discarded. --\n");
			if (smithyTest->playedCards[save->playedCardCount]==save->hand[rp][handpos])
             {
				printf("SUCCESS: last played card matches saved hand in position %i: the %ith played card is %i which matches the card formerly in the player hand, %i\n", handpos, save->playedCardCount, smithyTest->playedCards[save->playedCardCount], save->hand[rp][handpos]);
			}
			else
            {
				printf("FAILURE; last played card DOES NOT match saved hand in position %i: the %ith played card is %i which does NOT match the card formerly in the player hand, %i\n", handpos, save->playedCardCount,  smithyTest->playedCards[save->playedCardCount], save->hand[rp][handpos]);
			}
			printf("---inner loop random %i finished---\n", i);
			*smithyTest=*outerSave;
		}	
		printf("\n\n\n-----finish random test number %i-----\n\n\n", j); 
	}	
	printf("Ending random generation of players\n");
	
	return 0;
}	

