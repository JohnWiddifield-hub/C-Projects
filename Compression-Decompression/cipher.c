/**
  This is the implementation file for cipher to load in a codes
  file containing custom bit sequence representations of ascii characters. And to convert
  characters to and from these custom codes.
  @file cipher.c
  @author John Widdifield (jfwiddif)
*/
#include "cipher.h"

/** This global array contains all of the cipher code representations
    where the rows index is the unsigned char ascii value and the
    contents of that row are its cipher represetnation*/
static char code[TOTAL_ASCII + 1][CIPHER_MAX + 1] = {};

void loadCipher( char const *filename )
{
  for (int i = 0; i < TOTAL_ASCII + 1; i++ ) {
    for (int j = 0; j < CIPHER_MAX + 1; j++ ) {
      code[i][j] = '\0';
    }
  }
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    perror( filename );
    exit(EXIT_FAILURE);
  }

  int idx = 0;
  int rev = 0;
  while (fscanf(fp, "%[01]\n", code[idx]) == 1) {
    if (idx >= TOTAL_ASCII + 1) {
      fprintf(stderr, "Invalid code file: %s\n", filename);
      fclose(fp);
      exit(EXIT_FAILURE);
    }
    if (strlen(code[idx]) > CIPHER_MAX) {
      fprintf(stderr, "Invalid code file: %s\n", filename);
      fclose(fp);
      exit(EXIT_FAILURE);
    }
    if (idx != 0) {
      rev = idx - 1;
      for (int i = rev; i >= 0; i--) {
        if (strncmp(code[idx], code[i], strlen(code[i])) == 0) {
          fprintf(stderr, "Invalid code file: %s\n", filename);
          fclose(fp);
          exit(EXIT_FAILURE);
        }
      }
    }
    idx++;

  }
  if (idx != TOTAL_ASCII + 1 ) {
    fprintf(stderr, "Invalid code file: %s\n", filename);
    fclose(fp);
    exit(EXIT_FAILURE);
  }
  fclose(fp);
}

void freeCipher()
{
  return;
}

char const *getCipher( unsigned char byte )
{
 return code[byte];
}

int lookupCipher( char const *bits )
{
  for (int i = 0; i < TOTAL_ASCII + 1; i++) {
    if ( strncmp(bits, code[i], strlen(bits)) == 0 ) {
      if ( strlen(bits) == strlen(code[i]) ) {
        return i;
      } else {
        return CIPHER_PREFIX;
      }
    }
  }
  return CIPHER_INVALID;
}
