/*
  This file offers the functionality to read words from a book storing any
  relevant words based on the supplied genre storages and giving the
  amount of matches for each genre.
  @file readBook.c
  @author John Widdifield (jfwiddif)
*/
#include "wordLists.h"
#include "readBook.h"

void readBookWords(FILE *book, char bookStorage[][21], char fanStor[][21], char sciStor[][21],
     char advStor[][21], char polStor[][21], char traStor[][21], int *fanCnt, int *sciCnt,
     int *advCnt, int *polCnt, int *traCnt)
{
  char ch = fgetc(book);
  int words = 0;
  int wordLen = 0;
  int totWords = 0;

  while ( ch != EOF ) {
    if (ch >= 'A' && ch <= 'Z') {
      ch = tolower(ch);
    }
    if ((ch >= 'a' && ch <= 'z') || ch == APOSTROPHE) {
      if (wordLen >= MAXWORDLEN) {
        while (isalpha(ch) || ch == APOSTROPHE) {
          ch = fgetc(book);
        }
        while (!isalpha(ch) && ch != APOSTROPHE) {
          ch = fgetc(book);
        }
        for (int i = 0; i <= (MAXWORDLEN + 1); i++) {
          bookStorage[words][i] = '\0';
        }
        wordLen = 0;
      }
      bookStorage[words][wordLen] = ch;
      wordLen++;
      ch = fgetc(book);
    } else {
      bookStorage[words][wordLen] = '\0';
      totWords++;
      //check for matches
      bool match = false;
      for (int i = 0; i < MAXWORDS; i++) {
        if (strcmp(bookStorage[words], fanStor[i]) == 0) {
          match = true;
          *fanCnt += 1;
        }
        if (strcmp(bookStorage[words], sciStor[i]) == 0) {
          match = true;
          *sciCnt += 1;
        }
        if (strcmp(bookStorage[words], advStor[i]) == 0) {
          match = true;
          *advCnt += 1;
        }
        if (strcmp(bookStorage[words], polStor[i]) == 0) {
          match = true;
          *polCnt += 1;
        }
        if (strcmp(bookStorage[words], traStor[i]) == 0) {
          match = true;
          *traCnt += 1;
        }
      }
      //if no matches were found then erase the word from the list
      if (match == false) {
        for (int i = 0; i <= (MAXWORDLEN + 1); i++) {
          bookStorage[words][i] = '\0';
        }
        words--;
      }
      wordLen = 0;
      words++;
      if (totWords >= MAXWORDS) {
        fprintf(stderr, "Too many words");
        fprintf(stdout, "Too many words");
        fclose(book);
        exit(EXIT_FAILURE);
      }
      while (ch != EOF && !isalpha(ch) && ch != APOSTROPHE) {
        ch = fgetc(book);
      }
    }
  }
  fclose(book);
}
