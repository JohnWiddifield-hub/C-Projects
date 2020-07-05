/**
  This file gives access to functionality to store and manage a buffer
  which contains the binary representation for a file.  Ways in which you
  can manage the buffer are by setting bits, appending bits, getting bits,
  loading a buffer from a file, saving a buffer to a file, and getting the
  total number of bits held by the buffer.
  @file filebuffer.h
  @author John Widdifield (jfwiddif)
*/

#ifndef _FILEBUFFER_H_
#define _FILEBUFFER_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "cipher.h"

/** This is the number of bits which are stored at the beginning of a FileBuffer
    to represent the total number of bytes stored in the buffer */
#define NUM_BITS_BCNT 32

/** initial capacity for FileBuffer data array */
#define INIT_CAP 4

/** Multiplyer for binary to decimal conversions */
#define BIN_DEC_CONV 2

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

/**
  This will instantiate a new FileBuffer struct and allocating memory for the data array
  @return Pointer to a new FileBuffer struct
*/
FileBuffer *makeFileBuffer();

/**
  This will free any memory occupied by the FileBuffer
  @param buffer the FileBuffer struct you wish to free memory of
*/
void freeFileBuffer( FileBuffer *buffer );

/**
  This will get the total number of bits held by the FileBuffer
  @param buffer The FileBuffer you wish to know the total number of bits of
  @return The number of bits held by the FileBuffer
*/
int getBitCount( FileBuffer const *buffer );

/**
  This will get a bit from the given index of the FileBuffer.
  @param buffer The FileBuffer which contains the bit(s) you are trying to retrieve
  @param idx index of the bit you are trying to retrieve
  @return bool 1 (true) if the bit at the given index is a '1', 0 (false) if it is a '0'
*/
bool getBit( FileBuffer const *buffer, int idx );

/**
  This will set a bit at a given index in a FileBuffer to a specified value 0, or 1.
  @param buffer The FileBuffer which contains the bit you are trying to set.
  @param idx The index of the bit you are trying to set.
  @param value The value (0 or 1) you want to set as the bit at the given index of the buffer
*/
void setBit( FileBuffer const *buffer, int idx, bool value );

/**
  This will append a given bit to the end of the FileBuffer.
  @param buffer FileBuffer you wish to append a bit to
  @param value Value of the bit you wish to append true for 1 false for 0
*/
void appendBit( FileBuffer *buffer, bool value );

/**
  This will load a FileBuffer from the given file.  The new FileBuffer will contain
  the binary representation of every character within the file in their respective order
  @param filename Name of the file you wish to load into a FileBuffer
  @return FileBuffer pointer which contains the binary representation of the provided file
*/
FileBuffer *loadFileBuffer( char const *filename );

/**
  This will save a FileBuffer's data to a given file in binary.
  @param buffer FileBuffer you wish to save to a file
  @param filename The file you wish the FileBuffer to be written to in binary
*/
void saveFileBuffer( FileBuffer *buffer, char const *filename );
#endif
