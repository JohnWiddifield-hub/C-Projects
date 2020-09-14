/**
  This is a header file for the connect 4 board display module.

  @author John Widdifield & NCSU Staff (jfwiddif)
  @file board.h
 */

/**
  Error number to be returned if there is an invalid row or column input
 */
#define INVALID_ROWS_COLS 100

/**
  Error number to be returned if there is an invalid column
 */
#define INVALID_COL 101

/**
 Error number to be returned if the columns are full
 */
#define FULL_COL 102

/**
 Minimum number of rows and columns
 */
#define MIN_ROWS_COLS 4

/**
 Maximum number of rows and columns
 */
#define MAX_ROWS_COLS 10

/**
  This will initialize the game board with spaces
 @param rows rows of the board
 @param cols columns of the board
 @param board gameboard to be added to
 */
void initBoard(int rows, int cols, char board[rows][cols]);

/**
 This adds the color of the disc to the board array in the first available row in the column, col.
 It then returns the index of the row to which the disc was added.
 @param rows rows of the board
 @param cols columns of the board
 @param board gameboard to be added to
 @param color color of the disc to be added
 @param col column you would like to add to
 @return If col is less than 0 or greater than or equal to the number of columns, it returns the
 error code of 101.  If the column, col, is full and the disc cannot be added,
 it returns the error code of 102.
 Otherwise it will return the index of the row to which the disc was added.
 */
int addDisc(int rows, int cols, char board[rows][cols], char color, int col);

/**
  This will print the game board for the user to view
 @param rows rows of the board
 @param cols columns of the board
 @param board gameboard to be added to
 */
void printBoard(int rows, int cols, char board[rows][cols]);
