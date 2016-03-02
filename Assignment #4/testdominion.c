#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>

char *cardLookUP(int cardNum);
int getState(int, struct gameState *G);
int initializeGame(int numPlayers, int kingdomCard[10],
     	 int randomSeed, struct gameState *state);

int main(int argc, char **argv){
	struct gameState G;
	int seed = rand() % 1500;
	int numPlayers, rando, plays = 0; //Initialization Variables
	int currentPlayer;
	FILE *fp;
	
	printf("Nothing is printed to the screen see file gameResults.out for results\n");
	//--------------------------------------
	//INITIALIZATION
	//--------------------------------------
	
	fp = fopen("gameResults.out", "w");
	fprintf(fp, "Beginning Testing!\n");
	
	fprintf(fp, "Initializing Game\n");
	int k[10] = {gardens, adventurer, steward, minion, village,
	  	 salvager, sea_hag, embargo, mine, smithy};	
	
	do{
		numPlayers = rand() % 4;
	}while(numPlayers < 2);

	fprintf(fp, "The Number of players is: %d\n", numPlayers);
	fprintf(fp, "Kingdom Cards used are: ");
	for(int i = 0; i < 10; i++){
		fprintf(fp, "%s ", cardLookUP(k[i]));
	}
	fprintf(fp, "\n");

	int result = initializeGame(numPlayers, k, seed, &G);
	assert(result == 0);

	fprintf(fp, "\nPlacing Cards in Hand\n");
	for(int i = 0; i < numPlayers; i++){
		fprintf(fp, "Player %d: ", i+1);
		for(int j = 0; j < numHandCards(&G); j++){
			fprintf(fp, "%s ", cardLookUP(handCard(j, &G)));
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "\n");

	//-------------------------------------------------------
	//The game is set up playing game now
	//-------------------------------------------------------
	
	fprintf(fp, "Finished initialization of game!\n");
	
	while(!isGameOver(&G)){
		plays++;
		currentPlayer = whoseTurn(&G);
		fprintf(fp, "\nThe current player is: %d\n", currentPlayer + 1);
		fprintf(fp, "Current hand: ");
		for(int i = 0; i < numHandCards(&G); i++){
			fprintf(fp, "%s ", cardLookUP(handCard(i, &G)));
		}
		
	//---------------------------------------------------
	//Performing Action
	//---------------------------------------------------
		fprintf(fp, "\nEntering the Action Phase\n");
		
		while(G.numActions > 0){
			int numActionCards = 0;
			int numMoneyCards = 0;
		    int *actionCardIndex = NULL;
			int *moneyIndex = NULL;
			int choice1 = -1;
		    int choice2 = -1;
		    int choice3 = -1;
			
			//Go through all the cards and see if there are any action cards
			for(int i = 0; i < numHandCards(&G); i++){
				int card = handCard(i, &G);
				if(card >= adventurer && card != gardens){
					numActionCards++;
					actionCardIndex = realloc(actionCardIndex, numActionCards * sizeof(int));
					actionCardIndex[numActionCards-1] = i;
				}
				else if(card >= copper && card <= gold){
					numMoneyCards++;
					moneyIndex = realloc(moneyIndex, numMoneyCards * sizeof(int));
					moneyIndex[numMoneyCards-1] = i;
				}
			}
			
			//If the player can't do anything
			if(numActionCards == 0){
				fprintf(fp, "Player %d has no action to play.\n", currentPlayer + 1);
				fprintf(fp, "\nEntering Buying Phase!\n");
				int money = getState(currentPlayer, &G);
				if(money >= 8){
					fprintf(fp, "Bought province\n");
					money = buyCard(province, &G);
				}
				else if(money >= 6){
					fprintf(fp, "Bought gold\n");
					money = buyCard(gold, &G);
				}
				else if(money >= 5){
					fprintf(fp, "Bought duchy\n");
					money = buyCard(duchy, &G);
				}
				else if(money >= 3){
					fprintf(fp, "Bought steward\n");
					money = buyCard(steward, &G);
				}
				else if(money >= 2){
					fprintf(fp, "Bought estate\n");
					money = buyCard(estate, &G);
				}
				
				//-------------------------------------------
				//Finished Buying Phase
				//-------------------------------------------
				
				fprintf(fp, "Ending Turn\n");
				endTurn(&G);
				break;
			}
			
			rando = rand() % numActionCards;
			int pickACard = handCard(actionCardIndex[rando], &G);
			
			if(pickACard == ambassador){
				fprintf(fp, "The card picked was: %s\n", cardLookUP(pickACard));
				choice1 = rand() % numHandCards(&G), choice2 = 1, choice3 = -1;
				playCard(pickACard, choice1, choice2, choice3, &G);
			}
			else if (pickACard == baron){
				fprintf(fp, "The card picked was: %s\n", cardLookUP(pickACard));
				choice1 = 0, choice2 = -1, choice3 = -1;
				playCard(pickACard, choice1, choice2, choice3, &G);
			}
			else if(pickACard == embargo){
				fprintf(fp, "The card picked was: %s\n", cardLookUP(pickACard));
				choice1 = rand() % (curse + 1 - treasure_map) + treasure_map, choice2 = -1, choice3 = -1;
				playCard(pickACard, choice1, choice2, choice3, &G);
			}
			else if(pickACard == feast){
				fprintf(fp, "The card picked was: %s\n", cardLookUP(pickACard));
				choice1 = rand() % (duchy + 1 - treasure_map) + treasure_map, choice2 = -1, choice3 = -1;
				playCard(pickACard, choice1, choice2, choice3, &G);
			}
			else if(pickACard == mine){
				fprintf(fp, "The card picked was: %s\n", cardLookUP(pickACard));
				choice1 = moneyIndex[rand() % numMoneyCards];
				choice2 = copper;
				choice3 = -1;
				playCard(pickACard, choice1, choice2, choice3, &G);
			}
			else if(pickACard == minion){
				fprintf(fp, "The card picked was: %s\n", cardLookUP(pickACard));
				choice1 = (rand() % 1) + 1, choice2 = -1, choice3 = -1;
				playCard(pickACard, choice1, choice2, choice3, &G);
			}
			else if(pickACard == remodel){
				fprintf(fp, "The card picked was: %s\n", cardLookUP(pickACard));
				choice1 = rand() % numHandCards(&G), choice2 = rand() % (estate + 1 - treasure_map) + treasure_map, choice3 = -1;
				playCard(pickACard, choice1, choice2, choice3, &G);
			}
			else if(pickACard == remodel){
				fprintf(fp, "The card picked was: %s\n", cardLookUP(pickACard));
				choice1 = rand() % numHandCards(&G), choice2 = -1, choice3 = -1;
				playCard(pickACard, choice1, choice2, choice3, &G);
			}
			else if(pickACard == steward){
				fprintf(fp, "The card picked was: %s\n", cardLookUP(pickACard));
				choice1 = (rand() % 3) + 1, choice2 = -1, choice3 = -1;
				playCard(pickACard, choice1, choice2, choice3, &G);
			}
			else{
				fprintf(fp, "The card picked was %s\n", cardLookUP(pickACard));
				choice1 = -1, choice2 = -1, choice3 = -1;
				playCard(pickACard, choice1, choice2, choice3, &G);
			}
			
			fprintf(fp, "Finished Action.\nHere is the new Hand: ");
			for(int i = 0; i < numHandCards(&G); i++){
				fprintf(fp, "%s ", cardLookUP(handCard(i, &G)));
			}
			fprintf(fp, "\n");
			free(actionCardIndex);
			
			//------------------------------------------
			//Finished Action Phase, entering buying phase
			//------------------------------------------
			fprintf(fp, "Entering Buying Phase!\n");
			int money = getState(currentPlayer, &G);
			if(money >= 8){
				fprintf(fp, "Bought province\n");
				money = buyCard(province, &G);
			}
			else if(money >= 6){
				fprintf(fp, "Bought gold\n");
				money = buyCard(gold, &G);
			}
			else if(money >= 5){
				fprintf(fp, "Bought duchy\n");
				money = buyCard(duchy, &G);
			}
			else if(money >= 2){
				fprintf(fp, "Bought estate\n");
				money = buyCard(estate, &G);
			}
			
			//-------------------------------------------
			//Finished Buying Phase
			//-------------------------------------------
			
			fprintf(fp, "Ending Turn\n");
			endTurn(&G);
		}
	}
	
	//------------------------------------
	//End of game
	//------------------------------------
	
	fprintf(fp, "Finished Game!\nIt took %d plays to complete the game!", plays/2);
	printf("See file gameResults.out for results.\n");
	fclose(fp);
}

int getState(int currentPlayer, struct gameState *G){
	updateCoins(currentPlayer, G, 0);
   	return G->coins;
}   

char* cardLookUP(int cardNum) {
	switch (cardNum) {
		case curse: return "Curse";
		case estate: return "Estate";
		case duchy: return "Duchy";
		case province: return "Province";
		case copper: return "Copper";
		case silver: return "Silver";
		case gold: return "Gold";
		case gardens: return "Gardens";
		case adventurer: return "Adventurer";
		case council_room: return "Council Room";
		case feast: return "Feast";
		case great_hall: return "Great Hall";
		case mine: return "Mine";
		case remodel: return "Remodel";
		case smithy: return "Smithy";
		case village: return "Village";
		case baron: return "Baron";
		case minion: return "Minion";
		case steward: return "Steward";
		case tribute: return "Tribute";
		case ambassador: return "Ambassador";
		case cutpurse: return "Cutpurse";
		case embargo: return "Embargo";
		case outpost: return "Outpost";
		case salvager: return "Salvager";
		case sea_hag: return "Sea Hag";
		case treasure_map: return "Treasure Map";
		default: return "";
	}
}
