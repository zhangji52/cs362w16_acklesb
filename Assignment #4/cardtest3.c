#include "assert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

//test village card
int main (int argc, char** argv) {
	struct gameState G;
	int result, rando = 0;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
	       sea_hag, tribute, smithy};
	rando = rand() % 10;
	result = initializeGame(2, k, rando, &G);
	assert(result == 0);
	printf ("Card Test 3:\n");
	
	//test invalid input
	result = villageFunc(-1, &G, 4);
	assert(result == 0);
	
	//test valid input
	result = villageFunc(1, &G, 4);
	assert(result == 0);
	
	printf("The test passed\n");
	return 0;
}