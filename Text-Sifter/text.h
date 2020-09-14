/*
*This is the header file for text.c it defines three key functions for use in select.c
*@author John Widdifield (jfwiddif)
*@file text.h
*/

// This is for use with reading from a input file
#include <stdio.h>

//This is for use with standard functions
#include <stdlib.h>

//This is the maximum number of characters allowed to be on a line
#define LINELENGTH_MAX 81

//This is the maximum number of lines allowed to be in a file
#define LINE_MAX 10000

//This is a tenth of the maximum number of lines allowed to be in a file
#define LINE_MAXTENTH 1000

//This is a one hundredth of the maximum number of lines allowed to be in a file
#define LINE_MAXHUNDREDTH 100

//This is a thousandth of the maximum number of lines allowed to be in a file
#define LINE_MAXTHOUSANDTH 10

/*
* This function will get a line from the input file
* @param i index of the line you wish to retrieve
* @return a string representing the contents of the line i
*/
char const *getLine( int i );

/*
*This function will tell you how many lines the input file has
*@return number of lines in the input file as an int
*/
int lineCount();

/*
*This function will read text from a file into a 2D array
*contained within the program
*@param filename this is a string representing the file you
* wish to read's name
*/
void readText( char const filename[] );
