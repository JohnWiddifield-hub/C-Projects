/**
This allows the user to type commands to modify the group given by the tracker
@file command.h
@author John Widdifield (jfwiddif)
*/
#include "model.h"
#include <limits.h>
/**
This function will process user input to modify the group of salespeople and their
sales using the following base commands: book, salesperson, sale, list books, list group,
list salesperson and quit.

book commands are in the following format: book id name
salesperson commands are in the following format: salesperson id name
sale commands are in the following format: sale salesperson-id book-id number-book-sold
list salesperson commands are in the following format: list salesperson salesperson-id

@param group the group which is to be modified by the users commands
@return true if the command was properly processed, false if there was an error such as invalid
        input
*/
bool processCommand( Group *group );
