#include "wordLists.h"
#include "readBook.h"

int main( int argc, char *argv[] ) 
{

  char sciStr[] = "science_words.txt";
  char polStr[] = "political_words.txt";
  char traStr[] = "tragic_words.txt";
  char fanStr[] = "fantasy_words.txt";
  char advStr[] = "adventure_words.txt";

  FILE *sciFile = fopen("science_words.txt", "r");
  FILE *polFile = fopen("political_words.txt", "r");
  FILE *traFile = fopen("tragic_words.txt", "r");
  FILE *fanFile = fopen("fantasy_words.txt", "r");
  FILE *advFile = fopen("adventure_words.txt", "r");

  int sciCnt = 0;
  int polCnt = 0;
  int traCnt = 0;
  int fanCnt = 0;
  int advCnt = 0;

  char sciStor[MAXWORDS][MAXWORDLEN + 1];
  char polStor[MAXWORDS][MAXWORDLEN + 1];
  char traStor[MAXWORDS][MAXWORDLEN + 1];
  char fanStor[MAXWORDS][MAXWORDLEN + 1];
  char advStor[MAXWORDS][MAXWORDLEN + 1];

  char bookStor[MAXWORDS][MAXWORDLEN + 1];

  readWords(sciFile, sciStor, sciStr);
  readWords(polFile, polStor, polStr);
  readWords(traFile, traStor, traStr);
  readWords(fanFile, fanStor, fanStr);
  readWords(advFile, advStor, advStr);

  FILE *book = fopen(argv[1], "r");
  readBookWords(book, bookStor, fanStor, sciStor, advStor, polStor, traStor, &fanCnt, &sciCnt, &advCnt, &polCnt, &traCnt);

  int recGen[5] = {}; //indeces are truth values for maxes in the order sci, tra, fan, adv, pol
  int max = -1;
  //find max
  if(sciCnt > max) {
    max = sciCnt;
  }
  if(traCnt > max) {
    max = traCnt;
  }
  if(fanCnt > max) {
    max = fanCnt;
  }
  if(advCnt > max) {
    max = advCnt;
  }
  if(polCnt > max) {
    max = polCnt;
  }

  //record which genre the max was and if there were any max ties
  if(sciCnt == max) {
    recGen[0] = 1;
  }
  if(traCnt == max) {
    recGen[1] = 1;
  }
  if(fanCnt == max) {
    recGen[2] = 1;
  }
  if(advCnt == max) {
    recGen[3] = 1;
  }
  if(polCnt == max) {
    recGen[4] = 1;
  }

  //print output
  bool printed = false;
  if(recGen[1]) {
    if(printed){
      printf(" Tragedy"); 
    } else {
      printf("Tragedy");
      printed = true;
    }
  }
  if(recGen[0]) {
    if(printed){
      printf(" Science"); 
    } else {
      printf("Science");
      printed = true;
    }
  }
  if(recGen[3]) {
    if(printed){
      printf(" Adventure"); 
    } else {
      printf("Adventure");
      printed = true;
    }
  }
  if(recGen[4]) {
    if(printed){
      printf(" Politics"); 
    } else {
      printf("Politics");
      printed = true;
    }
  }
  if(recGen[2]) {
    if(printed){
      printf(" Fantasy"); 
    } else {
      printf("Fantasy");
      printed = true;
    }
  }
  fclose(book);
  fclose(sciFile);
  fclose(polFile);
  fclose(traFile);
  fclose(advFile);
  fclose(fanFile);
  
}
