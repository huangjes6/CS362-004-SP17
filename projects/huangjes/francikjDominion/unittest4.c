/**************************************************************************************************
* ** Name: Jessica Huang
* ** Course: CS362_400_SP17
* ** Description: Unit test for fullDeckCount function in dominion.c.
* ***************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


// Checks if the previous state is equal to the state after actions have been taken
void assertTrue(int preG, int postG, char desc[])
{
	if (preG == postG)
	{
		printf("PASS: %s", desc);
	}
	else
	{
		printf("FAIL: %s", desc);
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
	printf(" UNIT TEST FOR fullDeckCount FUNCTION\n\n");
	struct gameState G;
	struct gameState preG;
	int i;
	int numPlayers = 2;
	int currentPlayer;
	int numHand;
	int k[10] = { adventurer, embargo, village, minion, mine,
		cutpurse, sea_hag, tribute, smithy, council_room };

	initializeGame(numPlayers, k, 1, &G);
	currentPlayer = G.whoseTurn;
	// copy the game state to a test case
	memcpy(&preG, &G, sizeof(struct gameState));
	numHand = G.handCount[currentPlayer];

	// Add 5 province to the players hand and check if it is 5 more than the previous game state
	for (i = numHand; i < numHand + 5; i++)
	{
		//drawCard(currentPlayer, &G);
		G.handCount[currentPlayer]++;
		G.hand[currentPlayer][i] = 3;
	}

	assertTrue(fullDeckCount(currentPlayer, 3, &G), (fullDeckCount(currentPlayer, 3, &preG) + 5), "Added 5 provinces to hand\n");

	// Add 5 provinces to players deck
	for (i = 0; i < 5; i++)
	{
		G.deckCount[currentPlayer]++;
		G.deck[currentPlayer][i] = 3;
	}
	assertTrue(fullDeckCount(currentPlayer, 3, &G), (fullDeckCount(currentPlayer, 3, &preG) + 10), "Added 5 provinces to discard\n");

	// Add 5 provinces to players discard pile
	for (i = 0; i < 5; i++)
	{
		G.discardCount[currentPlayer]++;
		G.discard[currentPlayer][i] = 3;
	}
	assertTrue(fullDeckCount(currentPlayer, 3, &G), (fullDeckCount(currentPlayer, 3, &preG) + 15), "Added 5 provinces to deck\n");

	// Discard 3 provinces from the players hand and add to discard pile
	for (i = 0; i < 3; i++)
	{
		G.discardCount[currentPlayer]++;
		discardCard(i, currentPlayer, &G, 0);
	}
	assertTrue(fullDeckCount(currentPlayer, 3, &G), (fullDeckCount(currentPlayer, 3, &preG) + 15), "Discard 3 provinces from hand\n");

	// Trash 2 provinces from the hand
	for (i = 0; i < 2; i++)
	{
		discardCard(i, currentPlayer, &G, 1);
	}
	assertTrue(fullDeckCount(currentPlayer, 3, &G), (fullDeckCount(currentPlayer, 3, &preG) + 13), "Trashing 2 provinces\n");
	// Adding 1 of each card into discard
	for (i = 0; i <= 27; i++)
	{
		if (i == 3)
		{
			G.discardCount[currentPlayer]++;
			G.discard[currentPlayer][i + 5] = i;
			assertTrue(fullDeckCount(currentPlayer, i, &G), (fullDeckCount(currentPlayer, i, &preG) + 14), "Adding 1 of each card in discard");
			printf(": index %d\n", i);
		}
		else
		{
			G.discardCount[currentPlayer]++;
			G.discard[currentPlayer][i + 5] = i;
			assertTrue(fullDeckCount(currentPlayer, i, &G), (fullDeckCount(currentPlayer, i, &preG) + 1), "Adding 1 of each card in discard");
			printf(": index %d\n", i);
		}
	}
	// Switch to other player to check hand deck, which should not change
	endTurn(&G);
	currentPlayer = G.whoseTurn;
	assertTrue(fullDeckCount(currentPlayer, i, &G), fullDeckCount(currentPlayer, i, &preG), "Other player's deck should be the same\n");

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