/* Jeffrey Do
 * CS 262, Lab Section 207
 * Project 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 15
#define NUM_GOOSE_SPACES 3
#define NUM_BRIDGE_SPACES 1
#define NUM_MAZE_SPACES 2
#define NUM_SKULL_SPACES 1
#define BOARD_SIZE 24
/* initialize arrays to store the different special spaces */
const int gooseSpaces[NUM_GOOSE_SPACES] = {7, 11, 15};
const int bridgeSpaces[NUM_BRIDGE_SPACES] = {6};
const int mazeSpaces[NUM_MAZE_SPACES] = {13, 20};
const int skullSpaces[NUM_SKULL_SPACES] = {23};
const int board[BOARD_SIZE];

/* load a menu that asks for a user input and store the input as reference*/
void menu(char *c) {
  char inBuf[size];
  printf("\nWelcome to the game of goose, please select an option: ");
  printf("\nPress 'P' or 'p' to play\nPress 'Q' or 'q' to quit\n");
  fgets(inBuf, size, stdin);
  sscanf(inBuf, "%c", c);
  return;
}

/* randomly select numbers 1-6 twice and return the sum of the two numbers */
int roll() {
  int die1 = random() % 6 + 1;
  int die2 = random() % 6 + 1;
  int sum = die1 + die2;
  printf("\n%d and %d for a %d\n", die1, die2, sum);
  return sum; 
}

/* create an array called board of BOARD_SIZE and then look through each array containing indexes for special symbols
 * use sprintf to manipulate each index in board to contain the correct corresponding symbol
 * print the board */
void printBoard(int human, int comp) {
  char board[BOARD_SIZE][size];
  char buffer[size];
  int i, index, spot;

  for(i = 0; i < BOARD_SIZE-1; i++) {
    spot = i + 1;
    sprintf(buffer,"[%d]", spot);
    strcpy(board[i], buffer);
  }
  for(i = 0; i < NUM_GOOSE_SPACES; i++) {
    index = gooseSpaces[i]-1;
    spot = gooseSpaces[i];
    sprintf(buffer,"+[%d]", spot);
    strcpy(board[index], buffer);
  }
  for(i = 0; i < NUM_BRIDGE_SPACES; i++) {
    index = bridgeSpaces[i]-1;
    spot = bridgeSpaces[i];
    sprintf(buffer,"*[%d]", spot);
    strcpy(board[index], buffer);
  }
  for(i = 0; i < NUM_MAZE_SPACES; i++) {
    index = mazeSpaces[i]-1;
    spot = mazeSpaces[i];
    sprintf(buffer,"-[%d]", spot);
    strcpy(board[index], buffer);
  }
  for(i = 0; i < NUM_SKULL_SPACES; i++) {
    index = skullSpaces[i]-1;
    spot = skullSpaces[i];
    sprintf(buffer,"![%d]", spot);
    strcpy(board[index], buffer);
  }
  spot = BOARD_SIZE;
  sprintf(buffer,"<%d>", spot);
  strcpy(board[BOARD_SIZE-1], buffer);
  if(human == comp) strcpy(board[human], "[$%]");
  else {
    strcpy(board[human], "[$]");
    strcpy(board[comp], "[%]");
    if(human == BOARD_SIZE-1) strcpy(board[BOARD_SIZE-1], "<$>");
    if(comp == BOARD_SIZE-1) strcpy(board[BOARD_SIZE-1], "<%>");
  }  
  printf("\n\n===============================================================\n");
  for(i = 0; i < BOARD_SIZE; i++) {
    if(i == BOARD_SIZE/2) printf("\n");
    printf("%s ", board[i]);
  }
  printf("\n===============================================================\n");
  return;
}

/* function to decide who goes first
 * have user press enter to call roll() function to randomly cast the dice then
 * have user roll for computer as well. reroll if both are the same
 * check who has the higher number. if it is human, return 1, otherwise return 0 */
int start() {
  char inBuf[5];
  int human = 0, comp = 0;
  char humanIn = 0, compIn = 0;
  while(human == comp) {
    printf("\nHUMAN PLAYER, Press <enter> to roll the dice  ");  
    fgets(inBuf, size, stdin);
    sscanf(inBuf, "%c", &humanIn);  
    switch(humanIn) {
      case 10: 
        human = roll();
        break;
        default:
        printf("\nPRESS ENTER KEY ");
    }
  
    printf("\nCOMPUTER PLAYER, Press <enter> to roll the dice  ");
    fgets(inBuf, size, stdin);
    sscanf(inBuf, "%c", &compIn);
    switch(compIn) {
      case 10:
        comp = roll();
        break;
      default:
        printf("\nPRESS ENTER KEY ");
    }
    if(human == comp) printf("\nYOU BOTH ROLLED THE SAME VALUE. REROLL\n");
  }

  if(human > comp) {
    printf("\nHUMAN PLAYER goes first");
    return 1;  
  }
  else {
    printf("\nCOMPUTER PLAYER goes first");
    return 2;
  }
}

/* uses parameters "player" and "rollNum" to decide where to move the players
 * looks through each element of each of the arrays containing special spaces and moves the player
 * according to the special case if the indexes match 
 * if the roll is higher than the player's distance remaining to the end, move up until you reach the
 * end then move back (roll - distance to end) spaces */
int move(int player, int rollNum) {
  int i, startPos = player, distToEnd = BOARD_SIZE - player, moveBack = -1 * (rollNum - distToEnd);
  if(rollNum > distToEnd) {
    player += distToEnd;
    player += moveBack;
  }
  else player += rollNum;
  printf("\ngo to space %d", player);
  for(i = 0; i < NUM_GOOSE_SPACES; i++) {
    if(player == gooseSpaces[i]) {
      if(rollNum > distToEnd) {
        player += distToEnd;
        player += moveBack;
      }
      else player += rollNum;
      printf(", GOOSE! go to space %d", player);
    }
  }
  for(i = 0; i < NUM_BRIDGE_SPACES; i++) {
    if(player == bridgeSpaces[i]) {
      player = 12;
      printf(", BRIDGE! go to space %d", player);
      break;
    }
  }
  for(i = 0; i < NUM_MAZE_SPACES; i++) {
    if(player == mazeSpaces[i]) {
      player = startPos;
      printf(", MAZE! return to space %d", player);
      break;
    }
  }
  for(i = 0; i < NUM_SKULL_SPACES; i++) {
    if(player == skullSpaces[i]) {
      player = 1;
      printf(", SKULL! return to the beginning");
      break;
    }
  }
  return player;
}

/* calls start() and stores the int value in startRoll.
 * while neither player has reached the end, continue to alternate rolls for each player.
 * human rolls first if startRoll = 1, otherwise computer rolls first.
 * print the board after each roll finishes.
 * if one player reaches the end, print GAME OVER and the winner.
 * finally, ask the user to press enter to return to the menu.
 * */
void play() {
 
  char inBuf[size], c;
  int startRoll, rollNum, humanPos = 1, compPos = 1;  
  startRoll = start();
  printBoard(humanPos-1, compPos-1);
  while(humanPos != BOARD_SIZE && compPos != BOARD_SIZE) {
    if(startRoll == 1) {
      printf("\nHUMAN PLAYER'S TURN, [%d]... Press <enter> to roll the dice ", humanPos);
      fgets(inBuf, size, stdin);
      sscanf(inBuf, "%c", &c);
      switch(c){
        case 10:
          rollNum = roll();
          humanPos = move(humanPos, rollNum);
          break;
        default:
          printf("\nPRESS ENTER ");
      }
      printBoard(humanPos-1, compPos-1);
      startRoll++;
    }
    else {
      printf("\nCOMPUTER PLAYER'S TURN, [%d]... Press <enter> to roll the dice ", compPos);
      fgets(inBuf, size, stdin);
      sscanf(inBuf, "%c", &c);
      switch(c) {
        case 10:
          rollNum = roll();
          compPos = move(compPos, rollNum);
          break;
        default:
          printf("\nPRESS ENTER ");
      }
      printBoard(humanPos-1, compPos-1);
      startRoll--;
    }
  }
  if(startRoll == 1) printf("\nGAME OVER! Computer Won!");
  else printf("\nGAME OVER! Human Won!");
  printf("\nPress <ENTER> to return to main menu ");
  fgets(inBuf, size, stdin);
  sscanf(inBuf, "%c", &c);
  return;
}

/* asks the user to enter a number to generate a seed for the rolls.
 * loads the menu and either quits or plays the game depending on the user input.
 * */
int main() {

  char inBuf[size], c;
  int randNum, playGame = 0;
  printf("\nEnter a seed for the random number generator: ");
  fgets(inBuf, size, stdin);
  sscanf(inBuf, "%d", &randNum);
  srandom(randNum);
  while(playGame != 1) {
    menu(&c);
    switch(c) {
      case 'q':
      case 'Q':
        playGame = 1;
        break;
      case 'p':
      case 'P':
        play();
        break;
      default:
        printf("\nPlease select a valid option");
    }
  }
  return 0;
}

