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
		//add one to upperBoundary so that when we decrement it later it still goes up to the
		//upper boundary
		handpos=rand() % (upperBoundary+1);
		//decrement so that chance of zero exists.
		handpos--;	
		printf("randomly generated %i\n", handpos);
		randomCounter=i;
		//placing Smithy in players hand
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
		}
		else
		{	
			printf("FAILURE: handcount has %i cards instead of required %i\n", smithyTest->handCount[rp], save->handCount[rp]+2);
		}
		//printPlayerHand(rp, smithyTest);
		printf("--STEP 2: Checking that expected played card count matches actual played card count--\n");
		if (exPCCA!=smithyTest->playedCardCount)
		{
			printf("FAILURE: Expected %i, got %i\n", exPCCA, smithyTest->playedCardCount);
		}
		else if (exPCCA==smithyTest->playedCardCount)
		{	
			printf("SUCCESS: Expected %i, got %i\n", exPCCA, smithyTest->playedCardCount);
		}
		printf("--STEP 3: Checking that corect card is discarded---\n");
	
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
		//the smityh function discards the card without using the trash flag, so we expect the last played card, at the index of the last cardcount in smithyTest's playedCards array, to match the 
		//card at the previous handposition put in
		if (smithyTest->playedCards[save->playedCardCount]==save->hand[rp][handpos])
                {
			printf("SUCCESS: last played card matches saved hand in position %i: the %i the played card is  %i whcih matches the card formerly in the player hand, %i\n", handpos, save->playedCardCount,  smithyTest->playedCards[save->playedCardCount], save->hand[rp][handpos]);
		}
		else
              	{
			
			printf("FAILURE; last played card DOES NOT  match saved hand in position %i: the %i the played card is  %i which does NOT match the card formerly in the player hand, %i\n", handpos, save->playedCardCount,  smithyTest->playedCards[save->playedCardCount], save->hand[rp][handpos]);
		}
		printf("---TEST CASE %i finished, resetting game state to original--- \n", randomCounter);
		*smithyTest=*blankSave;
	}
	//*smithyTest=*saveTwo;
	//a second set of tests for random testing regarding the players that we choose
	int j=0;
	for (j=0; j < MAX_PLAYERS*2; j++)
	{
		printf("\n\n\n-----Running random test number %i-----\n\n\n", j); 
		numPlayers=rand() % MAX_PLAYERS;
		numPlayers++;
		printf("Randomly selected %i players\n\n", numPlayers);
		printf("Initializing Gmae with %i players\n", numPlayers);
		initializeGame(numPlayers, smithyTestKC, seed, smithyTest);
		printf("Setting up blankSave and save");
		*blankSave=*smithyTest;
		*save=*smithyTest;
		numRandCounter=smithyTest->numPlayers;
		//printf("\n\n\n----Starting SECOND RANDOM TEST; random generation of players----\n\n\n");

		printf("%i total players\n", numRandCounter);

		for (i=0; i < numRandCounter; i++)
		{
			//add one to upperBoundary so that when we decrement it later it still goes up to the
			//upper boundary
			rp=rand() % (smithyTest->numPlayers);
			//decrement so that chance of zero exists.
			rp++;
			printf("randomly generated %i; testing with this player\n\n", rp);
			randomCounter=i;
			//placing Smithy in players hand
			printf("Placing Smithy (enum %i) in player %i's hand at position %i\n",smithy, rp, handpos);
	
			smithyTest->hand[rp][handpos]=smithy;
			printf("--TEST CASE %i: calling with card:\n%i, choice1: %i, choice2: %i, choice3: %i, smithyTest: %p, handpos: %i, bonus: %p--\n",randomCounter,  card, choice1, choice2, choice3, smithyTest, handpos, &bonus);
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
				printf("FAILURE: Expeted %i, got %i\n", exPCCA, smithyTest->playedCardCount);
			}
			else if (save->playedCardCount+1==smithyTest->playedCardCount)
			{		
				printf("SUCCESS: Expected %i, got %i\n", exPCCA, smithyTest->playedCardCount);
			}
			printf("--CHECKING DISCARD FUNCTION--\n");
	
		//the smityh function discards the card without using the trash flag, so we expect the last played card, at the index of the last cardcount in smithyTest's playedCards array, to match the 
		//card at the previous handposition put in
			if (smithyTest->playedCards[smithyTest->playedCardCount-1]==save->hand[rp][handpos])
               		 {
				printf("SUCCESS: last played card matches saved hand in position %i: the %i the played card is  %i whcih matches the card formerly in the player hand, %i\n", handpos, save->playedCardCount,  smithyTest->playedCards[save->playedCardCount], save->hand[rp][handpos]);
			}
			else
              		{
			
				printf("FAILURE; last played card DOES NOT  match saved hand in position %i: the %i the played card is  %i which does NOT match the card formerly in the player hand, %i\n", handpos, save->playedCardCount,  smithyTest->playedCards[save->playedCardCount], save->hand[rp][handpos]);
			}
			printf("---TEST CASE %i finished, resetting game state to original--- \n", randomCounter);
			*smithyTest=*blankSave;
		}	
		printf("\n\n\n----FINISHED ALL %i  TESTS---\n", numRandCounter);
	
		printf("\n\n\n-----finish random test number %i-----\n\n\n", j); 
	}	
	printf("Ending random generation of players\n");
	
	return 0;
}	
