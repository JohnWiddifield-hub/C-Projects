/**
This file is the driver for the stamp program and will report the combinational
sums for the given stamps and customer requests.  Or it will report their ties or lack of
valid sumations.
@file stamp.c
@author John Widdifield (jfwiddif)
*/
#include "validate.h"
#include "solve.h"

/**
This is the heart of the program and delegates to validate.c and solve.c to determine
valid inputs and to solve the combinational sum given by the user
@return 0 if successful, 1 is unsuccessful
*/
int main()
{
  
  int num_customers = 0;
  int num_stamps = 0;
  int match_row = 0;
  scanf("%d %d", &num_stamps, &num_customers);

  int *cust_list = (int *) malloc( num_customers * sizeof(int));
  int *stamp_list = (int *) malloc( num_stamps * sizeof(int));
  
  for(int i = 0; i < num_stamps; i++) {
    scanf("%d", &stamp_list[i]);
  }

  for(int i = 0; i < num_customers; i++) {
    scanf("%d", &cust_list[i]);
    if(cust_list[i] > MAX_VALID){
      free(cust_list);
      free(stamp_list);
      return EXIT_FAILURE;
    }
  }

  if(!validateDenom(num_stamps, stamp_list)) {
    printf("Invalid denomination");
    free(cust_list);
    free(stamp_list);
    return EXIT_FAILURE; 
  } else if(!validateTypes(num_stamps, stamp_list)) {
    printf("Invalid number of types");
    free(cust_list);
    free(stamp_list);
    return EXIT_FAILURE;
  }

  for ( int i = 0; i < num_customers; i++) {
    int *output = (int *) calloc( cust_list[i], sizeof(int));
    int (*matches)[MAX_VALID];
    matches = (int (*)[MAX_VALID]) calloc(MAX_VALID * MAX_VALID, sizeof(int));
    int target = cust_list[i];
    int number_matched = 0;
    int change = match_row;
    findCombinations(1, cust_list[i], 0, output, 
                    stamp_list, num_stamps, target, matches, 
                    &match_row, &number_matched);
    if(change == match_row) {
      printf("\n%d ---- none", target);
    }

    free(output);
    free(matches);
  }



  free(cust_list);
  free(stamp_list);
}
