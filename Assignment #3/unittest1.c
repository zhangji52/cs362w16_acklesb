#include "assert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

//is game over 
//needed: GameState -> supply count

int main(int argc, char ** argv){
	struct gameState G;
	int result, rando = 0;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy};
	rando = rand() % 10;
	result = initializeGame(2, k, rando, &G);
	assert(result == 0);
	printf("Unittest 1:\n");
	
	for(int i = 25; i >= 0; i--){
		G.supplyCount[i] = i;
		result = isGameOver(&G);
	}
	printf("The test passed.\n");
	return 0;
}
