/**
This is the main function, entry point, for the search program.  It will search for a specified
pattern in the given text file and output the lines and matches which are found for that 
regex pattern.
@file search.c
@author John Widdifield (jfwiddif)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pattern.h"
#include "parse.h"

// On the command line, which argument is the pattern.
#define PAT_ARG 1

// On the command line, which argument is the input file.
#define FILE_ARG 2

// You won't need this function in the final version of your program.
// It prints out the input string and all matches of the pattern inside
// it.
/**
This function will report the matches found for the given string
@param pstr string which represents the pattern
@param str string whcih you are seraching for the pattern
@param len length of the str string
@param table match table which contains true values for the matched characters
*/
void reportMatches( char const *pstr, char const *str, int len,
                    bool (*table)[ len + 1 ] )
{
  // Report the pattern and copies of all the matches.
  printf( "Pattern: %s\n", pstr );
  printf( "String:  %s\n", str );

  bool mflag = false;
  for ( int begin = 0; begin <= len; begin++ )
    for ( int end = begin; end <= len; end++ )
      if ( table[ begin ][ end ] ) {
        // Report the matching substring.

        // Skip over to the start of the match.
        printf( "Match:   %*s", begin, "" );

        // Print the matchng string.
        for ( int k = begin; k < end; k++ )
          printf( "%c", str[ k ] );
        printf( "\n" );

        // Remember that we found a match.
        mflag = true;
      }

  if ( !mflag )
    printf( "No matches\n" );

  printf( "\n" );
}

/**
   Entry point for the program, parses command-line arguments, builds
   the pattern and then tests it against lines of input.

   @param argc Number of command-line arguments.
   @param argv List of command-line arguments.
   @return exit status for the program.
*/
int main( int argc, char *argv[] )
{
  // Temporary code to show how the pattern matching mechanism is
  // supposed to work.  You'll need to replace this with code to do
  // what the program is actually supposed to do, get a pattern from
  // the command line, match it against lines from an input file, and
  // report matching lines with occurrences of the matches
  // highlighted.
  { 
    
    // You should write here some code to get the pattern name from the command line argument. You should
    // have some data structure to store the regular expression for each pattern. You need to fetch the
    // regular expression from your data structure for the pattern obtained from command line arguments.
    /* Write Code Here */
    /******************/


    // Parse a simple regular expression.
    char *pstr = "b"; // pstr should actually contain the regular expression for the given pattern
    Pattern *pat = parsePattern( pstr );

    char *str = "abc"; // you should read lines from input files. This is just an example

    int len = strlen( str );
    // Zero-filled array to use as our match table.
    bool (*table)[ len + 1 ]  = calloc( ( len + 1 ) * ( len + 1 ), sizeof( bool ) );
    // Find matches for this pattern.
    pat->match( pat, str, len, table );

    // Print them out.
    reportMatches( pstr, str, len, table );

    free( table );
    pat->destroy( pat );
  }

  // Try a pattern with some concatenation and multiple matches.
  {
    // Parse another regular expression with some concatenation
    char *pstr = "aba";
    Pattern *pat = parsePattern( pstr );

    char *str = "ababababababab";

    int len = strlen( str );
    // Zero-filled array to use as our match table.
    bool (*table)[ len + 1 ]  = calloc( ( len + 1 ) * ( len + 1 ), sizeof( bool ) );
    // Find matches for this pattern.
    pat->match( pat, str, len, table );

    // Print them out.
    reportMatches( pstr, str, len, table );

    free( table );
    pat->destroy( pat );
  }

  return EXIT_SUCCESS;
}
