#!/bin/bash
FAIL=0

# Function to check the output of the program after it's run, including checking
# an output file, standard output, standard error and exit status.
checkResults() {
  TESTNO=$1
  ESTATUS=$2
  STATUS=$3

  # Make sure the program exited with the right exit status.
  if [ $STATUS -ne $ESTATUS ]; then
      echo "**** Test $TESTNO FAILED - Expected an exit status of $ESTATUS, but got: $STATUS"
      FAIL=1
      return 1
  fi

  # Make sure output matches expected output.
  if ! diff -q expected-$TESTNO.txt output.txt >/dev/null 2>&1 ; then
      echo "**** Test $TESTNO FAILED - output to stdout didn't match expected."
      FAIL=1
      return 1
  fi

  # Make sure the output to stderr matches expected.
  if ! diff -q estderr-$TESTNO.txt stderr.txt >/dev/null 2>&1 ; then
      echo "**** Test $TESTNO FAILED - output to stderr didn't match expected"
      FAIL=1
      return 1
  fi

  echo "Test $TESTNO PASS"
  return 0
}

# Try to get a fresh compile of the project.
make clean
make
if [ $? -ne 0 ]; then
    echo "**** Make didn't run succesfully when trying to build your program."
    FAIL=1
fi

# Run individual tests.  Since they each require different arguments,
# it didn't make as much sense to write a single test function for
# this.
if [ -x tellBookGenre ] ; then
    rm -f output.txt stderr.txt
    echo "Test 01: ./tellBookGenre input-01.txt"
    ./tellBookGenre input-01.txt > output.txt 2> stderr.txt
    STATUS=$?
    checkResults 01 0 $STATUS

    rm -f output.txt stderr.txt
    echo "Test 02: ./tellBookGenre input-02.txt"
    ./tellBookGenre input-02.txt > output.txt 2> stderr.txt
    STATUS=$?
    checkResults 02 0 $STATUS

    rm -f output.txt stderr.txt
    echo "Test 03: ./tellBookGenre input-03.txt"
    ./tellBookGenre input-03.txt > output.txt 2> stderr.txt
    STATUS=$?
    checkResults 03 0 $STATUS

    rm -f output.txt stderr.txt
    echo "Test 04: ./tellBookGenre input-04.txt"
    ./tellBookGenre input-04.txt > output.txt 2> stderr.txt
    STATUS=$?
    checkResults 04 0 $STATUS

    rm -f output.txt stderr.txt
    echo "Test 05: ./tellBookGenre input-05.txt"
    ./tellBookGenre input-05.txt > output.txt 2> stderr.txt
    STATUS=$?
    checkResults 05 0 $STATUS

    rm -f output.txt stderr.txt
    echo "Test 06: ./tellBookGenre input-06.txt"
    ./tellBookGenre input-06.txt > output.txt 2> stderr.txt
    STATUS=$?
    checkResults 06 0 $STATUS

    rm -f output.txt stderr.txt
    echo "Test 07: ./tellBookGenre input-07.txt"
    ./tellBookGenre input-07.txt > output.txt 2> stderr.txt
    STATUS=$?
    checkResults 07 1 $STATUS

    rm -f output.txt stderr.txt
    echo "Test 08: ./tellBookGenre input-08.txt"
    ./tellBookGenre input-08.txt > output.txt 2> stderr.txt
    STATUS=$?
    checkResults 08 0 $STATUS

    rm -f output.txt stderr.txt
    echo "Test 09: ./tellBookGenre input-09.txt"
    ./tellBookGenre input-09.txt > output.txt 2> stderr.txt
    STATUS=$?
    checkResults 09 0 $STATUS

    rm -f output.txt stderr.txt
    echo "Test 10: ./tellBookGenre input-10.txt"
    ./tellBookGenre input-10.txt > output.txt 2> stderr.txt
    STATUS=$?
    checkResults 10 0 $STATUS

else
    echo "**** Your program couldn't be tested since it didn't compile successfully."
    FAIL=1

fi

if [ $FAIL -ne 0 ]; then
  echo "**** There were failing tests"
  exit 1
else 
  echo "Tests successful"
  exit 0
fi
