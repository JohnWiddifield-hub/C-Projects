/**
  This is the header file for check.c which checks the status of the game board for if the
  last disc added to the board resulted in a win or if the board is full.
  @author John Widdifield (jfwiddif) NCSU Staff
  @file check.h
 */

#include <stdbool.h>

/**
  Number of same colored discs in a row column or diagonal needed to win
 */
#define N 4

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
bool checkForWinner(int rows, int cols, char board[rows][cols], char color, int row, int col);

/**
 This function will check if the game board is full
 @param rows rows of the board
 @param cols columns of the board
 @param board gameboard to be checked
 @return false if the board is not full, true if it is full
 */
bool checkIfFull(int rows, int cols, char board[rows][cols]);
