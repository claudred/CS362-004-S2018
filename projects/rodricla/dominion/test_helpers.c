#include "test_helpers.h"


void printPlayerDeck(int player, struct gameState *game)
{
	int n=game->deckCount[player];
	int i=0;
	for (i=0; i < n; i++)
	{
		printf("player %i %i deck card is %i\n", player+1, i+1, game->deck[player][i]);
	}
}
void printPlayerHand(int player, struct gameState *game)
{
	int n=game->handCount[player];
	int i=0;
	for (i=0; i < n; i++)
	{
		printf("player %i %i hand card is %i\n", player+1, i+1, game->hand[player][i]);
	}
}
void printSupplyCount(struct gameState *game)
{
	int i = 0; 
	for (i=0; i < 27; i++)
	{
		printf("%i: %i\n", i, game->supplyCount[i]);
	}
}
void printDiscard(int player, struct gameState *game)
{
	int n = game->discardCount[player]; 
	int i;
	for (i=0; i < n; i++)
	{
		printf("DISCARD %i: %i\n", i, game->discard[player][i]);
	}

}
int checkLastDiscard(int player, int card, struct gameState *game)
{

	int n=game->discardCount[player];
	if (game->discard[player][n-1]==card)
	{
		return 1;
	}
	return 0;
}
int checkLastPlayed(int card, struct gameState *game)
{
	int n=game->playedCardCount;
	if (game->playedCards[n-1]==card)
	{
		return 1;
	}
	return 0;
}