#include "command.h"

int main()
{
  Group *gp = createGroup();
  while (true) {
    processCommand(gp);
  }
  freeGroup(gp);
  return EXIT_SUCCESS;
}
