/**
  This program can compress a file reducing its overall size through a process
  known as huffman coding/encoding.
  @file deflate.c
  @author John Widdifield (jfwiddif)
*/
#include "filebuffer.h"
#include "cipher.h"
#include <string.h>

/** The number of arguments the program expects */
#define ARGS_EXP 4
/** The index of the code file */
#define CFILE 1
/** The index of the in-file */
#define INFILE 2
/** The index of the out-file */
#define OUTFILE 3

/**
  This is the main function which takes the given file and compresses it down
  using huffman coding.
  @param argc number of arguments provided
  @param argv an array containing arguments in the order of program name,
              code-file, infile, outfile
  @return 0 if the program was successful, and 1 if the program ran into an error
*/
int main(int argc, char *argv[])
{
  //check to make sure that all arguments are provided
  if ( argc != ARGS_EXP ) {
    fprintf(stderr, "usage: deflate <code-file> <infile> <outfile>\n");
    exit(EXIT_FAILURE);
  }
  //load up the cipher file
  loadCipher(argv[CFILE]);

  //create filebuffer to store codes into
  FileBuffer *buffer = makeFileBuffer();
  //separate initial 32 bits for file size
  for ( int i = 0; i < NUM_BITS_BCNT; i++ ) {
    appendBit(buffer, 0);
  }

  FILE *input = fopen(argv[INFILE], "r");

  if ( input == NULL ) {
    perror( argv[INFILE] );
    freeCipher();
    freeFileBuffer(buffer);
    exit(EXIT_FAILURE);
  }

  //begin reading in the input file to convert to cipher
  short ch = fgetc(input);
  char code[CIPHER_MAX + 1] = " ";
  int numBytes = 0;
  while ( ch != EOF ) {
    numBytes++;
    strncpy(code, getCipher(ch), CIPHER_MAX + 1);
    for ( int i = 0; code[ i ]; i++ ) {
      if (code[i] == '1') {
        appendBit(buffer, 1);
      } else if (code[i] == '0') {
        appendBit(buffer, 0);
      }
    }
    ch = fgetc(input);
  }
  fclose(input);
  //redo the originial 32 bits to show file length before compression
  int bitIdx = NUM_BITS_BCNT - 1;
  for (; numBytes > 0; numBytes = numBytes >> 1) {
    if ( numBytes & 1 ) {
      setBit(buffer, bitIdx, 1);
      bitIdx--;
    } else {
      setBit(buffer, bitIdx, 0);
      bitIdx--;
    }
  }
  //free all memory
  saveFileBuffer(buffer, argv[OUTFILE]);
  freeCipher();
  freeFileBuffer(buffer);
  return EXIT_SUCCESS;
}
