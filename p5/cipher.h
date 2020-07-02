/**
 */

#ifndef _CIPHER_H_
#define _CIPHER_H_

/** Number of bits in a byte.  */
#define BBITS 8

/** Maximum number of bits in a code. */
#define CIPHER_MAX 24

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

#endif
