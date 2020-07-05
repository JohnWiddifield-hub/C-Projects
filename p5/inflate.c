/**
  This program offers the functionality to decompress a file which was compressed via the
  deflate program.  In order to retrieve that original file which was compressed you
  must also use the same code file used with the deflate program.
  @file inflate.c
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
  This is the main function which takes the given file and decompresses it
  using the huffman coding technique.
  @param argc number of arguments provided
  @param argv an array containing arguments in the order of program name,
              code-file, infile, outfile
  @return 0 if the program was successful, and 1 if the program ran into an error
*/
int main(int argc, char *argv[])
{
  //check to make sure that all arguments are provided
  if ( argc != ARGS_EXP) {
    fprintf(stderr, "usage: inflate <code-file> <infile> <outfile>\n");
    exit(EXIT_FAILURE);
  }
  //load up the filebuffer and cipher for the file
  loadCipher(argv[CFILE]);
  FileBuffer *buffer = loadFileBuffer(argv[INFILE]);

  //get expected size (in bytes/characters) of the file buffer from first 4 bytes
  int length[1];
  length[0] = 0;
  for ( int i = 0; i < NUM_BITS_BCNT; i++) {
    if (!getBit(buffer, i)) {
      length[0] *= BIN_DEC_CONV;
    } else {
      length[0] *= BIN_DEC_CONV;
      length[0] += 1;
    }
  }
  //now that we have the length we need to find codes in the buffer and output to a file
  FILE *output = fopen(argv[OUTFILE], "w");
  int curBit = NUM_BITS_BCNT;
  int numBytes = 0;
  char code[CIPHER_MAX + 1] = "\0";
    for (int i = 0; i < (CIPHER_MAX + 1) && curBit < getBitCount(buffer) && numBytes !=
        length[0]; i++) {
      if (getBit(buffer, curBit)) {
        strncat(code, "1", sizeof(code) - strlen(code) - 1);
      } else {
        strncat(code, "0", sizeof(code) - strlen(code) - 1);
      }
      curBit++;
      int ch = lookupCipher(code);
      unsigned char ucch;
      switch (ch) {
        case CIPHER_PREFIX:
          continue;
        case CIPHER_INVALID:
          fprintf(stderr, "Invalid input file: %s\n", argv[INFILE]);
          fclose(output);
          freeCipher();
          freeFileBuffer(buffer);
          exit(EXIT_FAILURE);
          break;
        default:
          ucch = (unsigned char) ch;
          fprintf(output, "%c", ucch);
          numBytes++;
          char reset[CIPHER_MAX + 1] = "\0";
          strcpy(code, reset);
          i = -1;
          break;
      }
    }
  if (numBytes != length[0]) {
    fprintf(stderr, "Invalid input file: %s\n", argv[INFILE]);
    fclose(output);
    freeCipher();
    freeFileBuffer(buffer);
    exit(EXIT_FAILURE);
  } else {
    fclose(output);
    freeCipher();
    freeFileBuffer(buffer);
    return EXIT_SUCCESS;
  }
  fclose(output);
}
