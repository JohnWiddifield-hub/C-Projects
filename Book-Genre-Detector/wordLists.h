/*
  This is the header for wordLists.c and offers accessability to readWords checkValidity
  and checkDuplicate it also offers constants for maximum number of words
  maximum word length and the ascii apostrophe constant as well as
  libraries for use with strings, chars, booleans, standard IO, and basic library functionality
  @file wordLists.h
  @author John Widdifield (jfwiddif)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/* This constant represents the maximum number of words to be contained in an input file */
#define MAXWORDS 5000
/* This constant represents the maximum number of characters allowed to be in a word */
#define MAXWORDLEN 20
/* This constant is the ascii equivalent for an apostrophe character */
#define APOSTROPHE 39

/*
  This function will read words from a file (one word up to 20 chars per line up to 5000 words)
  and store them in the storage array.  No duplicate words will be recorded and words longer than
  20 chars will terminate the program as well as files with over 5000 words.
  @param wordListFile This is the file stream you wish to read from (containing the list of words)
  @param storage This is the array which will store the words contained in wordListFile
  @param fName This is a string representing the filename for the wordListFile stream
*/
void readWords(FILE *wordListFile, char storage[][21], char fName[]);

/*
  This will check the validity of a word ensuring it is no longer than 20 characters
  as well as checking for non alphabetic or apostrophe characters
  @param aWord String in which you wish to check for validity
  @return true if the word is valid false if the word is invalid
*/
bool checkValidity(char aWord[]);

/*
  This function will check to make sure that a word is not already contained within the
  storage array
  @param aWord This is the word you wish to check to see if it is already contained
  @param storage This is the array you are checking to see if it contains aWord
  @param idx This is the index of last word (highest used row) in the storage array
  @return true if the storage array contains a duplicate of aWord false if it does not
*/
bool checkDuplicate (char aWord[], char storage[][21], int idx);
