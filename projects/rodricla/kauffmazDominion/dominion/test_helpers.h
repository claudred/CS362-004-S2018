#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void printPlayerDeck(int player, struct gameState *game);
void printPlayerHand(int player, struct gameState *game);
void printSupplyCount(struct gameState *game);
void printDiscard(int player, struct gameState *game);
int checkLastDiscard(int player, int card, struct gameState *game);
int checkLastPlayed(int card, struct gameState *game);