#include <"validate.h">

bool validateTypes(int stpNum, int stamp[stpNum])
{
  if( stpNum < 1 ) {
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
  return validateTypes(stpNum, stamp);
}


bool validateInputs(int stpNum, int cusNum, int stamp[stpNum], int customer[cusNum])
{
  return (validateDenom(cusNum, customer) && validateTypes(stpNum, stamp));
  
}
