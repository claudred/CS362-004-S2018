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
	printf("\n\n----STARTING RANDOM TESTS FOR ADVENTURER CARD----\n\n");
	printf("----Welcome to random card tests with adventurer----\n");
	printf("----We will test the Adventurer card in this random test----\n");
	printf("----Adventurer is an Action card from the Base Set----\n");
	printf("-----It is a terminal Action card that digs for Treasure cards in the deck-----\n");
	printf("----If there is treasure in the players deck it should draw it-----\n");
	
	struct gameState *testAdventurer=newGame();
	int* kc_ac=kingdomCards(adventurer, smithy, embargo, village, minion, mine, cutpurse, sea_hag, tribute, baron);
	
	int numPlayers=2;
	int randomSeed=4;
	int card=adventurer;
	int choice1=0;
	int choice2=0; 
	int choice3=0;
	int handPos=0;
	int bonus=0;
	int x=0;
	int zeroPlayers=0;
	int onePlayers=0;
	int fivePlayers=0;
	int numTests=10;
	int testCounter=0;
	int PLAYERS_RANGE_FAIL_COUNT=0;
	int PLAYERS_RANGE_PASS_COUNT=0;
	int rp=-1;	
	
	printf("Step one: generate random number of players between 0 and %i; valid range is  %i to %i; tests will keep running until %i are reached and three upper and lower fail states (0, 1, and 5) are reached\n", MAX_PLAYERS+1, 2, MAX_PLAYERS, numTests);
	int successes=0;
	int failures=0;
	int handcountSuccesses=0;
	int handcountFailures=0;
	int discardSuccesses=0;
	int discardFailures=0;
	while ((x<numTests)||(zeroPlayers==0)||(fivePlayers==0)||(onePlayers==0))
	{
		//reset success and failure count for this loop
		successes=0;
		failures=0;
		handcountSuccesses=0;
		handcountFailures=0;
		discardSuccesses=0;
		discardFailures=0;
		x++;//increment x closer to numTests
		testCounter++;//increment so we track how many tests we actually run
		printf("\n\n$ # $ # STARTING TEST %i FOR RANDOM NUMBER OF PLAYERS TEST $ # $ #\n\n", testCounter);
		numPlayers=rand() % (MAX_PLAYERS+2);
		if (numPlayers==0)
		{
			zeroPlayers=1;
			PLAYERS_RANGE_FAIL_COUNT++;
		}
		else if (numPlayers==1)
		{
			onePlayers=1;
			PLAYERS_RANGE_FAIL_COUNT++;
		}
		else if (numPlayers==5)
		{
			fivePlayers=1;
			PLAYERS_RANGE_FAIL_COUNT++;
		}		
		else 
		{
			PLAYERS_RANGE_PASS_COUNT++;
		}
		printf("Generated %i players\n", numPlayers);	
		int ret_val=initializeGame(numPlayers, kc_ac, randomSeed, testAdventurer);
		if (ret_val==-1)
		{
			printf("initializeGame detected something wrong, restart without running tests to prevent segfault\n");
		}
		if (ret_val!=-1)
		{
			
			printf("\n\n# # # #  STARTING TEST CASE 1 FOR TEST %i: Treasure in deck # # # #\n\n", testCounter);
			rp=whoseTurn(testAdventurer);
			testAdventurer->hand[rp][handPos]=adventurer;
			struct gameState *save=newGame();
			*save=*testAdventurer;
			printf("PLAYER: %i\n", rp);
			
			printf("At this point, we know that the player should have only treasure in the deck; so we expect that the hand count before and after should differ by two counts\n");
			printf("Player's %i hand count before: %i\n", rp, testAdventurer->handCount[rp]);
			printf ("Player %i's deck before\n", rp);
			printPlayerDeck(rp, testAdventurer);
			printf("Players %i's hand before\n", rp);
			printPlayerHand(rp, testAdventurer);
			ret_val=cardEffect(card, choice1, choice2, choice3, testAdventurer, handPos, &bonus);
			//HOW TO REACH THIS STATE?
			/*if (ret_val==-1)	
			{
				printf("cardEffect detected something wrong, restart\n");
			}*/
			if (ret_val!=-1)
			{
				printf("Player's hand count after: %i\n", testAdventurer->handCount[rp]);
				if (save->handCount[rp]+2==testAdventurer->handCount[rp])
				{
					printf("SUCCESS: correct number of items incremented from the count\n");		
					successes++;
				}
				/*else 
				{
					printf("FAILURE: incorrect number of items incremented from the count\n");
					failures++;
				}*/
				printf("Checking player deck count\n");
				if (save->deckCount[rp]-2==testAdventurer->deckCount[rp])
				{
					printf("SUCCESS: correct number of treasure cards mined\n");
					successes++;
				}
				/*else 
				{
					printf("FAILURE: incorrect number of treasure cards mined\n");
					failures++;
				}*/
				handcountFailures=failures;
				handcountSuccesses=successes;
				printf("# # # # HANDCOUNT REPORT: %i successes, %i failures # # # #\n", handcountSuccesses, handcountFailures);
				printf("Player's %i hand count after: %i\n", rp, testAdventurer->handCount[rp]);
				printf ("Player %i's deck after\n", rp);
				printPlayerDeck(rp, testAdventurer);
				printf("Players %i's hand after\n", rp);
				printPlayerHand(rp, testAdventurer);
				printf("\n\n# # # #  FINISHED TEST CASE 1 FOR TEST %i: Treasure in deck # # # #\n\n", testCounter);
				printf("\n\n# # # #  STARTING TEST CASE 2 FOR TEST %i: No Treasure in deck # # # #\n\n", testCounter);
				*testAdventurer=*save;
				rp=whoseTurn(testAdventurer);
				printf("Setting all cards for player %i's deck to curse\n", rp);
				int i=0;
				for (i=0; i < testAdventurer->deckCount[rp]+1; i++)
				{
					testAdventurer->deck[rp][i]=0;
				}
				printPlayerDeck(rp, testAdventurer);
				printf("Discard count before call %i\n", testAdventurer->discardCount[rp]);
				printf("Testing card effect with only curse cards in deck; expecting discard count to increment by5\n");
				cardEffect(card, choice1, choice2, choice3, testAdventurer, handPos, &bonus);
				printf("Player %i deck before\n", rp);
				printPlayerDeck(rp, testAdventurer);
				printf("Player %i hand before\n", rp);
				printPlayerHand(rp, testAdventurer);
				if (save->discardCount[rp]+5==testAdventurer->discardCount[rp])
				{
					printf("SUCCESS: discard count is %i\n", testAdventurer->discardCount[rp]);
					successes++;
				}
				//failure state neber reached, get rid of it
				/*else 
				{
					printf("FAILURE: discard count is %i\n", testAdventurer->discardCount[rp]);
					failures++;
				}*/
				printf("DISCARD DECK AFTER\n");
				printDiscard(rp, testAdventurer);
				discardSuccesses=successes-handcountSuccesses;
				discardFailures=failures-handcountFailures;
				printf("# # # # DISCARD REPORT: %i successes, %i failures # # # #\n", discardSuccesses, discardFailures);
				printf("\n\n# # # #  FINISHED TEST CASE 2 FOR TEST %i: No Treasure in deck # # # #\n\n", testCounter);
				printf("# # # # TOTAL REPORT %i successes, %i failures # # # #\n", successes, failures);
				
			}

		}
		printf("\n\n $ # $ # FINISHED TEST %i FOR RANDOM NUMBER OF PLAYERS TEST $ # $ #\n\n", testCounter);
		
	}
	printf("# # # # Finished randomize numPlayers test # # # #\n");
	printf("# # # # REPORT: Ran test %i times # # # #\n", testCounter);
	printf("# # # # REPORT: Reached fail states %i times # # # #\n", PLAYERS_RANGE_FAIL_COUNT);
	printf("# # # # REPORT: Reached success states %i times # # # #\n", PLAYERS_RANGE_PASS_COUNT);
	
	numPlayers=2;
	x=0;
	printf("Step two: generate random hand position in the range of 0 to %i\n", testAdventurer->handCount[rp]);
	testCounter=0;
	while (x<numTests)
	{
		x++;
		testCounter++;
		int ret_val=initializeGame(numPlayers, kc_ac, randomSeed, testAdventurer);
		rp=whoseTurn(testAdventurer);
		handPos=rand() % testAdventurer->handCount[rp];
		printf("\n\n$ # $ # STARTING TEST %i FOR RANDOM HANDPOS FOR PLAYER %i $ # $ #\n\n", testCounter, rp);
		printf("Generated handpos %i\n", handPos);
		testAdventurer->hand[rp][handPos]=adventurer;
		//reset success and failure count for this loop
		successes=0;
		failures=0;
		handcountSuccesses=0;
		handcountFailures=0;
		discardSuccesses=0;
		discardFailures=0;
		printf("\n\n$ # $ # STARTING TEST %i FOR RANDOM NUMBER OF PLAYERS TEST $ # $ #\n\n", testCounter);
		if (ret_val!=-1)
		{
			
			printf("\n\n# # # #  STARTING TEST CASE 1 FOR TEST %i: Treasure in deck # # # #\n\n", testCounter);
			struct gameState *save=newGame();
			*save=*testAdventurer;
			printf("PLAYER: %i\n", rp);
			
			printf("At this point, we know that the player should have only treasure in the deck; so we expect that the hand count before and after should differ by two counts\n");
			printf("Player's %i hand count before: %i\n", rp, testAdventurer->handCount[rp]);
			printf ("Player %i's deck before\n", rp);
			printPlayerDeck(rp, testAdventurer);
			printf("Players %i's hand before\n", rp);
			printPlayerHand(rp, testAdventurer);
			ret_val=cardEffect(card, choice1, choice2, choice3, testAdventurer, handPos, &bonus);
			//HOW TO REACH THIS STATE?
			/*if (ret_val==-1)	
			{
				printf("cardEffect detected something wrong, restart\n");
			}*/
			if (ret_val!=-1)
			{
				printf("Player's hand count after: %i\n", testAdventurer->handCount[rp]);
				if (save->handCount[rp]+2==testAdventurer->handCount[rp])
				{
					printf("SUCCESS: correct number of items incremented from the count\n");		
					successes++;
				}
				/*else 
				{
					printf("FAILURE: incorrect number of items incremented from the count\n");
					failures++;
				}*/
				printf("Checking player deck count\n");
				if (save->deckCount[rp]-2==testAdventurer->deckCount[rp])
				{
					printf("SUCCESS: correct number of treasure cards mined\n");
					successes++;
				}
				/*else 
				{
					printf("FAILURE: incorrect number of treasure cards mined\n");
					failures++;
				}*/
				handcountFailures=failures;
				handcountSuccesses=successes;
				printf("# # # # HANDCOUNT REPORT: %i successes, %i failures # # # #\n", handcountSuccesses, handcountFailures);
				printf("Player's %i hand count after: %i\n", rp, testAdventurer->handCount[rp]);
				printf ("Player %i's deck after\n", rp);
				printPlayerDeck(rp, testAdventurer);
				printf("Players %i's hand after\n", rp);
				printPlayerHand(rp, testAdventurer);
				printf("\n\n# # # #  FINISHED TEST CASE 1 FOR TEST %i: Treasure in deck # # # #\n\n", testCounter);
				printf("\n\n# # # #  STARTING TEST CASE 2 FOR TEST %i: No Treasure in deck # # # #\n\n", testCounter);
				*testAdventurer=*save;
				rp=whoseTurn(testAdventurer);
				printf("Setting all cards for player %i's deck to curse\n", rp);
				int i=0;
				for (i=0; i < testAdventurer->deckCount[rp]+1; i++)
				{
					testAdventurer->deck[rp][i]=0;
				}
				printPlayerDeck(rp, testAdventurer);
				printf("Discard count before call %i\n", testAdventurer->discardCount[rp]);
				printf("Testing card effect with only curse cards in deck; expecting discard count to increment by5\n");
				cardEffect(card, choice1, choice2, choice3, testAdventurer, handPos, &bonus);
				printf("Player %i deck before\n", rp);
				printPlayerDeck(rp, testAdventurer);
				printf("Player %i hand before\n", rp);
				printPlayerHand(rp, testAdventurer);
				if (save->discardCount[rp]+5==testAdventurer->discardCount[rp])
				{
					printf("SUCCESS: discard count is %i\n", testAdventurer->discardCount[rp]);
					successes++;
				}
				else 
				{
					printf("FAILURE: discard count is %i\n", testAdventurer->discardCount[rp]);
					failures++;
				}
				printf("DISCARD DECK AFTER\n");
				printDiscard(rp, testAdventurer);
				discardSuccesses=successes-handcountSuccesses;
				discardFailures=failures-handcountFailures;
				printf("# # # # DISCARD REPORT: %i successes, %i failures # # # #\n", discardSuccesses, discardFailures);
				printf("\n\n# # # #  FINISHED TEST CASE 2 FOR TEST %i: No Treasure in deck # # # #\n\n", testCounter);
				printf("# # # # TOTAL REPORT %i successes, %i failures # # # #\n", successes, failures);
				
			}

		}
		printf("\n\n $ # $ # FINISHED TEST %i FOR RANDOM HANDPOST TEST$ # $ #\n\n", testCounter);
		
	
	}
	printf("# # # # Finished randomize numPlayers test # # # #\n");
	printf("# # # # REPORT: Ran test %i times # # # #\n", testCounter);
	printf("\n\n----FINISHED ALL RANDOM TESTS FOR ADVENTURER CARD----\n\n");
	return 0;

}

