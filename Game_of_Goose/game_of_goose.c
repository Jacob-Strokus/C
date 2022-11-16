#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>


#define NUM_GOOSE_SPACES 3
#define NUM_BRIDGE_SPACES 1
#define NUM_MAZE_SPACES 2
#define NUM_SKULL_SPACES 1


const int gooseSpaces[NUM_GOOSE_SPACES] = {7, 11, 15};
const int bridgeSpaces[NUM_BRIDGE_SPACES] = {6};
const int mazeSpaces[NUM_MAZE_SPACES] = {13, 20};
const int skullSpaces[NUM_SKULL_SPACES] = {23};

/* Global variable for size of game board. */
char board[24];


/*
 * Fuction to roll dice given a non-negative integer as the seed.
 */
int roll_Dice(void){
  
  int die_roll_1;
  int die_roll_2;
  int sum = 0;
 
  die_roll_1 = (rand() % 6) + 1;
  die_roll_2 = (rand() % 6) + 1;
  sum = die_roll_1 + die_roll_2;
  
  printf("%d and %d for a %d\n", die_roll_1, die_roll_2, sum);

  return sum;

} 

/*
 * Function to print the board to the console.
 *
 * @param playerPos1 First player's position.
 * @param playerPos2 Second player's position.
 */
void print_Board(int playerPos1, int playerPos2) {

  int i;

  for (i = 1; i <= sizeof(board); i++) {

    if ( i == 13 ) 
      printf("\n");

    if ( i == playerPos1 && i == playerPos2 ) {
      printf(" [$%%] ");
    }
    else if ( i == playerPos1 ) {
      printf(" [$] ");
    }
    else if ( i == playerPos2 ) {
      printf(" [%%] ");
    }
    else if ( i == gooseSpaces[0] || i == gooseSpaces[1] || i == gooseSpaces[2] ) {
     printf(" +[%d] ", i);
    } 
    else if ( i == bridgeSpaces[0] ) {
      printf(" *[%d] ", i);
    }
    else if ( i == mazeSpaces[0] || i == mazeSpaces[1] ) {
      printf(" -[%d] ", i);
    }
    else if ( i == skullSpaces[0] ) {
      printf(" ![%d] ", i);
    }
    else if ( i == sizeof(board) ) {
      printf(" <%d> ", i);
    }
    else {
      printf(" [%d] ", i);
    }
 
  }

  printf("\n\n");

} /* end print_Board */


/*
 * Function to play the game of goose.
 */
void playGame(void) {

  char c;
  int hSum = 0;
  int cSum = 0;
  int player_pos = 1;
  int computer_pos = 1;
  int total = 0; 
  bool playerOne_turn = false;

  while(1) {

    printf("\nHUMAN PLAYER, Press <enter> to roll the dice\n");
    c = fgetc(stdin);

    if ( c == 0x0A ) {
      break;

    } 
    else {

      printf("invalid entry.\n");
    
    }

    c = getchar();

  } /* end while loop */ 

  hSum = roll_Dice();      

  while(1) {

    printf("\nCOMPUTER PLAYER, Press <enter> to roll the dice\n");
    c = fgetc(stdin);

    if ( c == 0x0A ) {
      break;

    }
    else {

      printf("invalid entry.\n");

    }

    c = getchar();

  } /* end while */

  cSum = roll_Dice();

  while ( hSum == cSum ) {

    printf("\nTie. Rerolling dice..\n");
    hSum = 0;
    cSum = 0;
    hSum = roll_Dice();
    cSum = roll_Dice();

  } /* end while */ 
  
  if ( hSum > cSum ) {

    printf("HUMAN PLAYER goes first\n");
    playerOne_turn  = true;

  }
  else {

    printf("COMPUTER PLAYER goes first\n");
    
  }

  while (player_pos != sizeof(board) || computer_pos != sizeof(board) ) {

  printf("\n");
  print_Board(player_pos, computer_pos);
  if ( playerOne_turn ) {

    while(1) {

      printf("HUMAN PLAYER'S TURN [%d] ... Press <enter> to roll dice \n", player_pos);
      c = fgetc(stdin);

      if ( c == 0x0A ) {
        break;

      }
      else {

        printf("invalid entry.\n");

      }

      c = getchar();

    } /* end inner while loop */
  

  hSum = 0;
  hSum = roll_Dice();
  total = hSum + player_pos;

  if ( total > sizeof(board) ) {

    int temp = ( player_pos + hSum ) - sizeof(board);
    player_pos = sizeof(board) - temp;
    printf("\ngo to space %d \n", player_pos);
    total = player_pos;

    if ( total == skullSpaces[0] ) {

        player_pos = 1;
        printf("\nyou hit SKULL! return to the beginning\n");
        total = player_pos;

      }

  } 
  else if ( total == gooseSpaces[0] || total == gooseSpaces[1] || total == gooseSpaces[2] ) {

    int original_pos = player_pos;
    int temp = player_pos + hSum;
    player_pos = temp + hSum;
    printf("\ngo to space %d | You hit GOOSE!  go to space %d\n", temp, player_pos);
    total = player_pos;

    if ( total == mazeSpaces[0] || total == mazeSpaces[1] ) {

      player_pos = original_pos;
      printf("you hit MAZE! retum to %d \n", player_pos);
      total = player_pos;
    }

  } 
  else if ( total == bridgeSpaces[0] ) {

    int temp = player_pos + hSum;
    player_pos = temp + bridgeSpaces[0];
    printf("\ngo to space %d | you hit BRIDGE! go to space %d\n", temp, player_pos);
    total = player_pos;

  }
  else if ( total == mazeSpaces[0] || total == mazeSpaces[1] ) {

    int temp = player_pos + hSum;
    printf("\ngo to space %d | you hit MAZE! go back to space %d\n", temp, player_pos);
    total = player_pos;

  }
  else if ( total == skullSpaces[0] ) {

    int temp = player_pos + hSum;
    player_pos = 1;
    printf("\ngo to space %d | you hit SKULL! return to the beginning\n", temp);
    total = player_pos;

  }
  else {

    player_pos += hSum;
    printf("\ngo to space %d \n", player_pos);

  }
  
  playerOne_turn = false;

  } else {

    while(1) {

      printf("COMPUTER PLAYER'S TURN [%d] ... Press <enter> to roll dice \n", computer_pos);
      c = fgetc(stdin);

      if ( c == 0x0A ) {
        break;

      }
      else {

        printf("invalid entry.\n");

      }

      c = getchar();

    } /* end inner while loop */

    cSum = 0;
    cSum = roll_Dice();
    total = 0;
    total = cSum + computer_pos;

    if ( total > sizeof(board) ) {

      int temp = ( computer_pos + cSum ) - sizeof(board);
      computer_pos = sizeof(board) - temp;
      printf("\ngo to space %d \n", computer_pos);
      total = computer_pos;

      if ( total == skullSpaces[0] ) {

        computer_pos = 1;
        printf("\nyou hit SKULL! return to the beginning\n");
        total = computer_pos;

      }

    }
    else if ( total == gooseSpaces[0] || total == gooseSpaces[1] || total == gooseSpaces[2] ) {

      int original_pos = computer_pos;
      int temp = computer_pos + cSum;
      computer_pos = temp + cSum;
      printf("\ngo to space %d | You hit GOOSE!  go to space %d\n", temp, computer_pos);
      total = computer_pos;

      if ( total == mazeSpaces[0] || total == mazeSpaces[1] ) {

        computer_pos = original_pos;
        printf(" you hit MAZE! retum to %d \n", computer_pos);
        total = computer_pos;
      }

    }
    else if ( total == bridgeSpaces[0] ) {

      int temp = computer_pos + cSum;
      computer_pos = temp + bridgeSpaces[0];
      printf("\ngo to space %d | you hit BRIDGE! go to space %d\n", temp, computer_pos);
      total = computer_pos;

    }
    else if ( total == mazeSpaces[0] || total == mazeSpaces[1] ) {

      int temp = computer_pos + cSum;
      printf("\ngo to space %d | you hit MAZE! go back to space %d\n", temp, computer_pos);
      total = computer_pos;

    }
    else if ( total == skullSpaces[0] ) {

      int temp = computer_pos + cSum;
      computer_pos = 1;
      printf("\ngo to space %d | you hit SKULL! return to the beginning\n", temp);
      total = computer_pos;

    }
    else {

      computer_pos += cSum;
      printf("\ngo to space %d \n", computer_pos);

    }

    
    playerOne_turn = true;

  } /* end else */

  if ( player_pos == sizeof(board) ) {
    printf("\nGAME OVER! PLAYER WON!\n");
    break;
  }  else if ( computer_pos == sizeof(board) ) {
    printf("\nGAME OVER! COMPUTER WON!\n");
    break;
  }

  } /* end  outer while */


  printf("\n");

 /* capture enter key press */
  while(1) {

      printf("Press <enter> to return to the main menu \n");
      c = fgetc(stdin);

      if ( c == 0x0A ) {
        break;

      }
      else {

        printf("invalid entry.\n");

      }

      c = getchar();

    } /* end capture enter key */ 



} /* end playGame */


/*
 * Controls the flow of the program.
 */
int main(){

  char userInput[64];
  char userSeed[64];
  int seed;
  char choice;
  bool play = true;

  printf("Enter a seed for the random number generator: ");
  fgets(userSeed, 64, stdin);
  sscanf(userSeed, "%d", &seed);  
 
  /* randomize */
  srand(seed);

  while (play) {

    printf("\nWelcome to the game of goose, please select an option:\n\nPress 'P' or 'p' to play\nPress 'Q' or 'q' to quit\n\n");
    fgets(userInput, 64, stdin);

    if ( sscanf(userInput, "%s", &choice) != 1 ) {
      printf("Invalid selection. Please try again.\n");
      continue;
    }
    else {
     
      switch(choice) {
      
        case 'P' :
        case 'p' :
         playGame();
         break;
 
        case 'Q' :
        case 'q' :
          printf("\nYou selected quit. Thank you for playing the game of Goose!\n");
          play = false;
          break;

      } /* end switch */

    }

  } /* end while */
  return 0;

}
