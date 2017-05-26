/**************************************************************************************************
* ** Name: Jessica Huang
* ** Course: CS362_400_SP17
* ** Description: Unit test for Great Hall card in cardEffects function in dominion.c.
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
	printf("UNIT TEST FOR GREAT HALL\n\n");

	struct gameState G;
	struct gameState preG;
	int numPlayers = 2;
	int currentPlayer;
	int i;
	int greatHallCt = 0;
	int k[10] = { adventurer, embargo, village, minion, mine,
		cutpurse, sea_hag, tribute, smithy, council_room };

	initializeGame(numPlayers, k, 1, &G);
	currentPlayer = whoseTurn(&G);
	// copy the game state to a test case
	memcpy(&preG, &G, sizeof(struct gameState));

	G.hand[currentPlayer][0] = great_hall;
	great_hallRefactored(&G, 0);
	// Check if the current player has gained a card
	assertEqual(G.handCount[currentPlayer], preG.handCount[currentPlayer], "Draw a card\n");
	// Check if the current player has gained an action
	assertEqual(G.numActions, preG.numActions + 1, "Gained action\n");
	// Check if great_hall is still in player's hand
	for (i = 0; i < G.handCount[currentPlayer]; i++)
	{
		if (G.hand[currentPlayer][i] == great_hall)
			greatHallCt++;
	}
	assertEqual(greatHallCt, 0, "Great Hall discarded\n");
	// Check if discard pile is greater
	assertEqual(G.discardCount[currentPlayer], preG.discardCount[currentPlayer] + 1, "Great Hall in discard pile\n");

	// Check state of other player
	if (currentPlayer == 0)
		currentPlayer = 1;
	else if (currentPlayer == 1)
		currentPlayer = 0;
	assertEqual(G.handCount[currentPlayer], preG.handCount[currentPlayer], "Other player's hand is same as previous state\n");
	assertEqual(G.deckCount[currentPlayer], preG.deckCount[currentPlayer], "Other player's deck is same as previous state\n");
	assertEqual(G.discardCount[currentPlayer], preG.discardCount[currentPlayer], "Other player's discard is same as previous state\n");
	// Check if this player has gained more actions
	endTurn(&G);
	assertEqual(G.numActions, preG.numActions, "Other player did not gain action\n");

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

