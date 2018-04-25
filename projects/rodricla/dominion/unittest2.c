#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
int test(int input[10], int output[10]);
int check_card(int card);
int main(int argc, char *argv[]) 
{
	
	printf("+++++STARTING unit test 2: Testing kingdomCards() function+++++\n\n");

	printf("---GOOD INPUT: TEST ONE: adding adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall to kingdom cards----\n");
	int setUs[]={adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int *kc=kingdomCards(adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy);
	test(setUs, kc);
	
	printf("---BAD INPUT: TEST ONE: adding adventurer, copper, feast, gardens, mine, remodel, smithy, village, baron, great_hall to kingdom cards----\n");
	int setUs2[]={adventurer, copper, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int *kc2=kingdomCards(adventurer, copper, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy);
	test(setUs2, kc2);
	
	printf("\n\n+++++FINISHED unit test 2: Testing kingdomCards() function+++++\n\n");
}
int test(int setUs[10], int kc[10])
{
	printf("Checking that each kingdom card corresponds to the intended card\n");
	int i=0;
	for (i=0; i < 10; i++)
	{
		
		if (kc[i]==setUs[i])
		{
			printf("SUCCESS: Card #%i with enum %i successfully set to kingdom cards array\n", i, kc[i]);
			if (check_card(kc[i])==-1)
			{
				printf("FAILURE: Function allowed a non-kingdom card to be added\n");
			}
		}
		if ((kc[i]!=setUs[i])&&(check_card(setUs[i])==-1))
		{
			if (check_card(kc[i])==-1)
			{
				printf("SUCCESS: Function did NOT allow a non-kingdom card to be added\n");
			}
		}
	}
	return 0;
	
}
int check_card(int card)
{
	if (card<adventurer)
	{
		return -1;
	}
	return 0;
}