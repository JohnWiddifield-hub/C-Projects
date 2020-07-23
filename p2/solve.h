#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "validate.h"

/**
This will find and report combinational sums from beg up to the cust_num parameters.
@param beg lower bound fot the combinational sum
@param cust_Num upper bound for the combinational sum
@param idx index which will start at 0 and increase through recursion throughout the recursive
        calls
@param output This is an array which the program may use to store unfiltered combinational sums
@param stamps The array of stamps which are to be used to filter the combinational sums
@param stamp_Num number of stamps in the stamps array
@param target the target value for the sum to total up to
@param matches This is a 2D array which records the filtered combinational sums used in duplication
        checking
@param row The index of the current row in the matches array to be used for storing the next sum
@param number_matched Stores the number of matched valid filtered sums.
*/
void findCombinations(int beg, int cust_Num, int idx, int output[], int stamps[], int stamp_Num, int target, int (*matches)[MAX_VALID], int* row, int *number_matched);
