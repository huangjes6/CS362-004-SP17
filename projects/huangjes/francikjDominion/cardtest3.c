/**************************************************************************************************
* ** Name: Jessica Huang
* ** Course: CS362_400_SP17
* ** Description: Unit test for Cutpurse function in dominion.c.
* ***************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

// Function to make sure two parameters are equal and prints a statement
void assertEqual(int currentState, int preState, char desc[])
{
	if (currentState == preState)
		printf("PASS: %s", desc);
	else
		printf("FAIL: %s", desc);
}


int main()
{
	printf(" UNIT TEST FOR CUTPURSE\n\n");

	struct gameState G;
	struct gameState preG;
	int i;
	int prevCopperCt = 0;
	int copperCt = 0;
	int playerPrevCopperCt = 0;
	int playerCopperCt = 0;
	int numPlayers = 2;
	int cutpurseCt = 0;
	int currentPlayer;
	int k[10] = { adventurer, embargo, village, minion, mine,
		cutpurse, sea_hag, tribute, smithy, council_room };

	initializeGame(numPlayers, k, 1, &G);
	currentPlayer = whoseTurn(&G);

	// Give the other player some cards. Set a few to coppers
	for (i = 0; i < 5; i++)
	{
		drawCard(1, &G);
	}
	G.hand[1][0] = copper;
	G.hand[2][0] = copper;
	G.hand[3][0] = copper;
	for (i = 0; i < 5; i++)
	{
		if (G.hand[1][i] == copper)
			prevCopperCt++;
		if (G.hand[0][i] == copper)
			playerPrevCopperCt++;
	}

	// copy the game state to a test case
	memcpy(&preG, &G, sizeof(struct gameState));


	G.hand[currentPlayer][5] = cutpurse;
	cardEffect(cutpurse, 0, 0, 0, &G, 0, 0);
	// Check if the current player has 2 more coins
	assertEqual(G.coins, preG.coins + 2, "Gain 2 coins\n");
	for (i = 0; i < 5; i++)
	{
		if (G.hand[0][i] == copper)
			playerCopperCt++;
		if (G.hand[0][i] == cutpurse)
			cutpurseCt++;
	}

	// Check if player discards a copper
	assertEqual(playerPrevCopperCt, playerCopperCt, "Player does not discard copper\n");
	// Check if cutpurse is discarded
	assertEqual(cutpurseCt, 0, "Player discards Cutpurse\n");
	assertEqual(G.discardCount[currentPlayer], preG.discardCount[currentPlayer] + 1, "Add cutpurse to discard pile\n");

	// Check state of other player
	if (currentPlayer == 0)
		currentPlayer = 1;
	else if (currentPlayer == 1)
		currentPlayer = 0;
	for (i = 0; i < G.handCount[currentPlayer]; i++)
	{
		if (G.hand[currentPlayer][i] == copper)
			copperCt++;
	}
	assertEqual(copperCt, prevCopperCt - 1, "Other player discards a copper\n");
	assertEqual(G.handCount[currentPlayer], preG.handCount[currentPlayer] - 1, "Other player has one less card in hand from copper\n");
	assertEqual(G.deckCount[currentPlayer], preG.deckCount[currentPlayer], "Other player's deck is same as previous state\n");
	assertEqual(G.discardCount[currentPlayer], preG.discardCount[currentPlayer] + 1, "Other player's discard increments from copper\n");

	// Check Victory card piles for any changes
	for (i = 1; i <= 3; i++)
	{
		assertEqual(G.supplyCount[i], preG.supplyCount[i], "No change to Victory card piles\n");
	}
	// Check Kingdom card piles for any changes
	for (i = 7; i < 27; i++)
	{
		assertEqual(G.supplyCount[i], preG.supplyCount[i], "No change to Kingdom card piles\n");
	}

	printf("\n TEST SUCCESSFULLY COMPLETED\n");
	return 0;
}