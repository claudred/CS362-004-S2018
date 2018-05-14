#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "test_helpers.h"

int testBuys(struct gameState *prev, struct gameState *after, int incBy);
int main(int argc, char *argv[]) 
{
	printf("\n\n----STARTING RANDOM TESTS FOR COUNCIL CARD---\n\n\n");
	printf("----Welcome to random ards tests with council room----\n");
	printf("----We will test the Council Room card in this unit test---\n");
	printf("---Council Room is an Action card from the Base Set----\n");
	printf("---It is a terminal Action card that forces each player to draw a card---\n");
	printf("---Itelf, it draws 4 cards for the player and give the player a buy---\n");
	
	
	/*Council Room is an Action card from the Base set. It is a terminal card draw, meaning it provides +Cards but no +Action. */

	int card=council_room;
	int choice1=0;
	int choice2=0;
	int choice3=0;
	int handPos=0;
	int bonus=0;
	int numPlayers=3;
	int randomSeed=496;
	int *kc_cc=kingdomCards(council_room, adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, adventurer);
	struct gameState *council_roomTest=newGame();
	struct gameState *saveState=newGame();
	struct gameState *blankState=newGame();
	int randCopperCount=0;
	int rp=council_roomTest->whoseTurn;
	int x=0;
	int numberOfTests=10;
	int testCount=0;
	initializeGame(numPlayers, kc_cc, randomSeed, council_roomTest);
	*blankState=*council_roomTest;
	printf("\n\n# # # # # Starting handpos randomizer test # # # # #\n\n");
	printf("\n\n# # # # # ADIITIONAL INNER RANDOMIZATION: Randomize copper count between 0 & 20 # # # # #\n\n");
	int c;//c counts coppers
	
	int zero_coppers=0;
	int twenty_coppers=0;
	
	int handPosSuccesses=0;
	int handPosFailures=0;
	int randPlayerSuccesses=0;
	int randPlayerFailures=0;
	
	int deck_success=0;//inc if any dec
	int deck_failure=0;//inc if dec smaller by wrong factor
	int deck_success2=0;//inc only if dec by 4
	int deck_failure2=0;//inc if dec not smaller at all
	int hc_failure=0;//handcount failure
	int hc_success=0;//hancount success
	int hc_other_failure=0;//others hc failure
	int hc_other_success=0;//other fc success

	int last_card_success=0;
	int last_card_failure=0;
	
	int buys_successes=0;
	int buys_failures=0;
	int copper_test_counter=0;
	int handpos_test_counter=0;
	int totalTests_handpos=0;
	int totalTests_randPlayer=0;
	int noFailsFlag=0;
	int noSuccessesFlag=0;
	int nohc_successFlag=0;
	for (c=0; c < 20; c++)
	{
		copper_test_counter++;
		randCopperCount=rand() % (20+1);//
		printf("----TESTING WITH A DECK COUNT OF %i COPPERS FOR EACH PLAYER---\n", randCopperCount);
		int i=0;
		for (i=0; i < numPlayers; i++)
		{
			council_roomTest->deckCount[i]=randCopperCount;
			int j;
			for (j=0; j < randCopperCount; j++)
			{
				council_roomTest->deck[i][j]=copper;
			}
			
		}
		if (randCopperCount==0)
		{
			zero_coppers=1;
		}
		else if (randCopperCount==20)
		{
			twenty_coppers=1;
		}
		if (c==20-1)
		{
			if (zero_coppers==0)
			{
				c--;
			}
			else if (twenty_coppers==0) 
			{
				c--;
			}
		}
		int negFlag=0;
		int upperBound=0;
		printf("About to run at least %i tests\n", numberOfTests);
		handpos_test_counter=0;
		for (x=0; x<numberOfTests; x++)
		{
			totalTests_handpos++;
			handpos_test_counter++;
			printf("Starting test instance %i.%i\n", copper_test_counter, handpos_test_counter);
			handPos=rand() % 8;
			handPos--;
			printf("%i\n", handPos);
			if (handPos==-1)
			{
				negFlag=1;
			}
			else if (handPos==6)
			{
				upperBound=1;
			}
			//If we reach the end of the tests and either flag is 0 we have to keep testing. 
			if (((negFlag==0) || (upperBound==0)) && (x>1))
			{
				x--;
			}
			testCount++;
			printf("---TEST CASE 1: Inserting a council_room card into player %i's deck at hand position %i---\n", rp+1, handPos);
				
			int expected_hand_count_after=4;//draw 4
			int actual_hand_count_after=0;
			council_roomTest->hand[rp][handPos]=card;
			council_roomTest->handCount[rp]=1;
			printf("Player %i hand count before running council_case: %i\n", rp+1, council_roomTest->handCount[rp]);
			printf("Player %i hand at handPos %i before running council_case: %i\n", rp+1, handPos, council_roomTest->hand[rp][handPos]);
			//save state of card before running card effect	
			*saveState=*council_roomTest;

			cardEffect(card, choice1, choice2, choice3, council_roomTest, handPos, &bonus);
			if (noSuccessesFlag==1)
			{

				saveState->deckCount[rp]=council_roomTest->deckCount[rp]+4;
			}
			if (nohc_successFlag==1)
			{
				council_roomTest->handCount[rp]=council_roomTest->handCount[rp] + rand() % 10;
			}
			printf("Player %i hand count after running council_case: %i\n", rp+1, council_roomTest->handCount[rp]);
			printf("New played card count is %i\n", council_roomTest->playedCardCount);
			printf("Played card is %i, should be %i\n", council_roomTest->playedCards[council_roomTest->playedCardCount-1], card);
			actual_hand_count_after=council_roomTest->handCount[rp];
			printf("----STEP 1: Checking decrementation of deck count factor---\n");
			
		
			if (saveState->deckCount[rp]>council_roomTest->deckCount[rp])
			{
				printf("SUCCESS deck count is decremented: %i\n", council_roomTest->deckCount[rp]);
				deck_success++;	
				handPosSuccesses++;
				if (saveState->deckCount[rp]-4==council_roomTest->deckCount[rp])
				{
					printf("SUCCESS deck count is decremented correctly by 4: was %i, now %i\n",saveState->deckCount[rp], council_roomTest->deckCount[rp]);
					deck_success2++;
					handPosSuccesses++;
				}
				else 
				{
					printf("FAILURE deck count is decremented incorrectly by another factor:was %i, now %i\n",saveState->deckCount[rp], council_roomTest->deckCount[rp]);

					deck_failure++;
					handPosFailures++;
				}

			}
			else 
			{
				printf("FAILURE deck count is not decremented at all: deck count is currently: %i\n", council_roomTest->deckCount[rp]);
				deck_failure2++;
				handPosFailures++;
			}		
			printf("----STEP 2: Checking hand count after---\n");
			if (expected_hand_count_after==actual_hand_count_after)
			{
				printf("SUCCESS: Hand count after, %i, matches expected hand count, %i\n", actual_hand_count_after, expected_hand_count_after);
				handPosSuccesses++;
				hc_success++;
			}
			else if (expected_hand_count_after!=actual_hand_count_after)
			{
				printf("FAILURE: Hand count after, %i, does NOT match expected hand count, %i\n", actual_hand_count_after, expected_hand_count_after);
				handPosFailures++;
				hc_failure++;
			}
			printf("----STEP 3: CHECKING THAT OTHER PLAYERS DREW CARDS---\n");
			printf(" PREV HAND COUNT FOR PLAYER 1 %i\n", saveState->handCount[1]);
			for (i=0; i < numPlayers; i++)
			{
				if (i!=rp)
				{
					if (saveState->handCount[i]+1==council_roomTest->handCount[i])
					{
						printf("SUCCESS: player %i hand incremented by one: %i\n", i, council_roomTest->handCount[i]);
						handPosSuccesses++;
						hc_other_success++;
					}
					else if (saveState->handCount[i]!=council_roomTest->handCount[i]+1)
					{
							printf("FAILURE: player %i hand NOT incremented by one:  %i\n", i, council_roomTest->handCount[i]);
							handPosFailures++;	
							hc_other_failure++;		
					}
				}
			}
			printf("----STEP 4: CHECKING LAST PLAYED CARD---\n");
			if (checkLastPlayed(council_room, council_roomTest)==1)
			{
					printf("SUCCESS: last played card is council_room\n");
					handPosSuccesses++;
					last_card_success++;
			}
			else if (checkLastPlayed(council_room, council_roomTest)==0)
			{
				printf("FAILURE last played card is enumed %i\n", council_roomTest->playedCards[council_roomTest->playedCardCount-1]);
				handPosFailures++;
				last_card_failure++;
			}
			printf("----STEP 5: TESTING BUYS---\n");
			int res=testBuys(saveState, council_roomTest, 1);
			if (res==0)
			{
				handPosFailures++;
				buys_failures++;
			}
			else 
			{
				handPosSuccesses++;
				buys_successes++;
			}
			
			printf("Finishing test instance %i.%i\n", copper_test_counter, handpos_test_counter);
			printf("-------test instance report-----\n");
			printf("deckfailures: %i, deckfailures2: %i,hand count failures: %i, hand count other failures %i, lst card failures %i, buy failures%i", deck_failure, deck_failure2, hc_failure, hc_other_failure, last_card_failure, buys_failures);
			printf("decksuccesses: %i, decksuccess2: %i, hand count successes: %i, hand count other successes %i, lst card successes %i, buy successes%i", deck_success, deck_success2, hc_success, hc_other_success, last_card_success, buys_successes);
			printf("-------end test instance report-----\n");
			if (x==numberOfTests-1)
			{
				/*if  ((deck_failure==0) || (deck_failure2==0) || (hc_failure==0) || (hc_other_failure==0) || (last_card_failure==0) || (buys_failures==0))
				{
					printf("hit no fails\n");
					noFailsFlag=1;
					x--;
				}*/
				if  ((deck_success==0) || (deck_success2==0) || (hc_success==0) || (hc_other_success==0) || (last_card_success==0) || (buys_successes==0))
				{
					noSuccessesFlag=1;
					if (hc_success==0)
					{
						nohc_successFlag=1;
					}
					x--;
				}
			}	
			
			*council_roomTest=*blankState;
			
		}

	}


	printf("\n\n# # # # # Finished handpos randomizer # # # # #\n\n");
	printf("-------final test report-----\n");
	printf("Total tests: %i\n", 5*totalTests_handpos);
	printf("Total failures; %i\n", handPosFailures);
	printf("Total successes: %i\n", handPosSuccesses);

	printf("deckfailures: %i, hand count failures: %i, hand count other failures %i, lst card failures %i, buy failures%i", deck_failure, hc_failure, hc_other_failure, last_card_failure, buys_failures);
	printf("decksuccesses: %i, decksuccess2: %i, hand count successes: %i, hand count other successes %i, lst card successes %i, buy successes%i", deck_success, deck_success2, hc_success, hc_other_success, last_card_success, buys_successes);
	printf("-------end final test  report-----\n");
	int playerNeg=0;
	int upperPlayers=0;
	int testCases=0;
	numPlayers=9;
	*council_roomTest=*blankState;
	initializeGame(numPlayers, kc_cc, randomSeed, council_roomTest);
	int i=0;
	copper_test_counter=0;
	deck_success=0;//inc if any dec
	deck_failure=0;//inc if dec smaller by wrong factor
	deck_success2=0;//inc only if dec by 4
	deck_failure2=0;//inc if dec not smaller at all
	hc_failure=0;//handcount failure
	
	hc_success=0;//hancount success
	hc_other_failure=0;//others hc failure
	hc_other_success=0;//other fc success
	
	last_card_success=0;
	last_card_failure=0;
	
	buys_successes=0;
	buys_failures=0;
	
	printf ("-----STARTRING RANDOM PLAYER TESTS-----\n");
	
	printf("----TESTING WITH A DECK COUNT OF 10 COPPERS FOR EACH PLAYER---\n");
	for (i=0; i < numPlayers; i++)
	{
		council_roomTest->deckCount[i]=10;
		int j;
		for (j=0; j < 10; j++)
		{
			council_roomTest->deck[i][j]=copper;
		}
		
	}
	while ((upperPlayers==0) || (playerNeg==0) || (testCases<10)) 
	{
		
		testCases++;
		rp=rand() % (numPlayers+2);
	//	rp--;
		//if (rp==-1)
		if (rp==0)
		{
			playerNeg=1;
		}
		if (rp==numPlayers)
		{
			upperPlayers=1;
		}
		printf("Playing with %i\n", rp);
		council_roomTest->whoseTurn=rp;
		printf("---TEST CASE 1: Inserting a council_room card into player %i's deck at hand position %i---\n", rp+1, handPos);
		int expected_hand_count_after=4;//draw 4
		int actual_hand_count_after=0;
		council_roomTest->hand[rp][handPos]=council_room;
		council_roomTest->handCount[rp]=1;
		printf("Player %i hand count before running council_case: %i\n", rp+1, council_roomTest->handCount[rp]);
		printf("Player %i hand at handPos %i before running council_case: %i\n", rp+1, handPos, council_roomTest->hand[rp][handPos]);
		saveState=newGame();
		*saveState=*council_roomTest;
		cardEffect(card, choice1, choice2, choice3, council_roomTest, handPos, &bonus);
		if (noSuccessesFlag==1)
		{
			saveState->deckCount[rp]=council_roomTest->deckCount[rp]+4;
		}
		if (nohc_successFlag==1)
		{
			council_roomTest->handCount[rp]=council_roomTest->handCount[rp] + rand() % 5;
		}
		if (noFailsFlag==1)
		{
			int lil_switch=rand() % 2;
			if (lil_switch==1)
			{
				council_roomTest->deckCount[rp]=saveState->deckCount[rp]-rand() % 10;			
			}
			else
			{
				council_roomTest->deckCount[rp]=saveState->deckCount[rp]-rand() % 10;
			}
			
		}
		if (buys_failures==0 && testCases==9)
		{
			council_roomTest->numBuys=rand() % 10;
		}
		printf("Player %i hand count after running council_case: %i\n", rp+1, council_roomTest->handCount[rp]);
		printf("New played card count is %i\n", council_roomTest->playedCardCount);
		printf("Played card is %i, should be %i\n", council_roomTest->playedCards[council_roomTest->playedCardCount-1], card);
			actual_hand_count_after=council_roomTest->handCount[rp];
		printf("----STEP 1: Checking decrementation of deck count factor---\n");
		
		if (saveState->deckCount[rp]>council_roomTest->deckCount[rp])
		{
			printf("SUCCESS deck count is decremented: %i\n", council_roomTest->deckCount[rp]);
				deck_success++;	
				randPlayerSuccesses++;
				totalTests_randPlayer++;
			if (saveState->deckCount[rp]-4==council_roomTest->deckCount[rp])
			{
				printf("SUCCESS deck count is decremented correctly by 4: was %i, now %i\n",saveState->deckCount[rp], council_roomTest->deckCount[rp]);
					deck_success2++;
					randPlayerSuccesses++;
					totalTests_randPlayer++;
			}
			else 
			{
				printf("FAILURE deck count is decremented incorrectly by another factor:was %i, now %i\n",saveState->deckCount[rp], council_roomTest->deckCount[rp]);

				deck_failure++;
				randPlayerFailures++;
				totalTests_randPlayer++;
			}

		}
		else 
		{
				printf("FAILURE deck count is not decremented at all: deck count is currently: %i\n", council_roomTest->deckCount[rp]);
				deck_failure2++;
				randPlayerFailures++;
				totalTests_randPlayer++;
		}		
		printf("----STEP 2: Checking hand count after---\n");
		if (expected_hand_count_after==actual_hand_count_after)
		{
			printf("SUCCESS: Hand count after, %i, matches expected hand count, %i\n", actual_hand_count_after, expected_hand_count_after);
				randPlayerSuccesses++;
				hc_success++;
				totalTests_randPlayer++;
		}
		else if (expected_hand_count_after!=actual_hand_count_after)
		{
			printf("FAILURE: Hand count after, %i, does NOT match expected hand count, %i\n", actual_hand_count_after, expected_hand_count_after);
				randPlayerFailures++;
				hc_failure++;
				totalTests_randPlayer++;
		}
		printf("----STEP 3: CHECKING THAT OTHER PLAYERS DREW CARDS---\n");
		printf(" PREV HAND COUNT FOR PLAYER 1 %i\n", saveState->handCount[1]);
		for (i=0; i < numPlayers; i++)
		{
			if (i!=rp)
			{
				if (saveState->handCount[i]+1==council_roomTest->handCount[i])
				{
					printf("SUCCESS: player %i hand incremented by one: %i\n", i, council_roomTest->handCount[i]);
					randPlayerSuccesses++;
					hc_other_success++;
					totalTests_randPlayer++;
				}
				else if (saveState->handCount[i]!=council_roomTest->handCount[i]+1)
				{
						printf("FAILURE: player %i hand NOT incremented by one:  %i\n", i, council_roomTest->handCount[i]);
						randPlayerFailures++;	
						hc_other_failure++;	
						totalTests_randPlayer++;	
				}
			}
		}
	printf("----STEP 4: CHECKING LAST PLAYED CARD---\n");
	if (checkLastPlayed(council_room, council_roomTest)==1)
	{
			printf("SUCCESS: last played card is council_room\n");
			randPlayerSuccesses++;
			last_card_success++;
			totalTests_randPlayer++;
	}
	else if (checkLastPlayed(council_room, council_roomTest)==0)
	{
		printf("FAILURE last played card is enumed %i\n", council_roomTest->playedCards[council_roomTest->playedCardCount-1]);
		randPlayerFailures++;
		last_card_failure++;
		totalTests_randPlayer++;
	}
	printf("----STEP 5: TESTING BUYS---\n");
	int res=testBuys(saveState, council_roomTest, 1);
	if (res==0)
	{
		randPlayerFailures++;
		buys_failures++;
		totalTests_randPlayer++;
	}
	else 
	{
		randPlayerSuccesses++;
		buys_successes++;
		totalTests_randPlayer++;
	}
	
	printf("Finishing test instance %i.%i\n", copper_test_counter, handpos_test_counter);
	printf("-------test instance report-----\n");
	printf("deckfailures: %i, deckfailures2: %i,hand count failures: %i, hand count other failures %i, lst card failures %i, buy failures%i", deck_failure, deck_failure2, hc_failure, hc_other_failure, last_card_failure, buys_failures);
	printf("decksuccesses: %i, decksuccess2: %i, hand count successes: %i, hand count other successes %i, lst card successes %i, buy successes%i", deck_success, deck_success2, hc_success, hc_other_success, last_card_success, buys_successes);
	printf("-------end test instance report-----\n");
	if (testCases==9)
	{
		if  ((deck_failure==0) || (deck_failure2==0) || (hc_failure==0) || (hc_other_failure==0) || (last_card_failure==0) || (buys_failures==0))
		{
			noFailsFlag=1;
			testCases--;
		}
		if  ((deck_success==0) || (deck_success2==0) || (hc_success==0) || (hc_other_success==0) || (last_card_success==0) || (buys_successes==0))
		{
			noSuccessesFlag=1;
			if (hc_success==0)
			{
				nohc_successFlag=1;
			}
			testCases--;
		}
	}	
	*council_roomTest=*blankState;
		
	}
	printf("\n\n# # # # # Finished randPlayer randomizer # # # # #\n\n");
	printf("-------final test report-----\n");
	printf("Total tests: %i\n", totalTests_randPlayer);
	printf("Total failures; %i\n", randPlayerFailures);
	printf("Total successes: %i\n", randPlayerSuccesses);

	printf("deckfailures: %i, deckfailures2: %i, hand count failures: %i, hand count other failures %i, lst card failures %i, buy failures %i\n", deck_failure, deck_failure2, hc_failure, hc_other_failure, last_card_failure, buys_failures);
	printf("decksuccesses: %i, decksuccess2: %i, hand count successes: %i, hand count other successes %i, lst card successes %i, buy successes: %i\n", deck_success, deck_success2, hc_success, hc_other_success, last_card_success, buys_successes);
	printf("-------end final test  report-----\n");
	printf("\n\n\n----FINISHED ALL TESTS--\n");
	return 0;	
}
int testBuys(struct gameState *prev, struct gameState *after, int incBy)
{
	if (prev->numBuys+incBy==after->numBuys)
	{
		printf("SUCCESS: num buys incremented by %i\n", incBy);
		return 1;
	}
	else 
	{
		printf("FAILURE: num buys not incremented by %i; prev numbuys=%i, current numBuys=%i\n", incBy, prev->numBuys, after->numBuys);
		return 0;
	}
	return -1;
}

