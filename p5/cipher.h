/**
  This file gives access to functionality to load in a codes file containing
  custom bit sequence representations of ascii characters. And to convert characters to
  and from these custom codes.
  @file cipher.h
  @author John Widdifield (jfwiddif)
*/

#ifndef _CIPHER_H_
#define _CIPHER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Number of bits in a byte.  */
#define BBITS 8

/** Maximum number of bits in a code. */
#define CIPHER_MAX 24

/** Total number of ASCII characters */
#define TOTAL_ASCII 255

/** Return value from lookupCipher() indicating that the given
  * string is the prefix of a code (so, it needs more bits
  * to match a code exactly. */
#define CIPHER_PREFIX -1

/** Return value from lookupCipher() indicating that the given
  * string doesn't match (and isn't a prefix of) any code.  This
  * should only happen in case of an error. */
#define CIPHER_INVALID -2

/** Given a string of '0' and '1' characters representing string of bits,
  * report whether this sequence of bits matches the code for any
  * byte.
  * @param bits String containing a sequence of '0' and '1'.
  * @return the byte value for a matching code, or values CODE_PREFIX
  * or CODE_INVALID described above. */
int lookupCipher( char const *bits );

/**
  Given a code file which contains bit sequences for each ascii value (indicated by the
  line number the code is displayed on) which contains 256 codes each on a new line
  with a maximum sequence length of 24 characters this function will save those codes
  to be accessed through getCipher() and lookupCipher()
  @param filename Name of the file you wish to load codes from (must have 256 codes
                  each with a maximum sequence length of 24
*/
void loadCipher( char const *filename );

/**
  This function will free any memory allocated by the cipher
*/
void freeCipher();

/**
  Given a character or byte worth of memory this will fetch an array of characters
  representing the cipher's variable length bit sequence for that character.
  @param byte character you wish to translate to the cipher's bit sequence representation
  @return A string containing the cipher's bit sequence representation of byte
*/
char const *getCipher( unsigned char byte );

#endif
