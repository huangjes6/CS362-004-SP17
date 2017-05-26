/**************************************************************************************************
* ** Name: Jessica Huang
* ** Course: CS362_400_SP17
* ** Description: Unit test for numHandCards function in dominion.c.
* ***************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

// Compares whether the number of cards returned matches the number of cards that should return
void assertTrue(int numCardsReturned, int numCards, char desc[])
{
	if (numCardsReturned == numCards && numCards >= 0)
	{
		printf("PASS: Correct # cards - %s", desc);
	}
	else
	{
		printf("FAIL: Incorrect # cards - %s", desc);
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
	printf(" UNIT TEST FOR numHandCards FUNCTION \n\n");
	struct gameState G;
	struct gameState preG;
	int numPlayers = 2;
	int i;
	int k[10] = { adventurer, embargo, village, minion, mine,
		cutpurse, sea_hag, tribute, smithy, council_room };

	initializeGame(numPlayers, k, 1, &G);
	// copy the game state to a test case
	memcpy(&preG, &G, sizeof(struct gameState));
	// At the beginning of the game, each player has 5 cards in their hands
	assertTrue(numHandCards(&G), 5, "At start of game\n");

	// Draw a card
	drawCard(G.whoseTurn, &G);
	assertTrue(numHandCards(&G), 6, "When add card\n");

	drawCard(G.whoseTurn, &G);
	drawCard(G.whoseTurn, &G);
	assertTrue(numHandCards(&G), 8, "When draw 2 cards\n");

	// Discard a card from hand
	discardCard(0, G.whoseTurn, &G, 0);
	assertTrue(numHandCards(&G), 7, "When discard card\n");

	discardCard(0, G.whoseTurn, &G, 0);
	assertTrue(numHandCards(&G), 6, "When discard card\n");

	while (numHandCards(&G) > 0)
	{
		discardCard(0, G.whoseTurn, &G, 0);
	}

	assertTrue(numHandCards(&G), 0, "When all cards discarded\n");

	// Check if this number can be negative
	discardCard(0, G.whoseTurn, &G, 0);
	assertTrue(numHandCards(&G), -1, "Should not have negative cards\n");

	// Switching to other player
	endTurn(&G);
	assertTrue(numHandCards(&G), 5, "Other player cards don't change\n");

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