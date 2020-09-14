/*
This is the file which allows select.c to read a file into a 2D array and retrieve
the information from the file line by line through getLine()

@author John Widdifield (jfwiddif)
@file text.c
*/
#include "text.h"
#include <stdio.h>
#include <stdlib.h>

/*
* This is a 2D array which contains all of the contents of the
* file after a call to readFile()
*/
static char text[LINE_MAX][LINELENGTH_MAX];
/*
* This will count the nubmer of lines read in by readFile() and
* will contain the total lines in the file
*/
static int lineCounter = 1;

/*
* This variable is to contain the last line from the file
* retrieved by getLine
*/
static char line[LINELENGTH_MAX];

char const *getLine( int i )
{
  for (int j = 0; j < LINELENGTH_MAX; j++) {
    line[j] = text[i][j];
  }
  return line;
}

int lineCount()
{
  return lineCounter - 1;
}

void readText( char const filename[] )
{
  FILE *fp = fopen( filename, "r" );
  if ( !fp ) {
    fprintf(stderr, "Can't open file: %s\n", filename);
    exit(EXIT_FAILURE);
  }
  int ch;
  int numCharsOnLine = 0;
  while ( (ch = fgetc(fp)) != EOF) {
    if (lineCounter > LINE_MAX) {
      fprintf(stderr, "Too many lines: %s\n", filename);
      exit(EXIT_FAILURE);
    }
    if (ch == '\n') {
      numCharsOnLine = 0;
      lineCounter++;
    } else if (numCharsOnLine >= LINELENGTH_MAX - 1) {
      fprintf(stderr, "Line too long: %s:%d\n", filename, (lineCounter));
      exit(EXIT_FAILURE);
    } else {
      text[lineCounter - 1][numCharsOnLine] = ch;
      numCharsOnLine++;
    }
  }

  fclose(fp);
}
