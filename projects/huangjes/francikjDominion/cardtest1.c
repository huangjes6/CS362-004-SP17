/**************************************************************************************************
* ** Name: Jessica Huang
* ** Course: CS362_400_SP17
* ** Description: Unit test for Adventurer function in dominion.c.
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

// Function to check if the current state is less than the previous state and prints a statement
void assertLess(int currentState, int preState, char desc[])
{
	if (currentState < preState)
		printf("PASS: %s", desc);
	else
		printf("FAIL: %s", desc);
}

// Function to check if the current state is greater or equal to the previous state and prints a statement
void assertGreaterEqual(int currentState, int preState, char desc[])
{
	if (currentState >= preState)
		printf("PASS: %s", desc);
	else
		printf("FAIL: %s", desc);
}

// Function to check if the current state is greater than the previous state and prints a statement
void assertGreater(int currentState, int preState, char desc[])
{
	if (currentState > preState)
		printf("PASS: %s", desc);
	else
		printf("FAIL: %s", desc);
}

int main()
{
	printf(" UNIT TEST FOR ADVENTURER\n\n");

	struct gameState G;
	struct gameState preG;
	int i;
	int z = 0;
	int numPlayers = 2;
	int currentPlayer;
	int tempHand[500];
	int k[10] = { adventurer, embargo, village, minion, mine,
		cutpurse, sea_hag, tribute, smithy, council_room };

	initializeGame(numPlayers, k, 1, &G);

	// copy the game state to a test case
	memcpy(&preG, &G, sizeof(struct gameState));
	currentPlayer = whoseTurn(&G);
	G.hand[currentPlayer][0] = adventurer;
	// adventurerRefactored(&G);
/* 	// Check if anything changes with state if there are already 2 treasures drawn
	assertEqual(G.handCount[currentPlayer], preG.handCount[currentPlayer], "Hand Count when 2 treasures already drawn\n");
	assertEqual(G.deckCount[currentPlayer], preG.deckCount[currentPlayer], "Deck Count when 2 treasures already drawn\n");
	assertEqual(G.discardCount[currentPlayer], preG.discardCount[currentPlayer], "Discard Count when 2 treasures already drawn\n"); */

	G = preG;
	G.hand[currentPlayer][0] = adventurer;
	// Draw treasures and check hand
	adventurerRefactored(&G);
	if (G.handCount[currentPlayer] == preG.handCount[currentPlayer] + 1)
		printf("PASS: 2 treasures drawn and in hand\n");
	else
		printf("FAIL: 2 treasures drawn and in hand\n");

	// Check to see if deck is less than before 
	assertLess(G.deckCount[currentPlayer], preG.deckCount[currentPlayer], "2 treasures drawn, deck decreases\n");

	// Check if discard pile is greater or equal to before (will be equal only if treasures were on top)
	assertGreaterEqual(G.discardCount[currentPlayer], preG.discardCount[currentPlayer], "2 treasures drawn, discard stays same or increases\n");

	G = preG;
	// Check if the deck will be shuffled if it is zero
	for (i = 0; i < 5; i++)
	{
		G.deck[currentPlayer][i] = sea_hag;
		G.deckCount[currentPlayer]--; 
	}
	G.hand[currentPlayer][0] = adventurer;
	adventurerRefactored(&G);
	assertGreater(G.deckCount[currentPlayer], preG.deckCount[currentPlayer], "Deck shuffled\n");

	G = preG;
	// Insert one treasure into the deck. If there is only one treasure, that is the only one the player gets.
	G.deckCount[currentPlayer] = 2;
	G.deck[currentPlayer][0] = copper;
	G.deck[currentPlayer][1] = smithy;
	G.hand[currentPlayer][0] = adventurer;
	i = adventurerRefactored(&G);
	assertEqual(i, 0, "Only 1 treasure, function ends\n");

	// There should only be one extra card in the player's hand
	if (G.handCount[currentPlayer] == preG.handCount[currentPlayer])
		printf("PASS: 1 treasures drawn and in hand\n");
	else
		printf("FAIL: 1 treasures drawn and in hand\n");

	// Check if Adventurer was discarded
	for (i = 0; i < G.handCount[currentPlayer]; i++)
	{
		if (G.hand[currentPlayer][i] == adventurer)
			z++;
	}
	assertEqual(z, 0, "Adventurer discarded from hand\n");

	// Check other player for any changes in state
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