/**
  This checks the status of the game board for if the
  last disc added to the board resulted in a win or if the board is full.
  @author John Widdifield (jfwiddif)
  @file check.c
 */
#include "check.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
  This funtion is part of the check component. It returns true if the disc of the
 given color and located in the given row and col, is one of the 4 discs in a row, column,
 or diagonal that have the same color, false, otherwise. it should be called each time a
 disc has been added to the board.
 @param rows rows of the board
 @param cols columns of the board
 @param board gameboard to be checked
 @param color of disc to check for
 @param row which was added at
 @param column which was added at
 @return true if there is a winner, false otherwise
 */
bool checkForWinner(int rows, int cols, char board[rows][cols], char color, int row, int col)
{
  int matchCounter = 0;
  //check vertical
  for (int i = rows - 1; i >= 0; i--) {
    if (board[i][col - 1] == color){
      matchCounter++;
    }
  }
  if (matchCounter == N) {
    return true;
  }
  
  //check horizontal
  matchCounter = 0;
  
  for (int i = 0; i < cols; i++) {
    if (board[row][i] == color) {
      matchCounter++;
    } else {
      matchCounter = 0;
    }
    if (matchCounter == N) {
      return true;
    }
  }
  
  //check the diagonal
  matchCounter = 0;
  int highDiagRow = row;
  int lowDiagCol = col - 1;
  //find lower left diagonal bounds
  while (highDiagRow < rows - 1 && lowDiagCol >= 0) {
    highDiagRow++;
    lowDiagCol--;
  }
  //find upper right diagonal bounds
  int lowDiagRow = row;
  int highDiagCol = col - 1;
  while (highDiagCol < cols - 1 && lowDiagRow >= 0) {
    lowDiagRow--;
    highDiagCol++;
  }
  //search the entire bot left to top right diagonal
  int i, j;
  for (i = highDiagRow, j = lowDiagCol; i >= lowDiagRow && j <= highDiagCol; i--, j++) {
    if (board[i][j] == color) {
      matchCounter++;
    } else {
      matchCounter = 0;
    }
    
    if (matchCounter == N) {
      return true;
    }
  }
  
  matchCounter = 0;
  highDiagRow = row;
  highDiagCol = col - 1;
  //find lower right diagonal bounds
  while (highDiagRow < rows - 1 && highDiagCol < cols - 1) {
    highDiagRow++;
    highDiagCol++;
  }
  //find upper left diagonal bounds
  lowDiagRow = row;
  lowDiagCol = col - 1;
  while (lowDiagCol > 0 && lowDiagRow > 0) {
    lowDiagCol--;
    lowDiagRow--;
  }
  //search the entire bottom right to top left diagonal
  for (i = highDiagRow, j = highDiagCol; i >= lowDiagRow && j >= lowDiagCol; i--, j--) {
    if (board[i][j] == color) {
      matchCounter++;
    } else {
      matchCounter = 0;
    }
    
    if (matchCounter == N) {
      return true;
    }
  }
  //if no matches are found
  return false;
}

/**
 This function will check if the game board is full
 @param rows rows of the board
 @param cols columns of the board
 @param board gameboard to be checked
 @return false if the board is not full, true if it is full
 */
bool checkIfFull(int rows, int cols, char board[rows][cols])
{
  //test the tops of each column to see if there is a value in it
  for (int i = 0; i < cols; i++) {
    if (board[0][i] == ' ') {
      return false;
    }
  }
  // if there are values at the tops of each column then the board must be full
  return true;
}
