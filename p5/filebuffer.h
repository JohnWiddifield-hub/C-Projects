/**
 */

#ifndef _FILEBUFFER_H_
#define _FILEBUFFER_H_

#include <stdbool.h>

/** Representation of a resizable array of bytes, with functions to
    make it easy to access individual bits. */
typedef struct {
  /** Resizable array of bytes stored in this buffer. */
  unsigned char *data;

  /** Number of bits currently stored in the data array (may not
      always be a multiple of 8). */
  int bitCount;

  /** Capacity of the data array, measured in bytes. */
  int cap;
} FileBuffer;

FileBuffer *makeFileBuffer();

void freeFileBuffer( FileBuffer *buffer );

int getBitCount( FileBuffer const *buffer );

bool getBit( FileBuffer const *buffer, int idx );

void setBit( FileBuffer const *buffer, int idx, bool value );

void appendBit( FileBuffer *buffer, bool value );

FileBuffer *loadFileBuffer( char const *filename );

void saveFileBuffer( FileBuffer *buffer, char const *filename );
#endif
