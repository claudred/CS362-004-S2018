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
	printf("\n\n\n----STARTING RANDOM TESTS FOR SMITHY CARD ----\n\n\n");
	printf("----Welcome to random card tests with smithy----\n");
	printf("----We will test the Smithy card using some random tests ----\n");
	printf("-----Smithy is an Action card from the Base Set----\n");
	printf("-----Smithy's purpose is to increase the handside by drawing three cards----\n");
	printf("-----Smithy is a terminal card, meaning that it provides no +Action---\n");
	struct gameState *smithyTest=newGame();
	struct gameState *save=newGame();
	struct gameState *blankSave=newGame();
	int card=smithy;
	int numPlayers=2;
	int seed=450;
	int handpos=0;
	int choice1=0;
	int choice2=0;
	int choice3=0;
	int bonus = 0;
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
	//exPCCA=expected played card count after
	int exPCCA=pccb+1;

	//exHCA=expected hand count after: draw three, discard this one; result in two more
	int exHCA=hcb+2;
	//actHCA=actual hand count after
	int actHCA=0;
	printf("Player %i's hand count before cardEffect is called with Smithy is: %i\n", rp+1, hcb);
	printf("Here is player %i's hand state before\n", rp);
	printPlayerHand(rp, smithyTest);
	printf("Here is player %i's deck state before\n", rp);
	printPlayerDeck(rp, smithyTest);
	printf("The games played card count before is %i\n", pccb);

	int randomCounter=0;//This keeps track of which random test case we are running. 
	//The first test randomizes the handpos of the smithy card i.e. the placement of the card
	//the lower boundary is -1 and the upper boundary is one plus the handcount. 

	int upperBoundary=smithyTest->handCount[rp]+1;
	int numRandCounter=upperBoundary*2;
	int handPosSuccessCount=0;
	int handPosFailureCount=0;
	
		
	int randPlayerSuccessCount=0;
	int randPlayerFailureCount=0;
	printf("Step one: generate a random hand position between -1 and and %i. Test will keep running until -1 and %i is reached\n", upperBoundary, upperBoundary);
	printf("\n\n########### STARTING FIRST SET OF TESTS WITH RANDOM VARIABLE: HANDPOS ###########\n\n\n");
	int hitNeg=0;
	int hitTop=0;
	int i;
	int moreRandomFlag=0;
	int moreRandomFlag2=0;
	int handSuccess=0;
	int handFailure=0;
	int playedSuccess=0;
	int playedFailure=0;
	int discardSuccess=0;
	int discardFailure=0;

	for (i=0; i < numRandCounter; i++)
	{
		randomCounter++;
		printf("\n\n$ # $ # STARTING TEST %i FOR RANDOM HAND POS $ # $ # \n\n", randomCounter);
		//add one to upperBoundary so that when we decrement it later it still goes up to the
		//upper boundary
		
		handpos=rand() % (upperBoundary+2);
		//decrement so that chance of -1 exists.
		handpos--;	
		if (handpos==-1)
		{
			hitNeg=1;
		}
		else if (handpos==upperBoundary)
		{
			hitTop=1;
		}
		
		if (moreRandomFlag==1)
		{
			smithyTest->playedCardCount=rand() % 100;
		}
		printf("randomly generated %i from range of %i to %i in valid options of %i to %i\n", handpos, -1, upperBoundary, 0, smithyTest->handCount[rp]-1);
		
		printf("Placing Smithy (enum %i) in player %i's hand at position %i\n",smithy, rp, handpos);
	
		smithyTest->hand[rp][handpos]=smithy;
		
		printf("--TEST CASE %i: calling with card:\n%i, choice1: %i, choice2: %i, choice3: %i, smithyTest: %p, handpos: %i, bonus: %p--\n",randomCounter,  card, choice1, choice2, choice3, smithyTest, handpos, &bonus);
		*save=*smithyTest;
		cardEffect(card, choice1, choice2, choice3, smithyTest, handpos, &bonus);
		if (moreRandomFlag2==1)
		{
			smithyTest->handCount[rp]=rand() % (exHCA*10);
		}
		actHCA=smithyTest->handCount[rp];
		
		printf("--STEP 1: Checking hand counts--\n");
		if (actHCA==exHCA)
		{
			printf("SUCCESS: new handcount is %i\n", smithyTest->handCount[rp]);
			handPosSuccessCount++;
			handSuccess++;
		}
		else
		{	
			printf("FAILURE: handcount has %i cards instead of required %i\n", smithyTest->handCount[rp], save->handCount[rp]+2);
			 handPosFailureCount++;
			handFailure++;
		}
		printf("--STEP 2: Checking that expected played card count matches actual played card count--\n");
		if (exPCCA!=smithyTest->playedCardCount)
		{
			printf("FAILURE: Expected %i, got %i\n", exPCCA, smithyTest->playedCardCount);
			handPosFailureCount++;
			playedFailure++;
		}
		else if (exPCCA==smithyTest->playedCardCount)
		{	
			
			printf("SUCCESS: Expected %i, got %i\n", exPCCA, smithyTest->playedCardCount);
			handPosSuccessCount++;
			playedSuccess++;
		}
		printf("--STEP 3: Checking that corect card is discarded---\n");
		if (smithyTest->playedCards[save->playedCardCount]==save->hand[rp][handpos])
        {
			printf("SUCCESS: last played card matches saved hand in position %i: the %ith played card is  %i which matches the card formerly in the player hand, %i\n", handpos, save->playedCardCount,  smithyTest->playedCards[save->playedCardCount], save->hand[rp][handpos]);
			handPosSuccessCount++;
			discardSuccess++;
		
		}	
		else
       {
			printf("FAILURE; last played card DOES NOT  match saved hand in position %i:th %i the played card is  %i which does NOT match the card formerly in the player hand, %i\n", handpos, save->playedCardCount,  smithyTest->playedCards[save->playedCardCount], save->hand[rp][handpos]);
			handPosFailureCount++;
			discardFailure++;
		}
		printf("\n\n$ # $ # END TEST %i FOR RANDOM HAND POS $ # $ # \n\n", randomCounter);
		if ((i<numRandCounter-1)&&(i>1))
		{
			if ((hitNeg==0)||(hitTop==0))
			{
				i--;
			}
			else if ((discardFailure==0)||(playedFailure==0)||(handFailure==0))
			{
				printf("discardFailures: %i, playedFailures: %i, handFailures %i", discardFailure, playedFailure, handFailure);
				moreRandomFlag=1;
				i--;
			}
			else if ((discardSuccess==0)||(playedSuccess==0)||(handSuccess==0))
			{
				printf("discardSuccess: %i, playedSuccesss: %i, handSuccess %i", discardSuccess, playedSuccess, handSuccess);
				
				
				moreRandomFlag2=1;
				i--;
			}
			
		} 
		
		*smithyTest=*blankSave;
	}
	printf("\n---------$$$----------\nFINAL TEST 1 REPORT\n---------$$$----------\n---------$$$-----------\n%i out of %i tests passed, \n%i failed, in total\n---------$$$-----------\n", handPosSuccessCount, 3*randomCounter, handPosFailureCount);
	printf("n---------$$$-----------\ndiscardFailures: %i, playedFailures: %i, handFailures: %i\n", discardFailure, playedFailure, handFailure);
	printf("---------$$$-----------\ndiscardSuccess: %i, playedSuccesss: %i, handSuccess: %i\n\n", discardSuccess, playedSuccess, handSuccess);

	printf("\n\n########### FINISHED FIRST SET OF TESTS WITH RANDOM VARIABLE: HANDPOS ###########\n\n\n");

	//a second set of tests for random testing regarding the players that we choose
	printf("\n\n########### STARTING SECOND SET OF TESTS WITH RANDOM VARIABLE: PLAYERS ###########\n\n\n");
	handpos=0;
	int j=0;
	handSuccess=0;
	handFailure=0;
	playedSuccess=0;
	playedFailure=0;
	discardSuccess=0;
	discardFailure=0;

	int noPlayers=0;
	int maxPlus1Player=0;
	
	moreRandomFlag=0;
	moreRandomFlag2=0;
	randomCounter=0;
	
	int jCounter=0;
	//START OUTER LOOP WITH J TO MAX PLAYERS
	for (j=0; j < MAX_PLAYERS*2; j++)
	{
		
		jCounter++;
		printf("\n-----RUNNING OUTER LOOP NUMBER %i-----\n", jCounter);
		if (j==(MAX_PLAYERS*2)-1)
		{
			if (noPlayers==0)
			{
				j--;
			}
			else if (maxPlus1Player==0)
			{
				j--;
			}
			
		}
		
 
		numPlayers=rand() % (MAX_PLAYERS+2);
		if (numPlayers==0)
		{
			noPlayers=1;
		}
		else if (numPlayers==MAX_PLAYERS+1)
		{
			maxPlus1Player=1;
		}
		printf("Randomly selected to play with %i players\n", numPlayers);
		printf("Initializing Game with %i players\n", numPlayers);
		smithyTest=newGame();
		struct gameState* outerSave=newGame();
		int retVal=initializeGame(numPlayers, smithyTestKC, seed, smithyTest);
		*outerSave=*smithyTest;
		
		numRandCounter=smithyTest->numPlayers;
		upperBoundary=smithyTest->numPlayers;
		//upperBoundary--;
		if (retVal!=-1)
		{
			for (i=0; i < numRandCounter; i++)
			{
				randomCounter++; 
				printf("\n\n$ # $ # SSTART TEST %i FOR RANDOM  PLAYER $ # $ # \n\n", randomCounter);			
				rp=rand() % upperBoundary;
				printf("randomly generated %i from range of 0 to %i; testing with this player\n\n", rp, upperBoundary);
				
				
				//placing Smithy in players hand
				printf("Placing Smithy (enum %i) in player %i's hand at position %i\n",smithy, rp, handpos);
				smithyTest->hand[rp][handpos]=smithy;
				printf("Setting player turn\n");
				smithyTest->whoseTurn=rp;
				printf("It is %i's turn now\n", whoseTurn(smithyTest));
				//draw cards if cards not initialized
				if (smithyTest->handCount[rp]==0)
				{
					printf("drawingCards\n");
					int x=0;
					for (x=0; x < 5; x++)
					{
						drawCard(rp, smithyTest);
					}
					
				}
				printPlayerHand(rp, smithyTest);
				printf("--TEST CASE %i: calling with card:\n%i, choice1: %i, choice2: %i, choice3: %i, smithyTest: %p, handpos: %i, bonus: %p--\n",randomCounter,  card, choice1, choice2, choice3, smithyTest, handpos, &bonus);
				
				printf("saving smithyTest to save before running cardeffect");
				save=newGame();
				*save=*smithyTest;

				cardEffect(card, choice1, choice2, choice3, smithyTest, handpos, &bonus);
				actHCA=smithyTest->handCount[rp];
				if (moreRandomFlag2==1)
				{
					actHCA=rand() % 100;
					smithyTest->playedCardCount=rand() % 100;

				}
				printf("--STEP 1: Checking hand counts--\n");
				if (actHCA==exHCA)
				{
					printf("SUfCCESS: new handcount is %i\n", smithyTest->handCount[rp]);
					randPlayerSuccessCount++;
					handSuccess++;
				}
				else
				{	
					printf("FAILURE: handcount has %i cards instead of required %i\n", smithyTest->handCount[rp], save->handCount[rp]+2);
					 randPlayerFailureCount++;
					handFailure++;
				}
				printf("--STEP 2: Checking that expected played card count matches actual played card count--\n");
				if (exPCCA==smithyTest->playedCardCount)
				{
					printf("FAILURE: Expected %i, got %i\n", exPCCA, smithyTest->playedCardCount);
					randPlayerFailureCount++;
					playedFailure++;
				}
				else if (exPCCA!=smithyTest->playedCardCount)
				{	
					
					printf("SUCCESS: Expected %i, got %i\n", exPCCA, smithyTest->playedCardCount);
					randPlayerSuccessCount++;
					playedSuccess++;
				}
				printf("--STEP 3: Checking that corect card is discarded---\n");
				if (moreRandomFlag==1)
				{
					printf("hit more randomflag\n");
					smithyTest->playedCards[save->playedCardCount]=rand() % 100;
				}
				if (smithyTest->playedCards[save->playedCardCount]==save->hand[rp][handpos])
		        {
					printf("SUCCESS: last played card matches saved hand in position %i: the %ith played card is  %i which matches the card formerly in the player hand, %i\n", handpos, save->playedCardCount,  smithyTest->playedCards[save->playedCardCount], save->hand[rp][handpos]);
					randPlayerSuccessCount++;
					discardSuccess++;
				
				}	
				else
		       {
					printf("FAILURE; last played card DOES NOT  match saved hand in position %i:th %i the played card is  %i which does NOT match the card formerly in the player hand, %i\n", handpos, save->playedCardCount,  smithyTest->playedCards[save->playedCardCount], save->hand[rp][handpos]);
					randPlayerFailureCount++;
					discardFailure++;
				}
				if ((i==numRandCounter-1)&&(i>1))
				{
					if ((discardFailure==0)||(playedFailure==0)||(handFailure==0))
					{
						printf("discardFailures: %i, playedFailures: %i, handFailures %i", discardFailure, playedFailure, handFailure);
						moreRandomFlag=1;
						i--;
					}
					else if ((discardSuccess==0)||(playedSuccess==0)||(handSuccess==0))
					{
						printf("discardSuccess: %i, playedSuccesss: %i, handSuccess %i", discardSuccess, playedSuccess, handSuccess);
						moreRandomFlag2=1;
						i--;
					}

				}
				*smithyTest=*outerSave;
			}	
			printf("\n\n$ # $ # END TEST %i FOR RANDOM  PLAYER $ # $ # \n\n", randomCounter);		
		}
		
		else 
		{
			printf("initialize Game detecting something wrong, restarting\n");
			
		}
		printf("\n-----ENDING OUTER LOOP NUMBER %i-----\n", jCounter);

	}	
	//END OUTER LOOP WITH J TO MAX PLAYERS
	printf("\n---------$$$----------\nFINAL TEST 2 REPORT\n---------$$$----------\n---------$$$-----------\n%i out of %i tests passed, \n%i failed, in total\n---------$$$-----------\n", randPlayerSuccessCount, 3*randomCounter, randPlayerFailureCount);
	printf("n---------$$$-----------\ndiscardFailures: %i, playedFailures: %i, handFailures: %i\n", discardFailure, playedFailure, handFailure);
	printf("---------$$$-----------\ndiscardSuccess: %i, playedSuccesss: %i, handSuccess: %i\n\n", discardSuccess, playedSuccess, handSuccess);

	printf("\n\n########### FINISHED SECOND SET OF TESTS WITH RANDOM VARIABLE: RANDOM NUMBER OF PLAYERS AND RANDOM PLAYER ###########\n\n\n");

	
	return 0;
}	


