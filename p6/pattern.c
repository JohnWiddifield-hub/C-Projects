/**
This file offers the functionality to maintain a pattern object
@file pattern.c
@author John Widdifield (jfwiddif)
*/

#include "pattern.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
   A simple function that can be used to free the memory for any
   pattern that doesn't allocate any additional memory other than the
   struct used to represent it (e.g., if it doesn't contain any
   sub-patterns).  It's like a default implementation of the destroy
   method.

   @param pat The pattern to free memory for.
*/
static void destroySimplePattern( Pattern *pat )
{
  // If we don't need fields that are specific to the sub-type, we can just
  // free the block of memory where the object is stored.
  free( pat );
}

/**
   Type of pattern used to represent a single, ordinary symbol,
   like 'a' or '5'.
*/
typedef struct {
  // Fields from our superclass.
  void (*match)( Pattern *pat, char const *str, int len, bool (*table)[ len + 1 ] );
  void (*destroy)( Pattern *pat );

  /** Symbol this pattern is supposed to match. */
  char sym;
} LiteralPattern;


// Overridden match() method for a LiteralPattern
static void matchLiteralPattern( Pattern *pat, char const *str, int len,
                                 bool (*table)[ len + 1 ] )
{
  // Cast down to the struct type pat really points to.
  LiteralPattern *this = (LiteralPattern *) pat;

  // Find all occurreces of the symbol we're supposed to match, and
  // mark them in the match table as matching, 1-character substrings.
  for ( int i = 0; i < len; i++ )
    if ( str[ i ] == this->sym )
      table[ i ][ i + 1 ] = true;
}

// Documented in the header.
Pattern *makeLiteralPattern( char sym )
{
  // Make an instance of LiteralPattern, and fill in its state.
  LiteralPattern *this = (LiteralPattern *) malloc( sizeof( LiteralPattern ) );

  this->match = matchLiteralPattern;
  this->destroy = destroySimplePattern;
  this->sym = sym;

  return (Pattern *) this;
}

/**
   Representation for a type of pattern that contains two sub-patterns
   (e.g., concatenation).  This representation could be used by more
   than one type of pattern, as long as it uses a pointer to a
   different match() function.
*/
typedef struct {
  // Fields from our superclass.
  void (*match)( Pattern *pat, char const *str, int len, bool (*table)[ len + 1 ] );
  void (*destroy)( Pattern *pat );

  // Pointers to the two sub-patterns.
  Pattern *p1, *p2;
} BinaryPattern;

// destroy function used for BinaryPattern
static void destroyBinaryPattern( Pattern *pat )
{
  // Cast down to the struct type pat really points to.
  BinaryPattern *this = (BinaryPattern *) pat;

  // Free our two sub-patterns.
  this->p1->destroy( this->p1 );
  this->p2->destroy( this->p2 );
  // Free the struct representing this object.
  free( this );
}

// match function for a BinaryPattern used to handle concatenation.
static void matchConcatenationPattern( Pattern *pat, char const *str, int len,
                                       bool (*table)[ len + 1 ] )
{
  // Cast down to the struct type pat really points to.
  BinaryPattern *this = (BinaryPattern *) pat;

  // Two more tables for matching sub-expressions.
  bool (*tbl1)[ len + 1 ]  = calloc( ( len + 1 ) * ( len + 1 ), sizeof( bool ) );
  bool (*tbl2)[ len + 1 ]  = calloc( ( len + 1 ) * ( len + 1 ), sizeof( bool ) );

  //  Let our two sub-patterns figure out everywhere they match.
  this->p1->match( this->p1, str, len, tbl1 );
  this->p2->match( this->p2, str, len, tbl2 );

  // Then, based on their matches, look for all places where their
  // concatenaton matches.  Check all substrings of the input string.
  for ( int begin = 0; begin <= len; begin++ )
    for ( int end = begin; end <= len; end++ ) {

      // For the [ begin, end ) range, check all places where it could
      // be split into two substrings, the first matching p1 and the second
      // matching p2.
      for ( int k = begin; k <= end; k++ )
        if ( tbl1[ begin ][ k ] && tbl2[ k ][ end ] )
          table[ begin ][ end ] = true;
    }

  free( tbl1 );
  free( tbl2 );
}

Pattern *makeConcatenationPattern( Pattern *p1, Pattern *p2 )
{
  // Make an instance of Binary pattern and fill in its fields.
  BinaryPattern *this = (BinaryPattern *) malloc( sizeof( BinaryPattern ) );
  this->p1 = p1;
  this->p2 = p2;

  this->match = matchConcatenationPattern;
  this->destroy = destroyBinaryPattern;

  return (Pattern *) this;
}
