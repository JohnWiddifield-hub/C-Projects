/*
This is the main controller program which will allow
the user to input a file and retrieve specific lines
based on their content from the file to stdout

@author John Widdifield (jfwiddif)
@file select.c

*/
#include "match.h"
#include "text.h"
#include <stdbool.h>
#include <string.h>
#include <limits.h>

//This is for use when incremeting an index for a pointer by two
#define DOUBLE_INDEXER 2

/*
This is for use with qsort it tells the function how to sort integers.
@param aptr the pointer to the int to compare against
@param bptr the pointer to the int to compare
@return -1 if aptr is < bptr, 0 if they are the same, and 1 if aptr > bptr
*/
int intComp( const void *aptr, const void *bptr )
{
  int const *a = aptr;
  int const *b = bptr;
  if ( *a < *b )
    return -1;
  if ( *a > *b )
    return 1;
  return 0;
}

/*
This is the main method which controls the entire program
@param argc the number of arguments commanded
@param argv an array of pointers to strings which contain the specified arguments
@return 0 if exit was successful, 1 if not
*/
int main( int argc, char *argv[] )
{
  if (argc <= 1) {
    fail:
    fprintf(stderr, "usage: select ( [-lines <start> <end>]\n                [+lines ");
    fprintf(stderr, "<start> <end>]\n   ");
    fprintf(stderr, "             [-pat <string>]\n                [+pat <string>]\n        ");
    fprintf(stderr, "        [-word <string>]\n                [+word <string>] )* <text-file>\n");
    exit(EXIT_FAILURE);
  }

  readText( argv[argc - 1] );
  int linesToPrint[LINE_MAX] = {0};
  int linesToNotPrint[LINE_MAX] = {0};
  int countAdd = 0;
  int countRemove = 0;

  for (int i = 1; i < argc - 1; i++) {
    if (strcmp( argv[i], "-lines") == 0) {
      int num1 = atoi(argv[i + 1]);
      if (num1 == 0) {
        fprintf(stderr, "Invalid line number: %s\n", argv[i + 1]);
        exit(EXIT_FAILURE);
      }
      int num2 = atoi(argv[i + DOUBLE_INDEXER]);
      if (num2 == 0) {
        fprintf(stderr, "Invalid line number: %s\n", argv[i + DOUBLE_INDEXER]);
        exit(EXIT_FAILURE);
      }
      
      for (int k = 1; k <= lineCount(); k++) {
        if (inRange(k, argv[i + 1], argv[i + DOUBLE_INDEXER])) {
          int failCount = 0;
          for (int j = 0; j <= lineCount(); j++) {
            if (linesToNotPrint[j] == k) {
              failCount++;
              break;
            }
          }
          if (failCount == 0) {
            linesToNotPrint[countRemove] = k;
            countRemove++;
          }
          for (int j = 0; j <= lineCount(); j++) {
            if (linesToPrint[j] == k) {
              linesToPrint[j] = -1;
            }
          }
        }
      }
      
      i = i + DOUBLE_INDEXER;
    } else if (strcmp( argv[i], "+lines") == 0) {
      int num1 = atoi(argv[i + 1]);
      if (num1 == 0) {
        fprintf(stderr, "Invalid line number: %s\n", argv[i + 1]);
        exit(EXIT_FAILURE);
      }
      int num2 = atoi(argv[i + DOUBLE_INDEXER]);
      if (num2 == 0) {
        fprintf(stderr, "Invalid line number: %s\n", argv[i + DOUBLE_INDEXER]);
        exit(EXIT_FAILURE);
      }

      for (int k = 1; k <= lineCount(); k++) {
        if (inRange(k, argv[i + 1], argv[i + DOUBLE_INDEXER])) {
          int failCount = 0;
          for (int j = 0; j <= lineCount(); j++) {
            if (linesToPrint[j] == k) {
              failCount++;
              break;
            }
          }
          if (failCount == 0) {
            linesToPrint[countAdd] = k;
            countAdd++;
          }
          for (int j = 0; j <= lineCount(); j++) {
            if (linesToNotPrint[j] == k) {
              linesToNotPrint[j] = -1;
            }
          }
        }
      }

      i = i + DOUBLE_INDEXER;

    } else if (strcmp( argv[i], "-pat") == 0) {
      for (int k = 0; k < lineCount(); k++) {
        if (containsPattern(getLine(k), argv[i + 1])) {
          int failCount = 0;
          for (int j = 0; j <= lineCount(); j++) {
            if (linesToNotPrint[j] == k + 1) {
              failCount++;
              break;
            }
          }
          if (failCount == 0) {
            linesToNotPrint[countRemove] = k + 1;
            countRemove++;
          }
        }
      }
      i++;

    } else if (strcmp( argv[i], "+pat") == 0) {
      for (int k = 0; k < lineCount(); k++) {
        if (containsPattern(getLine(k), argv[i + 1])) {
          int failCount = 0;
          for (int j = 0; j <= lineCount(); j++) {
            if (linesToPrint[j] == k + 1) {
              failCount++;
              break;
            }
          }
          if (failCount == 0) {
            linesToPrint[countAdd] = k + 1;
            countAdd++;
          }
        }
      }
      i++;

    } else if (strcmp( argv[i], "-word") == 0) {
      for (int k = 0; k < lineCount(); k++) {
        if (containsWord(getLine(k), argv[i + 1])) {
          int failCount = 0;
          for (int j = 0; j <= lineCount(); j++) {
            if (linesToNotPrint[j] == k + 1) {
              failCount++;
              break;
            }
          }
          if (failCount == 0) {
            linesToNotPrint[countRemove] = k + 1;
            countRemove++;
          }
        }
      }
      i++;

    } else if (strcmp( argv[i], "+word") == 0) {
      for (int k = 0; k < lineCount(); k++) {
        if (containsWord(getLine(k), argv[i + 1])) {
          int failCount = 0;
          for (int j = 0; j < countAdd; j++) {
            if (linesToPrint[j] == k + 1) {
              failCount++;
              break;
            }
          }
          if (failCount == 0) {
            linesToPrint[countAdd] = k + 1;
            countAdd++;
          }
        }
      }
      i++;
    } else {
      goto fail;
    }
  }
  for (int i = 0; i < countAdd; i++) {
    for (int j = 0; j < countRemove; j++) {
      if (linesToPrint[i] == linesToNotPrint[j]) {
        linesToPrint[i] = -1;
      }
    }
  }
  for (int i = 0; i < LINE_MAX; i++) {
    if (linesToPrint[i] == 0 || linesToPrint[i] == -1) {
      linesToPrint[i] = INT_MAX;
    }
  }
  qsort( linesToPrint, LINE_MAX, sizeof(linesToPrint[0]), intComp );
  int i = 0;
  if (lineCount() == LINE_MAX) {
    while (linesToPrint[i] != INT_MAX) {
      if (linesToPrint[i] != -1) {
        printf("%5d %s\n", linesToPrint[i], getLine(linesToPrint[i] - 1));
      }
      i++;
    }
    
  } else if (lineCount() >= LINE_MAXTENTH && lineCount() < LINE_MAX) {
    while (linesToPrint[i] != INT_MAX) {
      if (linesToPrint[i] != -1) {
        printf("%4d %s\n", linesToPrint[i], getLine(linesToPrint[i] - 1));
      }
      i++;
    }
    
  } else if (lineCount() >= LINE_MAXHUNDREDTH && lineCount() < LINE_MAXTENTH) {
    while (linesToPrint[i] != INT_MAX) {
      if (linesToPrint[i] != -1) {
        printf("%3d %s\n", linesToPrint[i], getLine(linesToPrint[i] - 1));
      }
      i++;
    }
    
  } else if (lineCount() >= LINE_MAXTHOUSANDTH && lineCount() < LINE_MAXHUNDREDTH) {
    while (linesToPrint[i] != INT_MAX) {
      if (linesToPrint[i] != -1) {
        printf("%2d %s\n", linesToPrint[i], getLine(linesToPrint[i] - 1));
      }
      i++;
    }
  } else {
    while (linesToPrint[i] != INT_MAX) {
      if (linesToPrint[i] != -1) {
        printf("%d %s\n", linesToPrint[i], getLine(linesToPrint[i] - 1));
      }
      i++;
    }
  }
  exit(EXIT_SUCCESS);
}
