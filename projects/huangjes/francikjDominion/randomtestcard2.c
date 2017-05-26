/**************************************************************************************************
** Name: Jessica Huang
** Course: CS362_400_SP17
** Description: Assignment 4 - Random test for sea hag card.
***************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define NUM_TESTS 2000

int checkPlaySeaHag(int curPlayer, struct gameState *G, struct gameState *pre)
{
	int i;

	// Check the number of players
	if (G->numPlayers == 0)
		printf("0 Players\n\n");
	if (G->numPlayers == 5)
		printf("5 Players\n\n");

	// Check that the current player has fewer cards in hand
	if (G->handCount[curPlayer] > pre->handCount[curPlayer])
		printf("Test Failed: Current player has one less card from playing Sea Hag\n");
	// Check that the current player has no changes to deck
	if (G->deckCount[curPlayer] != pre->deckCount[curPlayer])
		printf("Test Failed: Current player has same deck count\n");
	// Check that the current player has no changes to discard
	if (G->discardCount[curPlayer] != pre->discardCount[curPlayer])
		printf("Test Failed: Current player has same discard count\n");
	// Check that the top of the current player's deck is the same as before
	if (G->deck[curPlayer][G->deckCount[curPlayer] - 1] != pre->deck[curPlayer][pre->deckCount[curPlayer] - 1])
	{
		printf("Test Failed: Current player does not gain a curse\n");
		printf("Previous top deck: %d", pre->deck[curPlayer][pre->deckCount[curPlayer] - 1]);
		printf("Current top deck : %d", G->deck[curPlayer][G->deckCount[curPlayer] - 1]);
	}
	// Check the decks, hands, and discard piles of the other players
	for (i = 0; i < G->numPlayers; i++)
	{
		if (i != curPlayer)
		{
			if (G->handCount[i] != pre->handCount[i])
				printf("Test Failed: Other players have same hand count\n");
			if (G->deckCount[i] != pre->deckCount[i])
			{
				printf("Test Failed: Player %d has the same deck count\n", i);
				printf("Previous deck count: %d\n", pre->deckCount[i]);
				printf("Current deck count : %d\n\n", G->deckCount[i]);
			}
			if (G->discardCount[i] != pre->discardCount[i] + 1)
			{
				printf("Test Failed: Player %d one more card in discard\n", i);
				printf("Previous discard count: %d\n", pre->discardCount[i]);
				printf("Current discard count : %d\n\n", G->discardCount[i]);
			}
			// Make sure the top card of the deck is a curse
			if (G->deck[i][G->deckCount[i] - 1] != curse)
			{
				printf("Test Failed: Player %d has a curse on top of deck\n", i);
				printf("Previous top deck: %d\n", pre->deck[i][G->deckCount[i] - 1]);
				printf("Current top deck : %d\n\n", G->deck[i][G->deckCount[i] - 1]);
			}
		}
	}

	// Check Curse card pile, which should be less
	if (G->supplyCount[0] >= pre->supplyCount[0])
		printf("Test Failed: Fewer curse cards in supply\n\n");
	// Check Victory card piles for any changes
	for (i = 1; i <= 3; i++)
	{
		if (G->supplyCount[i] != pre->supplyCount[i])
			printf("Test Failed: No change to Victory cards\n");
	}
	// Check Kingdom card piles for any changes
	for (i = 7; i < 27; i++)
	{
		if (G->supplyCount[i] != pre->supplyCount[i])
			printf("Test Failed: No change to Kingdom cards\n");
	}
	return 0;
}

int main()
{
	int i, j, curPlayer, players;
	int k[10] = { adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall };
	struct gameState G;
	struct gameState pre;

	srand(time(NULL));
	printf("\n	RANDOM TESTS - SEA HAG CARD:\n\n");
	for (i = 0; i < NUM_TESTS; i++)
	{
		int handPos;
		players = rand() % MAX_PLAYERS + 1;
		initializeGame(players, k, 3, &G);
		// Random number of players ranging from 1 - 4
		curPlayer = rand() % players;
		G.whoseTurn = curPlayer;
		// Random number of cards in hand, deck and discard pile from 0 to max defined in dominion.h
		for (j = 0; j < players; j++)
		{
			G.deckCount[j] = rand() % MAX_DECK;
			G.discardCount[j] = rand() % MAX_DECK;
			G.handCount[j] = rand() % MAX_HAND;
		}

		if (G.handCount[curPlayer] > 0)
			handPos = rand() % G.handCount[curPlayer];
		else
			handPos = 0;

		// Copy the state of the game before playing sea hag card
		memcpy(&pre, &G, sizeof(struct gameState));
		int r = cardEffect(sea_hag, 0, 0, 0, &G, handPos, 0);
		assert(r == 0);

		r = checkPlaySeaHag(curPlayer, &G, &pre);
		assert(r == 0);
	}

	printf("	\nTEST SUCCESSFUL\n\n");

	return 0;
}