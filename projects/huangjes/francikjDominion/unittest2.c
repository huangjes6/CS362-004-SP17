/**************************************************************************************************
 * ** Name: Jessica Huang
 * ** Course: CS362_400_SP17
 * ** Description: Unit test for handCard function in dominion.c.
 * ***************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


// Assert that the cards are in the right positions in the player's hands
void assertTrue(struct gameState G, int handPos) 
{
	if (handCard(handPos, &G) == handPos)
	{
		printf("PASS: Card in correct position\n");
	}
	else 
	{
		printf("FAIL: Card in incorrect position\n");
	}
}

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
	printf(" UNIT TEST FOR handCard FUNCTION\n\n");
	struct gameState G;
	struct gameState preG;
	int i;
	int numPlayers = 2;
	int seed = 1000;
	int currentPlayer = 1;
	int k[10] = { adventurer, embargo, village, minion, mine,
		cutpurse, sea_hag, tribute, smithy, council_room };

	initializeGame(numPlayers, k, seed, &G);
	// copy the game state to a test case
	memcpy(&preG, &G, sizeof(struct gameState));
	// Change the turn to the currentPlayer.
	G.whoseTurn = currentPlayer;
	// Add cards into the hands of the current player
	for (i = 0; i <= 26; i++) 
	{
		G.hand[currentPlayer][i] = i;
	}

	// Check if the cards are in the correct positions.
	for (i = 0; i <= 26; i++)
	{
		assertTrue(G, i);
	}

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
