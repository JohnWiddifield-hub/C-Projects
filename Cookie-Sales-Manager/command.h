/*
This is the header file for the command interpreting piece of the sales program.
@author John Widdifield
@file command.h
*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "model.h"
/*
This will process a command from the command line on a troop
@param troop troop to perform the command on
@return true if the command was a success false if the command failed
due to invalid input.
*/
bool processCommand( Troop *troop );
