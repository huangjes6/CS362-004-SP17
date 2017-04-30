/**************************************************************************************************
** Name: Jessica Huang
** Course: CS362_400_SP17
** Description: Unit test for fullDeckCount function in dominion.c.
***************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main()
{
	struct gameState G;
	int numPlayers = 2;
	int seed = 1000;
	int i;
	int k[10] = { adventurer, embargo, village, minion, mine,
		cutpurse, sea_hag, tribute, smithy, council_room };

	// Testing game state with different number of province cards
	initializeGame(numPlayers, k, seed, &G);

	int numCards = numHandCards(&G);
	printf("%d", numCards);

	return 0;
}