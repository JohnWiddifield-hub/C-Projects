/**
This will implement the functionalities laid out in the solve header file.
To implement this I adapted code from the website provided in the project description
https://www.includehelp.com/icp/combinational-sum-problem.aspx
@file solve.c
@author John Widdifield
*/
#include "solve.h"
#include "validate.h"

void findCombinations(int beg, int cust_Num, int idx, int output[], int stamps[], int stamp_Num, int target, int (*matches)[MAX_VALID], int* row, int *number_matched)
{
	if (cust_Num == 0) {
    for(int i = 0; i < stamp_Num; i++) {
      int valid = 0;
      int numzero = 0;
      int invalid = 0;
      for(int j = 0; j < idx; j++) {
        if(output[j] == stamps[i] && output[j] != 0) {
          valid++;
        } else if(output[j] == 0) {
          numzero++;
        } else {
          invalid++;
        }
      }
      if(valid <= 0 || invalid >= 1) {
        return;
      }
    }

    int total = 0;
    for( int i = 0; i < idx; i++) {
      total += output[i];
    }
    if(total != target) {
      return;
    }
    //output is valid. now check for duplicates
    int row_idx = *row;
    while(row_idx >= 0) {
      int past_idx = 0;
      int test_idx = 0;
      while(output[test_idx] == 0) {
        test_idx++;
      }
      bool dupe = true;
      while(output[test_idx] != 0 && test_idx < idx ) {
        if (output[test_idx] != matches[row_idx][past_idx]) {
          dupe = false;
        }
        past_idx++;
        test_idx++;
      }
      row_idx--;
      if(dupe){
        return;
      } 
    }
    //perfectly valid output
    int j = 0;
    (*number_matched)++;
    if(*row != 0) {
      printf("\n");
    }
    printf("%d (%d):", target, *number_matched);
    for(int i = 0; i < idx; i++) {
      if(output[i] != 0) {
        //add the output to the matches array
        matches[*row][j] = output[i];
        j++;
        printf(" %d", output[i]);
      }
    }
    (*row)++;
  }
		
	for (int k = idx; k <= cust_Num; k++)
	{
		output[idx] = k;

		findCombinations(k, cust_Num - k, idx + 1, output, stamps, stamp_Num, target, matches, row, number_matched);
	}
}
