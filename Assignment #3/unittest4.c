#include "assert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

//shuffle
int main(int argc, char ** argv){
	struct gameState G;
	int result, rando = 0;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy};
	rando = rand() % 10;
	result = initializeGame(2, k, rando, &G);
	assert(result == 0);
	printf("Unittest 4:\n");
	
	//test a bad value for the deck size
	G.deckCount[1] = -10;
	result = shuffle(1, &G);
	assert(result == -1);
	
	//test valid values
	G.deckCount[1] = 3;
	result = shuffle(1, &G);
	assert (result == 0);
		
	printf("The tests passed\n");
	return 0;
}
	