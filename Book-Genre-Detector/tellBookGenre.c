/*
  This is the main controller file which controlls the flow of readBook and wordLists in order to
  read lists of target words for specific genres (science politics tragedys fantasy and adventure)
  and determine the genre of a given text document (up to 5000 words)
  @file tellBookGenre.c
  @author John Widdifield (jfwiddif)
*/
#include "wordLists.h"
#include "readBook.h"

/* This constant is used in comparing double values up to this precision */
#define DOUBLE_PREC 0.00001

/*
  This function is the main controller function it will read words from the files
  science_words.txt political_words.txt tragic_words.txt fantasy_words.txt and
  adventure_words.txt and match them against the input file reporting which
  genre or genres have the highest number of matches.
  @param argc The number of arguments passed by the console
  @param argv An array containing the arguments passed by the console argv[1] should contain the
            filename of the input file (book)
  @return 0 if the program exited successfully and 1 if there was an error that resulted in exit
*/
int main( int argc, char *argv[] )
{

  char sciStr[] = "science_words.txt";
  char polStr[] = "political_words.txt";
  char traStr[] = "tragic_words.txt";
  char fanStr[] = "fantasy_words.txt";
  char advStr[] = "adventure_words.txt";

  //percent counters numerators out of the maximum number of matched words
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

  FILE *sciFile = fopen("science_words.txt", "r");
  readWords(sciFile, sciStor, sciStr);
  FILE *polFile = fopen("political_words.txt", "r");
  readWords(polFile, polStor, polStr);
  FILE *traFile = fopen("tragic_words.txt", "r");
  readWords(traFile, traStor, traStr);
  FILE *fanFile = fopen("fantasy_words.txt", "r");
  readWords(fanFile, fanStor, fanStr);
  FILE *advFile = fopen("adventure_words.txt", "r");
  readWords(advFile, advStor, advStr);

  FILE *book = fopen(argv[1], "r");
  readBookWords(book, bookStor, fanStor, sciStor, advStor, polStor, traStor, &fanCnt, 
                &sciCnt, &advCnt, &polCnt, &traCnt);

  double total = sciCnt + advCnt + polCnt + fanCnt + traCnt;
  int recGen[5] = {}; //indeces are truth values for maxes in the order sci, tra, fan, adv, pol
  double max = -1.0;
  //find maximum percentage of matches per genre
  if ((sciCnt/total) > max) {
    max = sciCnt / total;
  }
  if ((traCnt/total) > max) {
    max = traCnt / total;
  }
  if ((fanCnt/total) > max) {
    max = fanCnt / total;
  }
  if ((advCnt/total) > max) {
    max = advCnt / total;
  }
  if ((polCnt/total) > max) {
    max = polCnt / total;
  }
  if (max == 0) {
    return EXIT_SUCCESS;
  }

  //record which genre the max was and if there were any max ties
  if ((max - (sciCnt / total)) < DOUBLE_PREC) {
    recGen[0] = 1;
  }
  if ((max - (traCnt / total)) < DOUBLE_PREC) {
    recGen[1] = 1;
  }
  if ((max - (fanCnt / total)) < DOUBLE_PREC) {
    recGen[2] = 1;
  }
  if ((max - (advCnt / total)) < DOUBLE_PREC) {
    recGen[3] = 1;
  }
  if ((max - (polCnt / total)) < DOUBLE_PREC) {
    recGen[4] = 1;
  }

  //print output
  bool printed = false;
  if (recGen[1]) {
    if (printed) {
      printf(" Tragedy");
    } else {
      printf("Tragedy");
      printed = true;
    }
  }
  if (recGen[0]) {
    if (printed) {
      printf(" Science");
    } else {
      printf("Science");
      printed = true;
    }
  }
  if (recGen[3]) {
    if (printed) {
      printf(" Adventure");
    } else {
      printf("Adventure");
      printed = true;
    }
  }
  if (recGen[4]) {
    if (printed) {
      printf(" Politics");
    } else {
      printf("Politics");
      printed = true;
    }
  }
  if (recGen[2]) {
    if (printed) {
      printf(" Fantasy");
    } else {
      printf("Fantasy");
      printed = true;
    }
  }
  return EXIT_SUCCESS;
}
