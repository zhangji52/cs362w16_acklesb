#include "assert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

//test village card
int main (int argc, char** argv) {
	struct gameState G;
	int result, card, choice1, choice2, choice3, handPos, bonus, rando = 0;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
	       sea_hag, tribute, smithy};
	rando = rand() % 10;
	result = initializeGame(2, k, rando, &G);
	assert(result == 0);
	printf ("Card Test 4:\n");
	
	//set variables to values for test
	card = 20;
	choice1 = -100;
	choice2 = -1;
	choice3 = -10;
	handPos = 4;
	bonus = 0;
	
	//test invalid input
	result = cardEffect(card, choice1, choice2, choice3, &G, handPos, bonus);
	assert(result == -1);
	
	//set variables to values for test
	card = 20;
	choice1 = 1;
	choice2 = 0;
	choice3 = 3;
	handPos = 4;
	bonus = 0;
	
	//test valid input
	result = cardEffect(card, choice1, choice2, choice3, &G, handPos, bonus);
	assert(result == 0);
	
	printf("The test passed\n");
	return 0;
}