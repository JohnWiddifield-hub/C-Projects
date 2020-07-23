/**
This file will validate user input given the constraints of our program
blocking any input above the given threshold for parameters such as surpassing
maximum stamp types or invalid denominations.
@file validate.c
@author John Widdifield
*/
#include "validate.h"


bool validateTypes(int stpNum, int stamp[stpNum])
{
  if( stpNum < 1 ) {
    return false;
  } else if (stpNum > MAX_VALID) {
    return false;
  }
  int stp = stamp[0];
  if( stp > MAX_VALID || stp < MIN_VALID ) {
    return false;
  }
  
  for( int i = 1; i < stpNum; i++ ) {

    stp = stamp[i];

    if( stp > MAX_VALID || stp < MIN_VALID ) {
      return false;
    }
  }
  return true;
}



bool validateDenom(int stpNum, int stamp[stpNum]) 
{
  for (int i = 0; i < stpNum; i++) {
    if(stamp[i] > MAX_VALID || stamp[i] < 1) {
      return false;
    }
  }
  return true;
}


bool validateInputs(int stpNum, int cusNum, int stamp[stpNum], int customer[cusNum])
{
  return (validateDenom(cusNum, customer) && validateTypes(stpNum, stamp));
  
}
