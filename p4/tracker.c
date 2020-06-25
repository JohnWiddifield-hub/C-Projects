/**
This is the controller file which mainly delegates to the other files command.c and model.c
in order to maintain a list of book sales and salepeople
@file tracker.c
@author John Widdifield (jfwiddif)
*/
#include "command.h"
/**
This is the main controller function which holds the group and processes commands on it until
cancelled
@return 0 if successful 1 if any fatal errors occurred
*/
int main()
{
  Group *gp = createGroup();
  while (true) {
    processCommand(gp);
  }
  freeGroup(gp);
  return EXIT_SUCCESS;
}
