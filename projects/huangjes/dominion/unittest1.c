/**************************************************************************************************
** Name: Jessica Huang
** Course: CS362_400_SP17
** Description: Unit test for isGameOver function in dominion.c. 
***************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


// Compares the value returned from the gamestate to a boolean of whether the game should be over or not
void assertTrue(struct gameState G, int shouldPass, char desc[])
{
	// If the game ends and it should have ended, pass
	if (isGameOver(&G) && shouldPass == 1)
		printf("PASS: Game Over: %s", desc);
	// If the game ends and it should not have ended, fail
	else if (isGameOver(&G) && shouldPass == 0)
		printf("FAIL: Game Over: %s", desc);
	// If the game does not end and it should have ended, fail
	else if (!isGameOver(&G) && shouldPass == 1)
		printf("FAIL: Game Continues: %s", desc);
	// If the game did not end and it should not have ended, pass
	else
		printf("PASS: Game Continues: %s", desc);
}

int main() 
{
	printf(" UNIT TEST FOR isGameOver FUNCTION\n\n");
	struct gameState G;

	int seed = 1000;
	int numPlayers = 2;
	int i;
	int k[10] = { adventurer, embargo, village, minion, mine, 
			cutpurse, sea_hag, tribute, smithy, council_room };

	
	// Testing game state with different number of province cards
	initializeGame(numPlayers, k, seed, &G);

	// When game is initialized, provinces are greater than 0.
	assertTrue(G, 0, "Province greater than 0.\n");

	// Set number of province cards to 0.
	G.supplyCount[province] = 0;
	assertTrue(G, 1, "Province equal to 0.\n");

	// Set the supply piles for all cards to be greater than 0
	for (i = 0; i < 25; i++)
	{
		G.supplyCount[i] = 5;
	}
	assertTrue(G, 0, "Three supply piles not at 0.\n");

	// Set 1 supply pile to be 0
	for (i = 0; i < 25; i++)
	{
		G.supplyCount[i] = 0;
		// index 3 is province. Game should end
		if (i == 3) 
		{
			assertTrue(G, 1, "Province equal to 0.\n");
		}
		else
		{
			assertTrue(G, 0, "1 supply pile is 0. Index of pile: ");
			printf("%d\n", i);
		}
		G.supplyCount[i] = 5;
	}

	// Set 2 supply piles to be 0
	for (i = 1; i <= 25; i++)
	{
		// Avoid setting provinces to zero because that is automatic game over
		if (i != 3 && i != 4)
		{
			G.supplyCount[i] = 0;
			G.supplyCount[i - 1] = 0;
			assertTrue(G, 0, "2 Supply piles are 0. Index of piles: ");
			printf("%d & %d\n", i - 1, i);
			G.supplyCount[i] = 5;
			G.supplyCount[i - 1] = 5;
		}
	}

	// Set 3 supply piles to be 0. This should cause game over
	for (i = 2; i <= 25; i++)
	{
		// Avoid setting provinces to zero because that is automatic game over
		if (i != 3 && i != 4 && i != 5)
		{
			G.supplyCount[i] = 0;
			G.supplyCount[i - 1] = 0;
			G.supplyCount[i - 2] = 0;
			assertTrue(G, 1, "3 Supply piles are 0. Index of piles: ");
			printf("%d & %d & %d\n", i - 2, i - 1, i);
			G.supplyCount[i] = 5;
			G.supplyCount[i - 1] = 5;
			G.supplyCount[i - 2] = 5;
		}
	}

	// Set 4 supply piles to be 0. The game should never reach this point
	for (i = 3; i <= 25; i++)
	{
		if (i != 3 && i != 4 && i != 5 && i != 6)
		{
			G.supplyCount[i] = 0;
			G.supplyCount[i - 1] = 0;
			G.supplyCount[i - 2] = 0;
			G.supplyCount[i - 3] = 0;
			assertTrue(G, 1, "4 Supply piles are 0. Index of piles: ");
			printf("%d & %d & %d & %d\n", i - 3, i - 2, i - 1, i);
			G.supplyCount[i] = 5;
			G.supplyCount[i - 1] = 5;
			G.supplyCount[i - 2] = 5;
			G.supplyCount[i - 3] = 5;
		}
	}

	printf("\n TEST SUCCESSFULLY COMPLETED\n");

	return 0;
}