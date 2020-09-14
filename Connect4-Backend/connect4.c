/**
This is the main controller file to be used to run the connect4 program.
@author John Widdifield (jfwiddif)
@file connect4.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "check.h"
#include "board.h"
/**
This is the main controller function.
@return 0 if exit successfully, 100 if the rows and columns input were invalid,
        101 if there was an
        attempt to add to an invalid column, 102 if there was an
        attempt to add to a column that was full
*/
int main()
{
  int rows = 0;
  int cols = 0;
  scanf("%d", &rows);
  scanf("%d", &cols);
  //check for valid input
  if (rows < MIN_ROWS_COLS || rows > MAX_ROWS_COLS) {
    printf("Invalid rows\n");
    return INVALID_ROWS_COLS;
  }
  if (cols < MIN_ROWS_COLS || cols > MAX_ROWS_COLS) {
    printf("Invalid cols\n");
    return INVALID_ROWS_COLS;
  }


  char gameBoard[rows][cols];
  initBoard(rows, cols, gameBoard);
  
  int inputCol = 0;
  int inputCount = 0;
  while (scanf("%d", &inputCol) == 1) {
    //check if board is full
    if (checkIfFull(rows, cols, gameBoard)){
      printBoard(rows, cols, gameBoard);
      printf("\nWinner: Draw\n");
      return 0;
    }
    //determine who's turn it is
    inputCount++;
    char discColor = ' ';
    if (inputCount % 2 == 1){
      discColor = 'R';
    } else {
      discColor = 'Y';
    }
    //Add the game piece to the board
    int addResult = addDisc(rows, cols, gameBoard, discColor, inputCol);
    if (addResult == INVALID_COL) {
      printf("Invalid column\n");
      return addResult;
    } else if (addResult == FULL_COL) {
      printf("Full column\n");
      return addResult;
    }
    //check to see if the add resulted in a victory
    if (checkForWinner(rows, cols, gameBoard, discColor, addResult, inputCol)) {
      printBoard(rows, cols, gameBoard);
      if (discColor == 'Y') {
        printf("\nWinner: Yellow\n");
      } else if (discColor == 'R') {
        printf("\nWinner: Red\n");
      }
      return 0;
    }
  }
  //testing for scanf failure mid reading indicating improper input - will not catch 
  // invalid input that is last in the stream, will continue to run normally
  char extraCharLeft;
  if (scanf("%c", &extraCharLeft) == 1) {
    printf("Invalid column\n");
    return INVALID_COL;
  }
  //If the code has gotten to here, no one has won and the board is not full
  printBoard(rows, cols, gameBoard);
  printf("\nWinner: None\n");
  return 0;
}
