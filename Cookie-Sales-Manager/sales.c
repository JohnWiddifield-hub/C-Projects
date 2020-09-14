/*
This is the main controller file
@file sales.c
@author John Widdifield
*/
#include "command.h"

/*
Main method which controlls the program
@return 0 if successful, 1 if not
*/
int main()
{
  Troop *troop = createTroop();
  while (processCommand(troop)) {
    continue;
  }
  //printf("%d", EOF);
  freeTroop(troop);
}
