#!/bin/bash
FAIL=0

# Make a fresh copy of the target program
make clean
make
if [ $? -ne 0 ] || [ ! -x search ]; then
  echo "**** Make (compilation) FAILED"
  exit 13
fi

# Check the results of program execution.
# Splitting this out from the test function makes it easier
# to handle some error tests.
checkResults() {
  TESTNO=$1
  ESTATUS=$2

  # Make sure the program exited with the right exit status.
  if [ $STATUS -ne $ESTATUS ]; then
      echo "**** Test failed - incorrect exit status. Expected: $ESTATUS Got: $STATUS"
      FAIL=1
      return 1
  fi

  # Make sure the output matches the expected output.
  if [ -f expected-$TESTNO.txt ]; then
      diff -q expected-$TESTNO.txt output.txt >/dev/null 2>&1
      if [ $? -ne 0 ]; then
	  echo "**** Test FAILED - program output doesn't match expected"
	  FAIL=1
	  return 1
      fi
  elif [ -s output.txt ]; then
      # if there' no expected output for this test, the program shouldn't
      # have printed anything.
      echo "**** Test FAILED - shouldn't have printed output to stdout"
      FAIL=1
      return 1
  fi
      
  # Check different things, depending on whether it's successful.
  if [ $ESTATUS -eq 0 ]; then
      if [ -s stderr.txt ]; then
	  echo "**** Test FAILED - shouldn't have printed any error output"
	  FAIL=1
	  return 1
      fi
  else
      # Make sure the output matches the expected output.
      diff -q stderr-$TESTNO.txt stderr.txt >/dev/null 2>&1
      if [ $? -ne 0 ]; then
	  echo "**** Test FAILED - didn't print the right error message"
	  FAIL=1
	  return 1
      fi
  fi

  echo "Test $TESTNO PASS"
  return 0
}

# Test the pattern matching program.
runTest() {
  rm -f output.txt stderr.txt

  echo "Test $1: ./search $2 input-$1.txt > output.txt 2> stderr.txt"
  ./search $2 input-$1.txt > output.txt 2> stderr.txt
  STATUS=$?

  checkResults "$1" "$3"
}

# Run each of the test cases
runTest 01 capitalized_words 0
runTest 02 other_words 0
runTest 03 integers 0
runTest 04 real_numbers 0
runTest 05 alphanumeric 0
runTest 06 starting_with_a 0
runTest 07 empty_lines 0
runTest 08 ten_char_lines 0
runTest 09 other_words 1

if [ $FAIL -ne 0 ]; then
  echo "FAILING TESTS!"
  exit 13
else 
  echo "Tests successful"
  exit 0
fi

exit 0
