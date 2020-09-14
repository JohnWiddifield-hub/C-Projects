/*
This is the class which processes commands
@file command.c
@author John Widdifield
*/
#include "command.h"

bool processCommand( Troop *troop )
{
  static int lnCnt = 1;

  printf("%d> ", lnCnt);
  char input[MAX_LINE] = "0";
  fgets(input, sizeof(input), stdin);
  printf("\n");
  lnCnt++;


  char *word = strtok(input, " \n");
  
  if ( strcmp(word, "list") == 0) {
    word = strtok(NULL, " \n");
    if ( strcmp(word, "cookies") == 0  || strcmp(word, "cookies\n") == 0) {
      int total = 0;
      printf("ID         Name                          Boxes Sold\n");
      for ( int i = 0; i < troop->cCount; i++) {
        printf("%-10s %-30s %9d\n", troop->cList[i]->id, troop->cList[i]->name,
 troop->cList[i]->boxes);
        total += troop->cList[i]->boxes;
      }
      printf("Total                                            %2d\n", total);
      return true;
    } else if ( strcmp(word, "scout") == 0 || strcmp(word, "scout\n") == 0) {
      word = strtok(NULL, " \n");
      if ( strlen(word) > MAX_ID ) {
        return false;
      } else {
        char scoutID[MAX_ID + 1];
        for ( int i = 0; i < troop->sCount; i++) {
          if (strcmp(troop->sList[i]->id, scoutID) == 0) {
            printf("ID         Name                          Boxes Sold\n");
            CookieNode *current = troop->sList[i]->head;
            int total = 0;
            while (current) {
              printf("%-10s %-30s %9d\n", current->cookie->id,
current->cookie->name, current->boxes);
              total += current->boxes;
              current = current->next;
            }
            printf("Total                                            %2d\n", total);
            return true;
          }
        }
        return false;
      }
    } else if ( strcmp(word, "troop") == 0 || strcmp(word, "troop\n") == 0) {
      int total = 0;
      printf("ID         Name                          Boxes Sold\n");
      for ( int i = 0; i < troop->sCount; i++) {
        printf("%-10s %-30s %9d\n", troop->sList[i]->id, troop->sList[i]->name,
 troop->sList[i]->boxes);
        total += troop->sList[i]->boxes;
      }
      printf("Total                                            %2d\n", total);
      return true;
        return true;
    } else return false;

  } else if ( strcmp(word, "cookie") == 0) {
      word = strtok(NULL, " \n");
      if ( strlen(word) > MAX_ID ) {
        return false;
      } else {
        char cookieID[MAX_ID + 1] = "";
        strcpy(cookieID, word);
        char cookieName[MAX_NAME] = "";
        int wordCount = 0;
        int charCount = 0;
        word = strtok(NULL, " \n");
        while ( word != NULL ) {
          charCount += strlen(word + 1);
          if (wordCount != 0) {
            strcat(cookieName, " ");
          }
          strcat(cookieName, word);
          wordCount++;
          word = strtok(NULL, " \n");
        }
        if (wordCount == 0 || charCount > MAX_NAME) {
          return false;
        }
        Cookie *newCook = createCookie( cookieID, cookieName );
        for ( int i = 0; i < troop->cCap; i++ ) {
          if ( troop->cCount == troop->cCap ) {
            troop->cCap *= DOUBLE_CAP;
            troop->cList = (Cookie **) realloc(troop->cList, troop->cCap * sizeof(Cookie * ));
          }
          if (troop->cList[i] == NULL) {
            troop->cList[i] = newCook;
            troop->cCount = troop->cCount + 1;
            break;
          }
        }
      }
      return true;
  } else if ( strcmp(word, "scout") == 0) {
      word = strtok(NULL, " \n");
      if ( strlen(word) > MAX_ID ) {
        return false;
      } else {
        char scoutID[MAX_ID + 1] = "";
        strcpy(scoutID, word);
        char scoutName[MAX_NAME] = "";
        int wordCount = 0;
        int charCount = 0;
        while ( word != NULL ) {
          charCount += strlen(word + 1);
          if (wordCount != 0) {
            strcat(scoutName, " ");
          }
          strcat(scoutName, word);
          wordCount++;
        }
        if (wordCount == 0 || charCount > MAX_NAME) {
          return false;
        }
        Scout *newScout = createScout( scoutID, scoutName );
        for ( int i = 0; i < troop->sCap; i++ ) {
          if ( troop->sCount == troop->sCap ) {
            troop->sCap *= DOUBLE_CAP;
            troop->sList = (Scout **) realloc(troop->sList, troop->sCap * sizeof(Scout * ));
          }
          if (troop->sList[i] == NULL) {
            troop->sList[i] = newScout;
            troop->sCount = troop->sCount + 1;
            break;
          }
        }
      }
      return true;
  } else if ( strcmp(word, "sale") == 0) {
      char scoutID[MAX_ID + 1] = "";
      char cookieID[MAX_ID + 1] = "";
      int boxSold = 0;
      word = strtok(NULL, " \n");
      if ( strlen(word) > MAX_ID ) {
        return false;
      }
      strcpy(scoutID, word);

      word = strtok(NULL, " \n");
      if ( strlen(word) > MAX_ID ) {
        return false;
      }
      strcpy(cookieID, word);

      word = strtok(NULL, " \n");
      if (atoi(word) == 0) {
        return false;
      } else {
        boxSold = atoi(word);
      }
      
      for (int i = 0; i < troop->sCount; i++) {
        if ( strcmp(troop->sList[i]->id, scoutID) == 0 ) {
          CookieNode *current = troop->sList[i]->head;
          int match = 0;
          while ( current ) {
            if ( strcmp(current->cookie->id, cookieID) == 0 ) {
              current->boxes += boxSold;
              current->cookie->boxes += boxSold;
              match += 1;
              break;
            }
            if (!current->next) {
              break;
            }
            current = current->next;
          }
          if (match == 0) {
            for (int i = 0; i < troop->cCount; i++) {
              if (strcmp(troop->cList[i]->id, cookieID) == 0) {
                current->next = (CookieNode *) malloc( sizeof( CookieNode ) );
                current->next->next = NULL;
                current->next->cookie = troop->cList[i];
                troop->cList[i]->boxes += boxSold;
                current->next->boxes = boxSold;
              }
            }
          }
        }
      }

    return true;
  } else if (strcmp(word, "quit") == 0 || strcmp(word, "quit\n") == 0) {
      freeTroop(troop);
      //printf("\n");
      exit(EXIT_SUCCESS);
      return true;
  } else {
    return false;
  }
}
