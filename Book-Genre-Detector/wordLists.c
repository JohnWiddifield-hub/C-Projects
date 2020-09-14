/*
  This offers the functionality to read text files containing one genre specific word
  per line up to 5000 words and store them into an array.
  @file wordLists.c
  @author John Widdifield (jfwiddif)
*/
#include "wordLists.h"

void readWords(FILE *wordListFile, char storage[][21], char fName[])
{
  char ch = fgetc(wordListFile);
  int word = 0;
  int wordLen = 0;

  while (ch != EOF) {
    //check for if the word is over word limit
    if (word >= MAXWORDS) {
      fprintf(stderr, "Too many words");
      fclose(wordListFile);
      exit(EXIT_FAILURE);
    }
    //end of word check for validity and duplicate
    if (ch == '\n') {
      if (!checkValidity((storage[word]))) {
        fprintf(stderr, "Invalid word at %s:%d", fName, (word + 1));
        fclose(wordListFile);
        exit(EXIT_FAILURE);
      } else if (checkDuplicate(storage[word], storage, word)) {
        for (int i = 0; i <= (MAXWORDLEN + 1); i++) {
          storage[word][i] = '\0';
        }
        word--;
      }
      wordLen = 0;
      word++;
    //part of new word add to storage
    } else {
      storage[word][wordLen] = tolower(ch);
      wordLen++;
    }
    ch = fgetc(wordListFile);
  }
  fclose(wordListFile);
}

bool checkValidity(char aWord[])
{
  if (strlen(aWord) > MAXWORDLEN) {
    return false;
  }
  for (int i = 0; aWord[i]; i++) {
    if (!(isalpha(aWord[i])) && aWord[i] != APOSTROPHE) {
      return false;
    }
  }
  return true;
}

bool checkDuplicate (char aWord[], char storage[][(MAXWORDLEN + 1)], int idx)
{
  for (int i = idx - 1; i >= 0; i--) {
    if (strcmp(aWord, storage[i]) == 0) {
      return true;
    }
  }
  return false;
}
