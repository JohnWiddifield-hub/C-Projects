#!/bin/bash
FAIL=0

# Function to run a test.  Expects the arguments in the variable, args, which
# is probably bad.
runTest() {
  TESTNO=$1
  TEXT=$2
  ESTATUS=$3

  rm -f output.txt stderr.txt
  
  echo "Test $TESTNO: ./select ${args[@]} $TEXT"
  ./select ${args[@]} $TEXT > output.txt 2> stderr.txt
  STATUS=$?

  # Make sure the program exited with the right exit status.
  if [ $STATUS -ne $ESTATUS ]; then
      echo "**** FAILED - Expected an exit status of $ESTATUS, but got: $STATUS"
      FAIL=1
      return 1
  fi

  # Make sure output matches expected output.
  if ! diff -q expected-$TESTNO.txt output.txt >/dev/null 2>&1 ; then
      echo "**** FAILED - output to stdout didn't match expected."
      FAIL=1
      return 1
  fi

  # Make sure the output to stderr matches expected.
  if [ -f estderr-$TESTNO.txt ] &&
	 ! diff -q estderr-$TESTNO.txt stderr.txt >/dev/null 2>&1 ; then
      echo "**** FAILED - output to stderr didn't match expected"
      FAIL=1
      return 1
  fi

  echo "PASS"
  return 0
}

# Try to get a fresh compile of the project.
make clean
make
if [ $? -ne 0 ]; then
    echo "**** Make didn't run succesfully when trying to build your program."
    FAIL=1
fi

# Run individual tests.
if [ -x select ] ; then
    args=()
    runTest 01 input-1.txt 0
    
    args=(+lines 1 1)
    runTest 02 input-1.txt 0

    args=(+lines 1 9)
    runTest 03 input-1.txt 0

    args=(+lines -2 -1)
    runTest 04 input-1.txt 0

    args=(+lines 5 -5 -lines 10 -10)
    runTest 05 input-2.txt 0

    args=(+lines 10 90 -lines 21 29 -lines 41 49 +lines 45 45 -lines 61 89 +lines 70 80)
    runTest 06 input-2.txt 0

    args=(+pat 7)
    runTest 07 input-2.txt 0

    args=(+pat set)
    runTest 08 input-3.txt 0

    args=(+lines 1 -1 -pat set)
    runTest 09 input-3.txt 0

    args=(+pat oo -lines 1 1000 -lines -1000 -1)
    runTest 10 input-5.txt 0

    args=(+word set)
    runTest 11 input-3.txt 0

    args=(+word printf)
    runTest 12 input-4.txt 0

    args=(+lines 1 -1 -word the -word and)
    runTest 13 input-4.txt 0

    args=(+word a +word WqyxNt +word pazfr +word GJHPGPGSF +word RC +word rzlVN)
    runTest 14 input-5.txt 0

    args=(+lines 1 10 )
    runTest 15 input-6.txt 1

    args=(+lines 20 -20)
    runTest 16 input-7.txt 1

    args=(+word string-with7bad+characters)
    runTest 17 input-3.txt 1

    args=(+lines abc xyz)
    runTest 18 input-3.txt 1

    args=(+lines abc xyz)
    runTest 18 input-3.txt 1

    args=(+pat abc)
    runTest 19 not-a-real-file.txt 1

    args=(+bad arguments -that will not -work)
    runTest 20 input-1.txt 1

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
