#include "assert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

//test smithy
int main (int argc, char** argv) {
	struct gameState G;
	int result, card, choice1, choice2, choice3, handPos, bonus, rando = 0;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
	       sea_hag, tribute, smithy};
	rando = rand() % 10;
	result = initializeGame(2, k, rando, &G);
	assert(result == 0);
	printf ("Card Test 2:\n");
	
	//set variables to values for test
	card = 4;
	choice1 = 0;
	choice2 = 0;
	choice3 = 0;
	handPos = 4;
	bonus = 0;
	
	//test invalid input
	result = smithyFunc(-1, &G, 4);
	assert(result == 0);
	
	//test valid input
	result = smithyFunc(1, &G, 4);
	assert(result == 0);
	
	printf("The test passed\n");
	return 0;
}