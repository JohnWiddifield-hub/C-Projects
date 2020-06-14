/*
  This file is the header for readBook.c and provides public useage of its function
  readBookWords to read words from a book matching genre specific words
  @file readBook.h
  @author John Widdifield (jfwiddif)
*/

/*
  This function will read words from a book (up to 5000 words)and store them in a storage array
  as well as match genre specific words from specified 2D arrays containing those words and report
  the counts of each match found for each genre
  @param book This is the file stream which contains the book
  @param bookStorage This is the array which will store all of the matched words inside the book
  @param fanStor This is the array which stores all of the Fantasy genre words to match
  @param sciStor This is the array which stores all of the Science genre words to match
  @param advStor This is the array which stores all of the Adventure genre words to match
  @param polStor This is the array which stores all of the Political genre words to match
  @param traStor This is the array which stores all of the Tragedy genre words to match
  @param *fanCnt This is a pointer to an integer which represents the number Fantasy word matches
                (assumed to contain 0 upon function call)
  @param *sciCnt This is a pointer to an integer which represent the number Science word matches
                (assumed to contain 0 upon function call)
  @param *advCnt This is a pointer to an integer which represent the number Adventure word matches
                (assumed to contain 0 upon function call)
  @param *polCnt This is a pointer to an integer which represent the number Political word matches
                (assumed to contain 0 upon function call)
  @param *traCnt This is a pointer to an integer which represent the number Tragedy word matches
                (assumed to contain 0 upon function call)
*/
void readBookWords(FILE *book, char bookStorage[][21], char fanStor[][21], char sciStor[][21],
     char advStor[][21], char polStor[][21], char traStor[][21], int *fanCnt, int *sciCnt,
     int *advCnt, int *polCnt, int *traCnt);
