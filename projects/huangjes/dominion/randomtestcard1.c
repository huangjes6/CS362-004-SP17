/**************************************************************************************************
** Name: Jessica Huang
** Course: CS362_400_SP17
** Description: Assignment 4 - Random test for smithy card.
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

int checkPlaySmithy(int curPlayer, struct gameState *G, struct gameState *pre)
{
	int i;

	// Check the number of players
	if (G->numPlayers == 0)
		printf("0 Players\n\n");
	if (G->numPlayers == 5)
		printf("5 Players\n\n");
	// Hand count should be 2 more than before after playing Smithy
	if (pre->handCount[curPlayer] + 2 != G->handCount[curPlayer])
	{
		printf("Test Failed: Draw 3 cards, add to hand\n");
		printf("Hand Count Before: %d\n", pre->handCount[curPlayer]);
		printf("Hand Count After: %d\n\n", G->handCount[curPlayer]);
	}
	// Deck count should have 3 less than before
	if (pre->deckCount[curPlayer] >= 3 && pre->deckCount[curPlayer] - 3 != G->deckCount[curPlayer])
	{
		printf("Test Failed: Draw 3 cards from deck\n");
		printf("Deck Count Before: %d\n", pre->deckCount[curPlayer]);
		printf("Deck Count After: %d\n\n", G->deckCount[curPlayer]);
	}
	// Discard pile should be the same
	if (pre->deckCount[curPlayer] >= 3 && pre->discardCount[curPlayer] != G->discardCount[curPlayer])
	{
		printf("Test Failed: No discard\n");
		printf("Discard Count Before: %d\n", pre->discardCount[curPlayer]);
		printf("Discard Count After : %d\n\n", G->discardCount[curPlayer]);
	}

	// Check other players' cards for changes. 
	for (i = 0; i < G->numPlayers; i++)
	{
		if (i != curPlayer)
		{
			if (G->handCount[i] != pre->handCount[i])
			{
				printf("Test Failed: Player %d has the same hand count\n", i);
				printf("Previous hand count: %d\n", pre->handCount[i]);
				printf("Current hand count : %d\n\n", G->handCount[i]);
			}
			if (G->deckCount[i] != pre->deckCount[i])
			{
				printf("Test Failed: Player %d has the same deck count\n", i);
				printf("Previous deck count: %d\n", pre->deckCount[i]);
				printf("Current deck count : %d\n\n", G->deckCount[i]);
			}
			if (G->discardCount[i] != pre->discardCount[i])
			{
				printf("Test Failed: Player %d one more card in discard\n", i);
				printf("Previous discard count: %d\n", pre->discardCount[i]);
				printf("Current discard count : %d\n\n", G->discardCount[i]);
			}
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
	printf("\n	RANDOM TESTS - SMITHY CARD:\n\n");
	for (i = 0; i < NUM_TESTS; i++)
	{
		int handPos;
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

		if (G.handCount[curPlayer] > 0)
			handPos = rand() % G.handCount[curPlayer];
		else
			handPos = 0;
			
		// Copy the state of the game before playing smithy card
		memcpy(&pre, &G, sizeof(struct gameState));
		int r = playSmithy(curPlayer, &G, handPos);
		assert(r == 0);

		r = checkPlaySmithy(curPlayer, &G, &pre);
		assert(r == 0);
	}

	printf("	\nTEST SUCCESSFUL\n\n");

	return 0;
}