/**
  This file implements functionality to store and manage a buffer
  which contains the binary representation for a file.  Ways in which you
  can manage the buffer are by setting bits, appending bits, getting bits,
  loading a buffer from a file, saving a buffer to a file, and getting the
  total number of bits held by the buffer.
  @file filebuffer.c
  @author John Widdifield (jfwiddif)
*/
#include "filebuffer.h"

FileBuffer *makeFileBuffer()
{
  FileBuffer *fb = (FileBuffer *)malloc(sizeof(FileBuffer));
  fb->cap = INIT_CAP;
  fb->bitCount = 0;
  fb->data = (unsigned char *) malloc( INIT_CAP * BBITS * sizeof(unsigned char));
  return fb;
}

void freeFileBuffer( FileBuffer *buffer )
{
  free(buffer->data);
  free(buffer);
}

int getBitCount( FileBuffer const *buffer )
{
  return buffer->bitCount;
}

bool getBit( FileBuffer const *buffer, int idx )
{
  return buffer->data[idx] == '1';
}

void setBit( FileBuffer const *buffer, int idx, bool value )
{
  if (value) {
    buffer->data[idx] = '1';
  } else {
    buffer->data[idx] = '0';
  }
}

void appendBit( FileBuffer *buffer, bool value )
{
  if ((buffer->bitCount / BBITS) >= buffer->cap) {
    buffer->cap *= 2;
    buffer->data = (unsigned char *) realloc( buffer->data, buffer->cap * BBITS *
                   sizeof(unsigned char));
  }

  if (value) {
    buffer->data[buffer->bitCount] = '1';
  } else {
    buffer->data[buffer->bitCount] = '0';
  }

  buffer->bitCount++;

}

FileBuffer *loadFileBuffer( char const *filename )
{

  FileBuffer *buff = makeFileBuffer();

  FILE *fp = fopen(filename, "rb");

  if ( fp == NULL ) {
    fprintf(stderr, "Invalid input file: %s", filename);
    freeFileBuffer(buff);
    exit(EXIT_FAILURE);
  }
  //begin reading the file byte by byte
  int ch;
  while ((ch = fgetc(fp)) != EOF) {
    /*
    * The code for this process of separating bits is based on dumpbits.c which was included
    * in the starter for project 5
    */

    //should reverse order of bits and return one by one while storing
    for ( int i = BBITS - 1; i >= 0; i-- ) {
      ch & ( 1 << i ) ? appendBit(buff, 1) : appendBit(buff, 0);
    }
  }
  fclose(fp);
  return buff;
}

void saveFileBuffer( FileBuffer *buffer, char const *filename )
{
  FILE *fp = fopen(filename, "wb");
  if ( fp == NULL ) {
    fprintf(stderr, "Invalid output file: %s", filename);
    freeFileBuffer(buffer);
    exit(EXIT_FAILURE);
  }

  while (buffer->bitCount % BBITS != 0) {
    appendBit(buffer, 0);
  }

  //group bits into bytes and then convert to number which reps said byte
  unsigned char byte[1];
  byte[0] = 0;
  int bitCnt = 1;
  for ( int i = 0; i < buffer->bitCount; i++) {
    if (buffer->data[i] == '0') {
      byte[0] *= BIN_DEC_CONV;
    } else {
      byte[0] *= BIN_DEC_CONV;
      byte[0] += 1;
    }
    if (bitCnt % BBITS == 0) {
      fwrite( byte, 1, 1, fp);
      byte[0] = 0;
    }
    bitCnt++;
  }
  fclose(fp);
}
