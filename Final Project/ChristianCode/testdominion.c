#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TESTS 5

void runDomGame(){

	  struct gameState state;
      int i, n, numPlayers, seed;
      int flag = 0;

      srand(time(NULL));
      seed = rand();

	  // Check 2-4 players
	  while(flag == 0) {
	     numPlayers = rand() % 5;
	     if (!(numPlayers < 2)){
            flag = 1;
            printf("This game will have %d players!\n\n", numPlayers);
	     }
      }
      int k[10];
      int kCheck[26][2];

      for(i=0;i<27; i++){
        kCheck[i][0] = i;
        kCheck[i][1] = 0;
      }

      for (i=0; i<10; i++) {
          int rando=0;
          flag = 0;
          while (flag == 0) {
            rando = rand() % 27;
            if ((rando > 7) && (kCheck[rando][1] == 0)) {
                k[i] = rando;
                kCheck[rando][1] = 1;
                flag = 1;
            }
          }
      }

      initializeGame(numPlayers, k, seed, &state);	//initialize Gamestate

      printf("Printing INITIAL gamestate information: \n");
          printf("numPlayers: %d\n\n", state.numPlayers);

          printf("ALL Kingdom Cards -- KEY : \n");
          printf("curse - 0\n");
          printf("estate - 1\n");
          printf("duchy - 2\n");
          printf("province - 3\n");

          printf("copper - 4\n");
          printf("silver - 5\n");
          printf("gold - 6\n");

          printf("adventurer - 7\n");
          printf("council_room - 8\n");
          printf("feast - 9\n");
          printf("gardens - 10\n");
          printf("mine - 11\n");
          printf("remodel - 12\n");
          printf("smithy - 13\n");
          printf("village - 14\n");
          printf("baron - 15\n");
          printf("great_hall - 16\n");
          printf("minion - 17\n");
          printf("steward - 18\n");
          printf("tribute - 19\n");
          printf("ambassador - 20\n");
          printf("cutpurse - 21\n");
          printf("embargo - 22\n");
          printf("outpost - 23\n");
          printf("salvager - 24\n");
          printf("sea_hag - 25\n");
          printf("treasure_map - 26\n\n");

      printf("Randomly Selected Kingdom Cards (by ENUM): \n");
      for(i=0; i<10; i++){
        printf("k[%d]: %d\n", i, k[i]);
      }

      // IMPLEMENTATION OF GAME
      while(!isGameOver(&state)){

          for (n=0; n<numPlayers; n++) {
              int handCount = 0, temp = 0, money=0;

              printf("\nPlayer %d's information: \n", state.whoseTurn);
                  printf("whoseTurn: %d\n", state.whoseTurn);
                  printf("deckCount: %d\n", state.deckCount[n]);
                  printf("phase: %d\n", state.phase);
                  printf("numActions: %d\n", state.numActions);
                  printf("numBuys: %d\n", state.numBuys);
                  handCount = numHandCards(&state);
                  printf("numCards in Hand: %d\n", handCount);
                  printf("ENUMs of cards in hand: \n");
                  for (i=0; i<handCount; i++) {
                    temp = handCard(i, &state);
                    printf("%d ", temp);
                  }
                  printf("\n");

              // search for an action
              printf("\nPlayer %d Action Phase (if any): \n", n);
              for (i=0; i<handCount; i++) {
                temp = handCard(i, &state);
                if ( ( temp > 6 ) && ( state.numActions > 0 ) && ( temp != gardens ) ) {
                    playCard(i, 1, 1, 1, &state);
                    printf("Player %d: played card %d.\n", n, temp);
                    state.numActions--;
                }
              } printf("\n");

              // Total money in hand, buy something
              for (i=0; i<handCount; i++) {
                temp = handCard(i, &state);
                if (temp == 4) {
                    playCard(i, -1, -1, -1, &state);
                    money++;
                } else if (temp == 5) {
                    playCard(i, -1, -1, -1, &state);
                    money += 2;
                } else if (temp == 6) {
                    playCard(i, -1, -1, -1, &state);
                    money += 3;
                }
              }
              printf("\nPlayer %d: %d money before buy: \n", n, money);

              // Buy providence first
              if (money >= 8) {
                 printf("Player %d: bought province\n", n);
                 buyCard(province, &state);
               }
               // Buy a card from the table, if able
               for(i=0; i<10; i++){
                    if ((money > (getCost(k[i]))) && (state.supplyCount[k[i]] > 0)) {
                        buyCard(k[i], &state);
                        printf("Player %d: bought %d for %d money\n", n, k[i], getCost(k[i]));
                        money = money - (getCost(k[i]));
                    }
               }

              // Now buy victory or money cards
               if (money >= 6) {
                 printf("Player %d: bought gold\n", n);
                 buyCard(gold, &state);
               }
               else if (money >= 5) {
                 printf("Player %d: bought duchy\n", n);
                 buyCard(duchy, &state);
               }
               else if (money >= 3) {
                 printf("Player %d: bought silver\n", n);
                 buyCard(silver, &state);
               }
               else if (money >= 2) {
                 printf("Player %d: bought estate\n", n);
                 buyCard(estate, &state);
               }
               else if (money <= 1) {
                 printf("Player %d: bought copper\n", n);
                 buyCard(copper, &state);
               }

              // END TURN
              printf("Player %d: end turn\n", n);
          /*    if (isGameOver(&state)) {
                printf("\n\nGAME IS OVER\n\n")
                break;
              } */
              endTurn(&state);
          }
      }

	  printf("\n\n--\n--- The Game is over! ---\n\n");
	  int s;
	  for (s=0; s<numPlayers; s++) {
          printf("Score for Player %d: %d\n", s, scoreFor(s, &state));
	  }
}

int main() {

     int z;
     printf("\n\n---\nStart of testdominion.c -- Testing full implementation of Dominion\n---\n\n");

     for (z=0; z<MAX_TESTS; z++) {
        printf("\nRUNNING TEST %d\n\n", z+1);
        runDomGame();
     }
     printf("\n--- Tests completed ---\n--\n");

	 return 0;
}
