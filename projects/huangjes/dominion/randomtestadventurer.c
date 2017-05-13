/**************************************************************************************************
** Name: Jessica Huang
** Course: CS362_400_SP17
** Description: Assignment 4 - Random test for adventurer card.
***************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define NUM_TESTS 10000

int checkPlayAdventurer(int curPlayer, struct gameState *G, struct gameState *pre)
{
	int i;
	// Check the number of players
	if (G->numPlayers == 0)
		printf("0 Players\n\n");
	if (G->numPlayers == 5)
		printf("5 Players\n\n");
	int treasureCount = fullDeckCount(curPlayer, copper, pre) + fullDeckCount(curPlayer, silver, pre)
		+ fullDeckCount(curPlayer, gold, pre);

	if (treasureCount == 0)
		printf("NO TREASURE...\n\n");
	if (treasureCount == 1)
		printf("ONE TREASURE...\n\n");
	// Check to see if the player's hand has 
	if (pre->deckCount[curPlayer] > 0 && pre->discardCount[curPlayer] > 0)
	{
		if (treasureCount > 1 && pre->handCount[curPlayer] >= G->handCount[curPlayer])
		{
			printf("Test Failed: Gained 2 treasures\n");
			printf("Hand Count Before: %d\n", pre->handCount[curPlayer]);
			printf("Hand Count After: %d\n\n", G->handCount[curPlayer]);
		}
		else if (treasureCount == 1 && pre->handCount[curPlayer] > G->handCount[curPlayer])
		{
			printf("Test Failed: Only 1 treasure in full deck. Gained 1 treasure\n");
			printf("Hand Count Before: %d\n", pre->handCount[curPlayer]);
			printf("Hand Count After: %d\n\n", G->handCount[curPlayer]);
		}
		else if (treasureCount == 0 && pre->handCount[curPlayer] < G->handCount[curPlayer])
		{
			printf("Test Failed: No treasures in deck. Hand count less by 1\n");
			printf("Hand Count Before: %d\n", pre->handCount[curPlayer]);
			printf("Hand Count After: %d\n\n", G->handCount[curPlayer]);
		}
		if (pre->deckCount[curPlayer] <= G->deckCount[curPlayer])
		{
			printf("Test Failed: Drew cards, deck count is smaller\n");
			printf("Deck Count Before: %d\n", pre->deckCount[curPlayer]);
			printf("Deck Count After : %d\n\n", G->deckCount[curPlayer]);
		}
	}
	else if (pre->deckCount[curPlayer] == 0)
	{
		if (pre->discardCount[curPlayer] > G->discardCount[curPlayer])
		{
			printf("Test Failed: Discard pile shuffled into deck to replenish supplies\n");
			printf("Discard Count Before: %d\n", pre->discardCount[curPlayer]);
			printf("Discard Count After : %d\n\n", G->discardCount[curPlayer]);
		}
	}
	// Check Victory card piles for any changes
	for (i = 0; i <= 3; i++)
	{
		if (G->supplyCount[i] != pre->supplyCount[i])
			printf("Test Failed: No change to Victory cards\n\n");
	}
	// Check Kingdom card piles for any changes
	for (i = 7; i < 27; i++)
	{
		if (G->supplyCount[i] != pre->supplyCount[i])
			printf("Test Failed: No change to Kingdom cards\n\n");
	}

	return 0;
}

int main()
{
	int i, j, h, curPlayer, players;
	int k[10] = { adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall };
	struct gameState G; 
	struct gameState pre;

	srand(time(NULL));
	printf("\n	RANDOM TESTS - ADVENTURER CARD:\n\n");
	for (i = 0; i < NUM_TESTS; i++)
	{
		players = rand() % MAX_PLAYERS + 1;
		initializeGame(players, k, 3, &G);
		// Random number of players ranging from 1 - 4
		curPlayer = rand() % players;
		// Random number of cards in hand, deck and discard pile from 0 to max defined in dominion.h
		for (j = 0; j < players; j++)
		{
			G.deckCount[j] = rand() % MAX_DECK;
			G.discardCount[j] = rand() % MAX_DECK;
			G.handCount[j] = rand() % MAX_HAND;
		}
		// Fill players' piles with random cards
		for (j = 0; j < players; j++)
		{
			for (h = 0; h < G.handCount[j]; h++)
				G.hand[j][h] = rand() % 26;
			for (h = 0; h < G.deckCount[j]; h++)
				G.hand[j][h] = rand() % 26;
			for (h = 0; h < G.discardCount[j]; h++)
				G.hand[j][h] = rand() % 26;
		}

		// Copy the state of the game before playing adventurer card
		int temphand[MAX_HAND];
		memcpy(&pre, &G, sizeof(struct gameState));

		int r = playAdventurer(0, curPlayer, &G, temphand, 0, 0);
		assert(r == 0);

		r = checkPlayAdventurer(curPlayer, &G, &pre);
		assert(r == 0);

	}
	printf("ALL TESTS OK\n");

	return 0;
}