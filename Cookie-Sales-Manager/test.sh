#!/bin/bash
FAIL=0

# Function to run the program against a test case and check
# its output and exit status for correct behavior
testProgram() {
  TESTNO=$1

  rm -f output.txt

  echo "Test $TESTNO: ./sales < input-$TESTNO.txt > output.txt 2>&1"
  ./sales < input-$TESTNO.txt > output.txt 2>&1
  STATUS=$?

  # Make sure the program exited successfully
  if [ $STATUS -ne 0 ]; then
      echo "**** Test $TESTNO FAILED - incorrect exit status"
      FAIL=1
      return 1
  fi
  
  # Make sure any output to standard out looks right.
  if ! diff -q expected-$TESTNO.txt output.txt >/dev/null 2>&1
  then
      echo "**** Test $TESTNO FAILED - output didn't match the expected output"
      FAIL=1
      return 1
  fi

  echo "Test $TESTNO PASS"
  return 0
}

# make a fresh copy of the target programs
make clean
make

if [ -x sales ] ; then
    testProgram 01
    testProgram 02
    testProgram 03
    testProgram 04
    testProgram 05
    testProgram 06
    testProgram 07
    testProgram 08
    testProgram 09
    testProgram 10
    testProgram 11
    testProgram 12
    testProgram 13
    testProgram 14
    testProgram 15
    testProgram 16
    testProgram 17
    testProgram 18
else
    echo "**** Your program didn't compile successfully, so we couldn't test it."
    FAIL=1
fi

if [ $FAIL -ne 0 ]; then
  echo "FAILING TESTS!"
  exit 13
else 
  echo "Tests successful"
  exit 0
fi
