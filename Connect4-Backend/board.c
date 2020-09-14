/**
This is the implementation file for the board component
@author John Widdifield (jfwiddif)
@file board.c
*/
#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
  This will initialize the game board with spaces
 @param rows rows of the board
 @param cols columns of the board
 @param board gameboard to be added to
 */
void initBoard(int rows, int cols, char board[rows][cols])
{
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      board[i][j] = ' ';
    }
  }
}

/**
 This adds the color of the disc to the board array in the first available row in the column, col.
 It then returns the index of the row to which the disc was added.
 @param rows rows of the board
 @param cols columns of the board
 @param board gameboard to be added to
 @param color color of the disc to be added
 @param col column you would like to add to
 @return If col is less than 0 or greater than or equal to the number of columns, it returns the
 error code of 101.  If the column, col, is full and the disc
 cannot be added, it returns the error code of 102.
 Otherwise it will return the index of the row to which the disc was added.
 */
int addDisc(int rows, int cols, char board[rows][cols], char color, int col)
{
  if (col < 0 || col > cols) {
    return INVALID_COL;
  }
  for (int i = rows - 1; i >= 0; i--) {
    if (board[i][col - 1] == ' ') {
      board[i][col - 1] = color;
      return i;
    }
  }
  return FULL_COL;
  
}

/**
  This will print the game board for the user to view
 @param rows rows of the board
 @param cols columns of the board
 @param board gameboard to be added to
 */
void printBoard(int rows, int cols, char board[rows][cols])
{
  printf("\n");
  //print column labels
  for (int i = 0; i < cols; i++) {
    printf("  %d ", (i + 1));
  }
  printf("\n");
  for (int i = 0; i < cols; i++) {
    printf("+---");
  }
  printf("+\n");
  for (int i = 0; i < rows; i++) {
    printf("|");
    for (int j = 0; j < cols; j++) {
      printf(" %c |", board[i][j]);
    }
    printf("\n");
    for (int i = 0; i < cols; i++) {
      printf("+---");
    }
    printf("+\n");
  }
}
