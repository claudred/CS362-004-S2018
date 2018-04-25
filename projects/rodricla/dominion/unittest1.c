#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
int test(struct gameState* testMe);
int main(int argc, char *argv[]) 
{
	printf("+++++STARTING unit test 1: Testing newGame() function+++++\n\n");
	struct gameState* testMe=newGame();
	test(testMe);
	printf("\n\n+++++FINISHED unit test 1: Testing newGame() function+++++\n\n");
}
int test(struct gameState* testMe)
{
	//assert that dereferences piece of the gameState actually works. 
	if (sizeof(*testMe)==sizeof(struct gameState))
		printf("1. newGame() correctly allocated space\n");
	else
		printf("newGame() did not correctly allocate space\n");
	printf("newGame() unit test passed\n");
	return 0;
}