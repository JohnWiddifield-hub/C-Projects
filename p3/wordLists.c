#include "wordLists.h"

void readWords(FILE *wordListFile, char storage[][21], char fName[]) 
{
  //storage = {};
  char ch = fgetc(wordListFile);
  int word = 0;
  int wordLen = 0;

  while (ch != EOF) {
    if(word >= MAXWORDS) {
      fprintf(stderr, "Too many words");
      exit(EXIT_FAILURE);
    }
    if(ch == '\n') {
      //storage[word][wordLen] = '\0';
      if(!checkValidity((storage[word]))) {
        fprintf(stderr, "Invalid word at %s:%d", fName, (word + 1));
        exit(EXIT_FAILURE);
      } else if(checkDuplicate(storage[word], storage, word)) {
        for(int i = 0; i <= (MAXWORDLEN + 1)/*should be 22*/; i++) {
          storage[word][i] = '\0';
        }
        word--;
      }
      wordLen = 0;
      word++; 
    } else {
      storage[word][wordLen] = tolower(ch);
      wordLen++;
    }
    ch = fgetc(wordListFile);
  }
}

bool checkValidity(char aWord[])
{
  if(strlen(aWord) > MAXWORDLEN) {
    return false;
  }
  return true;
}

bool checkDuplicate (char aWord[], char storage[][(MAXWORDLEN + 1)], int idx)
{
  for(int i = idx - 1; i >= 0; i--) {
    if(strcmp(aWord, storage[i]) == 0) {
      return true;
    }
  }
  return false;
}
