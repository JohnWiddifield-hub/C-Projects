/**
This is the header file for the validate file and lays out the definitions for validating user
input
@file validate.h
@author John Widdifield
*/

#include <stdbool.h>
// This is the max number of stamps allowed by the program
#define MAX_VALID 25
// This is the minimum number of stamps allowed by the program
#define MIN_VALID 1

/**
This will validate that the parameters contain valid stamp types provided by the user.
@param stpNum number of stamps to solve
@param stamp an array of the stamps
@return true if the types are valid false if they are invalid
*/
bool validateTypes(int stpNum, int stamp[stpNum]);
/**
This will check the stamps array for valid denominations
@param stpNum number of stamps in the stamp array
@param stamp array which holds all of the different stamps
@return false if the array contains invalid denominations true if they are valid
*/
bool validateDenom(int stpNum, int stamp[stpNum]);
/**
This will validate all of the input given by the user to be used for stamp.c.  Checking
to see if the inputs are within the project specifications by using the other functions
@param stpNum number of stamps
@param cusNum number of customers
@param stamp array of stamps
@param customer array of customers
@return true if the inputs are valid false if there is an invalid input
*/
bool validateInputs(int stpNum, int cusNum, int stamp[stpNum], int customer[cusNum]);
