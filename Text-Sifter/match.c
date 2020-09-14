/*
This file allows you to compare strings for specific contents
@author John Widdifield (jfwiddif)
@file match.c
*/

#include "match.h"
#include "text.h"
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
bool inRange( int idx, char const *start, char const *end )
{
  int num1 = atoi(start);
  int num2 = atoi(end);
  if (num1 < 0) {
    num1 = lineCount() + num1 + 1;
  }
  if (num2 < 0) {
    num2 = lineCount() + num2 + 1;
  }

  if ((idx <= num1 && idx >= num2) || (idx >= num1 && idx <= num2)) {
    return true;
  } else {
    return false;
  }
}

bool containsPattern( char const *line, char const *str )
{
  int matchCount = 0;
  for (int i = 0; line[i]; i++) {
    if (strlen(line) - i < strlen(str)) {
      return false;
    }
    if (line[i] == str[0]) {
      matchCount++;
      for (int j = 1; str[j]; j++) {
        if (line[i+j] == str[j]) {
          matchCount++;
        }
      }
      if (matchCount == strlen(str)) {
            return true;
      }
    }
    matchCount = 0;
  }
  return false;
}

bool containsWord( char const *line, char const *word )
{
  if ((word[0] == '\'') || word[strlen(word) - 1] == '\''){
      fprintf(stderr, "Invalid word: %s\n", word);
      exit(EXIT_FAILURE);
  }
  for (int i = 0; word[i]; i++) {
    if ((word[i] < '@' || word[i] > 'Z') && (word[i] < 'a' || word[i] > 'z') && (word[i] != '\'')) {
      fprintf(stderr, "Invalid word: %s\n", word);
      exit(EXIT_FAILURE);
    }
  }
  char tempLine[LINELENGTH_MAX];
  char tempWord[strlen(word) + 1];
  strcpy(tempLine, line);
  strcpy(tempWord, word);
  for (int i = 0; tempLine[i]; i++) {
    tempLine[i] = tolower(tempLine[i]);
  }
  for (int i = 0; tempWord[i]; i++) {
    tempWord[i] = tolower(tempWord[i]);
  }

  int matchCount = 0;
  int indexStart = -1;
  int indexEnd = -1;
  for (int i = 0; tempLine[i]; i++) {
    matchCount = 0;
    if (strlen(tempLine) - i < strlen(tempWord)) {
      return false;
    }
    if (tempLine[i] == tempWord[0]) {
      matchCount++;
      indexStart = i;
      for (int j = 1; tempWord[j]; j++) {
        if (tempLine[i + j] == tempWord[j]) {
          matchCount++;
        }
      }
      if (matchCount == strlen(tempWord)) {
            indexEnd = i + strlen(tempWord) - 1;
        if (tempLine[indexStart - 1] > '`' && tempLine[indexStart - 1] < '{') {
          continue;
        } else if (tempLine[indexEnd + 1] > '`' && tempLine[indexEnd + 1] < '{') {
          continue;
        } else {
          return true;
        }
      }
    }
  }
  return false;
  
}
