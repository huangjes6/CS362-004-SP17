/**************************************************************************************************
* ** Name: Jessica Huang
* ** Course: CS362_400_SP17
* ** Description: Unit test for Smithy function in dominion.c.
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
	printf(" UNIT TEST FOR SMITHY\n\n");

	struct gameState G;
	struct gameState preG;
	int i;
	int z = 0;
	int numPlayers = 2;
	int currentPlayer;
	int k[10] = { adventurer, embargo, village, minion, mine,
		cutpurse, sea_hag, tribute, smithy, council_room };

	initializeGame(numPlayers, k, 1, &G);

	// copy the game state to a test case
	memcpy(&preG, &G, sizeof(struct gameState));
	currentPlayer = whoseTurn(&G);
	// Play smithy and check if there are 3 more cards in the player's hand
	smithyRefactored(&G, 0);
	// Should have 2 more cards than before because should discard smithy
	assertEqual(G.handCount[currentPlayer], preG.handCount[currentPlayer] + 2, "Draw 3 cards\n");
	// Check if smithy was discarded
	for (i = 0; i < G.handCount[currentPlayer]; i++)
	{
		if (G.hand[currentPlayer][i] == smithy)
			z++;
	}
	assertEqual(z, 0, "Smithy discarded\n");
	assertEqual(G.discardCount[currentPlayer], preG.discardCount[currentPlayer] + 1, "Increment discard pile\n");
	// Check if current player's deck has decreased in size by 3
	assertEqual(G.deckCount[currentPlayer], preG.deckCount[currentPlayer] - 3, "Cards drawn from current player's deck\n");

	// Check state of other player
	if (currentPlayer == 0)
		currentPlayer = 1;
	else if (currentPlayer == 1)
		currentPlayer = 0;
	assertEqual(G.handCount[currentPlayer], preG.handCount[currentPlayer], "Other player's hand is same as previous state\n");
	assertEqual(G.deckCount[currentPlayer], preG.deckCount[currentPlayer], "Other player's deck is same as previous state\n");
	assertEqual(G.discardCount[currentPlayer], preG.discardCount[currentPlayer], "Other player's discard is same as previous state\n");

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