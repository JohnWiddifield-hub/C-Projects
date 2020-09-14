/*
*This is the header file for match.c it defines three key functions for use in select.c
*@author John Widdifield (jfwiddif)
*@file match.h
*/

//This is for use with the boolean return values
#include <stdbool.h>

//This is for use with the containsword function for tolower()
#include <ctype.h>

/*
* This function determines if an index is within the given bounds (inclusive)
*@param idx index to check for
*@param start the index to start from
*@param end the index to stop at
*@return true if idx is between start and stop, false if otherwise
*/
bool inRange( int idx, char const *start, char const *end );

/*
* This function determines if a pattern is within the line
*@param line the line to check for the given pattern
*@param str the string pattern to check for
*@return true if the pattern is contained within the line false if it is not
*/
bool containsPattern( char const *line, char const *str );

/*
* This function determines if a word is within the line
*@param line the line to check for the given word
*@param word the word to check for
*@return true if the word is contained within the line false if it is not
*/
bool containsWord( char const *line, char const *word );
