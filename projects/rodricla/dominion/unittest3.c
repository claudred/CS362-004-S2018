#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
int test_numPlayers(int actual, int plan);
int test_supplyCounts(int numPlayers, struct gameState *state);
void test_num_kingcard(int numplayer, struct gameState *gameState, int kingdomCards[10]);
int main(int argc, char *argv[]) 
{
	
	printf("$$$$$---UNIT TEST 3---$$$$$\n\n-------Testing 'initializeGame' function with parameters 'int numPlayers', 'int kingdomGard', 'int randomSeed', and 'int gameState *state', and a return value of an integer signifying failure for -1 or 0 for success------\n\n\n");

	printf("----TEST CASE 1: GOOD INPUT 2 players-----\n");
	struct gameState *testGame1=newGame();
	int *kc1=kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);
	int test1_numPlayers=2;
	int returnval=initializeGame(test1_numPlayers, kc1, 1234, testGame1);	
	printf("Checking that the number of players for the state has been appropriately set\n");
	test_numPlayers(testGame1->numPlayers, test1_numPlayers);
	test_supplyCounts(testGame1->numPlayers, testGame1);
	test_num_kingcard(testGame1->numPlayers, testGame1, kc1);
		printf("----FINISHED TEST CASE 1----\n\n\n");
	
	printf("----TEST CASE 1A: GOOD INPUT 3 players-----\n");
	struct gameState *testGame1A=newGame();
	int *kc1A=kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);
	int test1A_numPlayers=3;
	returnval=initializeGame(test1A_numPlayers, kc1A, 1234, testGame1A);	
	printf("Checking that the number of players for the state has been appropriately set\n");
	test_numPlayers(testGame1A->numPlayers, test1A_numPlayers);
	test_supplyCounts(testGame1A->numPlayers, testGame1A);
	test_num_kingcard(testGame1A->numPlayers, testGame1A, kc1A);
	printf("----FINISHED TEST CASE 1A----\n\n\n");
	
	
	printf("----TEST CASE 1B: GOOD INPUT 4 players-----\n");
	struct gameState *testGame1B=newGame();
	int *kc1B=kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);
	int test1B_numPlayers=4;
	returnval=initializeGame(test1B_numPlayers, kc1B, 1234, testGame1B);	
	printf("Checking that the number of players for the state has been appropriately set\n");
	test_numPlayers(testGame1B->numPlayers, test1B_numPlayers);
	test_supplyCounts(testGame1B->numPlayers, testGame1B);
	test_num_kingcard(testGame1B->numPlayers, testGame1B, kc1B);
	printf("----FINISHED TEST CASE 1B----\n\n\n");
	
		
	printf("----TEST CASE 2: BAD INPUT RE: NumPlayers-----\n");
	printf("Attempting to initialize game with 5 players; should return -1\n");
	struct gameState *testGame2=newGame();
	int *kc2=kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);
	int test2_numPlayers=5;
	returnval=initializeGame(test2_numPlayers, kc2, 1234, testGame2);	
	if (returnval==-1)
	{
		printf("SUCCESS: registered that there are too many players\n");
	}
	else 
	{
		printf("FAILURE: did not register that there are too many players\n");
	}
	
	test_numPlayers(testGame2->numPlayers, test2_numPlayers);
	test_supplyCounts(testGame2->numPlayers, testGame2);
	
	printf("----FINISHED TEST CASE 2----\n\n\n");
	printf("----TEST CASE 3: BAD INPUT RE: duplicate cards-----\n");
	printf("Attempting to initialize game with duplicate cards; should return -1\n");
	struct gameState *testGame3=newGame();
	int *kc3=kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, adventurer);
	int test3_numPlayers=2;
	returnval=initializeGame(test3_numPlayers, kc3, 1234, testGame3);	
	if (returnval==-1)
	{
		printf("SUCCESS: registered that there are duplicate cards\n");
	}
	else 
	{
		printf("FAILURE: did not register that there are duplicate cards\n");
	}
	test_numPlayers(testGame3->numPlayers, test3_numPlayers);
	test_supplyCounts(testGame3->numPlayers, testGame3);
	
	printf("----FINISHED TEST CASE 3----\n\n\n");
	
	printf("----TEST CASE 4: BAD INPUT RE: non-kingdom cards-----\n");
	printf("Attempting to initialize game with duplicate cards; should return -1\n");
	
	struct gameState *testGame4=newGame();
	int *kc4=kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, copper);
	int test4_numPlayers=2;
	returnval=initializeGame(test4_numPlayers, kc4, 1234, testGame4);	
	if (returnval==-1)
	{
		printf("SUCCESS: registered that there is a non-kingdom card\n");
	}
	else 
	{
		printf("FAILURE: did not register that there is a non-kingdom card\n");
	}
	test_numPlayers(testGame4->numPlayers, test4_numPlayers);
	test_supplyCounts(testGame4->numPlayers, testGame4);
	printf("----FINISHED TEST CASE 4----\n\n\n");
	
	
	
	
	
}
int test_numPlayers(int actual, int plan)
{
	if (actual==plan)
	{
		printf("SUCCESS: %i matches %i\n", actual, plan);
		return 0;
	}
	else 
	{
		printf("FAILURE: %i does not match %i\n", actual, plan);
		return -1;
	}
}
int test_supplyCounts(int numPlayers, struct gameState *state)
{
	if ((state->supplyCount[copper])== 60 - (7 * numPlayers))
	{
		printf("SUCCESS: correct number of copper cards set: %i\n", state->supplyCount[copper]);
	}
	else if ((state->supplyCount[copper])!=60 - (7 * numPlayers))
	{
		printf("FAILURE: incorrect number of copper cards set: %i\n", state->supplyCount[copper]);

	}
	if (state->supplyCount[silver]==40)
	{
		printf("SUCCESS: correct number of silver cards set: %i\n", state->supplyCount[silver]);
	}
	else if (state->supplyCount[silver]!=40)
	{
		printf("FAILURE: incorrect number of silver cards set: %i\n", state->supplyCount[silver]);
	}
	if (state->supplyCount[gold]==30)
	{
		printf("SUCCESS: correct number of gold cards set: %i\n", state->supplyCount[gold]);
	}
	else if (state->supplyCount[gold]!=30)
	{
		printf("FAILURE: incorrect number of gold cards set: %i\n", state->supplyCount[gold]);
	}
	if (numPlayers==2)
	{
		if (state->supplyCount[curse]==10)
		{
			printf("SUCCESS: correct number of curse cards set: %i\n", state->supplyCount[curse]);
		}
		else 
		{
			printf("FAILURE: incorrect number of curse cards set: %i\n", state->supplyCount[curse]);
		}
		if (state->supplyCount[estate]==8)
		{
			printf("SUCCESS: correct number of estate cards set: %i\n", state->supplyCount[estate]);
		}
		else if (state->supplyCount[estate]!=8)
		{
			printf("FAILURE: incorrect number of estate cards set: %i\n", state->supplyCount[estate]);
		}
		if (state->supplyCount[duchy]==8)
		{
			printf("SUCCESS: correct number of duchy cards set: %i\n", state->supplyCount[duchy]);
		}
		else if (state->supplyCount[duchy]!=8)
		{
			printf("FAILURE: incorrect number of duchy cards set: %i\n", state->supplyCount[duchy]);
		}
		if (state->supplyCount[province]==8)
		{
			printf("SUCCESS: correct number of province cards set: %i\n", state->supplyCount[province]);
		}
		else if (state->supplyCount[province]!=8)
		{
			printf("FAILURE: incorrect number of province cards set: %i\n", state->supplyCount[province]);
		}

	}
	else 
	{
		if (numPlayers==3)
		{
			if (state->supplyCount[curse]==20)
			{
				printf("SUCCESS: correct number of curse cards set: %i\n", state->supplyCount[curse]);

			}
			else 
			{
				printf("FAILURE: incorrect number of curse cards set: %i\n", state->supplyCount[curse]);
			}
		}
		if (numPlayers==4)
		{
			if (state->supplyCount[curse]==30)
			{
				printf("SUCCESS: correct number of curse cards set: %i\n", state->supplyCount[curse]);
			}
			else 
			{
				printf("FAILURE: incorrect number of curse cards set: %i\n", state->supplyCount[curse]);
			}
		}
			
		if (state->supplyCount[estate]==12)
		{
			printf("SUCCESS: correct number of estate cards set: %i\n", state->supplyCount[estate]);

		}
		else if (state->supplyCount[estate]!=12)
		{
			printf("FAILURE: incorrect number of estate cards set: %i\n", state->supplyCount[estate]);
		}
		if (state->supplyCount[duchy]==12)
		{
			printf("SUCCESS: correct number of duchy cards set: %i\n", state->supplyCount[duchy]);

		}
		else if (state->supplyCount[duchy]!=12)
		{
			printf("FAILURE: incorrect number of duchy cards set: %i\n", state->supplyCount[duchy]);
		}
		if (state->supplyCount[province]==12)
		{
			printf("SUCCESS: correct number of province cards set: %i\n", state->supplyCount[province]);

		}
		else if (state->supplyCount[province]!=12)
		{
			printf("FAILURE: incorrect number of province cards set: %i\n", state->supplyCount[province]);
		}


	}
	return 0;
}
void test_num_kingcard(int numPlayers, struct gameState *state, int kingdomCards[10])
{
	int i;
	int j;
	for (i = adventurer; i <= treasure_map; i++)//loop all cards
	{
		for (j = 0; j < 10; j++) //loop chosen cards
		{
			if (kingdomCards[j]==i)
			{
				//check if card is a 'Victory' Kingdom card
				if (kingdomCards[j] == great_hall || kingdomCards[j] == gardens)
				{
					if (numPlayers==2)
					{ 
						//state->supplyCount[i] = 8; 
						if (state->supplyCount[i]==8)
						{
							printf("SUCCESS: supplycount at %i is %i\n", i, state->supplyCount[i]);
						}
						else if (state->supplyCount[i]!=8)
						{
							printf("FAILURE: supplycount at %i is %i\n", i, state->supplyCount[i]);
						}
					}
					else
					{ 
						//state->supplyCount[i] = 12; 
						if (state->supplyCount[i]==12)
						{
							printf("SUCCESS: supplycount at %i is %i\n", i, state->supplyCount[i]);
						}
						else if (state->supplyCount[i]!=12)
						{
							printf("FAILURE: supplycount at %i is %i\n", i, state->supplyCount[i]);
						}

					}
				}
				else
				{
					//state->supplyCount[i] = 10;
					if (state->supplyCount[i]==10)
					{
						printf("SUCCESS: supplycount at %i is %i\n", i, state->supplyCount[i]);
					}
					else if (state->supplyCount[i]!=10)
					{
						printf("FAILURE: supplycount at %i is %i\n", i, state->supplyCount[i]);
					}
				}
	      		break;
			}
			else    //card is not in the set choosen for the game
			 {
				//state->supplyCount[i] = -1;
				if (state->supplyCount[i]==-1)
				{
					printf("SUCCESS: supplycount at %i is %i\n", i, state->supplyCount[i]);
				}
				else if (state->supplyCount[i]!=-1)
				{
					printf("FAILURE: supplycount at %i is %i\n", i, state->supplyCount[i]);
				}
			}
	   }
	}

}
