#!/bin/bash
FAIL=0

# make a fresh copy of the target programs
make clean
make
if [ $? -ne 0 ]; then
  echo "**** Make (compilation) FAILED"
  FAIL=1
fi

# Test the deflate program.
testDeflate() {
  TESTNO=$1
  ESTATUS=$2

  rm -f compressed.bin stdout.txt stderr.txt

  echo "Test deflate $TESTNO: ./deflate ${args[@]}"
  ./deflate ${args[@]} > stdout.txt 2> stderr.txt
  STATUS=$?

  # Make sure the program exited with the right exit status.
  if [ $STATUS -ne $ESTATUS ]; then
      echo "**** Test failed - incorrect exit status. Expected: $ESTATUS Got: $STATUS"
      FAIL=1
      return 1
  fi

  # See if the output file looks right.
  if [ -s expected-$TESTNO.bin ]; then
      # Make sure the output matches the expected output.
      diff -q compressed.bin expected-$TESTNO.bin >/dev/null 2>&1
      if [ $? -ne 0 ]; then
	  echo "**** Test FAILED - output file (compressed.bin) doesn't match expected-$TESTNO.bin"
	  FAIL=1
	  return 1
      fi
  fi

  # 
  if [ -s estderr-$TESTNO.txt ]; then
      # Make sure the error message matches the expected message
      diff -q stderr.txt estderr-$TESTNO.txt >/dev/null 2>&1
      if [ $? -ne 0 ]; then
	  echo "**** Test FAILED - error output doesn't match estderr-$TESTNO.txt"
	  FAIL=1
	  return 1
      fi
  else
      # On successful tests, the program shouldn't print anything to stderr.
      if [ -s stderr.txt ]; then
	  echo "**** Test FAILED - shouldn't write anything to standard error."
	  FAIL=1
	  return 1
      fi
  fi

  # Shouldn't print anything to the terminal.
  if [ -s stdout.txt ]; then
      echo "**** Test failed - shouldn't print anything to standard output"
      FAIL=1
      return 1
  fi

  echo "Test PASS"
  return 0
}

# Test the inflate program.
testInflate() {
  TESTNO=$1
  ESTATUS=$2

  rm -f original stdout.txt stderr.txt

  echo "Test inflate $TESTNO: ./inflate ${args[@]}"
  ./inflate ${args[@]} > stdout.txt 2> stderr.txt
  STATUS=$?

  # Make sure the program exited with the right exit status.
  if [ $STATUS -ne $ESTATUS ]; then
      echo "**** Test failed - incorrect exit status. Expected: $ESTATUS Got: $STATUS"
      FAIL=1
      return 1
  fi

  # See if the output file looks right.
  if [ -s expected-$TESTNO.bin ]; then
      # Make sure the output matches the expected output.
      diff -q original input-$TESTNO >/dev/null 2>&1
      if [ $? -ne 0 ]; then
	  echo "**** Test FAILED - output file (original) doesn't match original file input-$TESTNO"
	  FAIL=1
	  return 1
      fi
  fi

  # 
  if [ -s estderr-$TESTNO.txt ]; then
      # Make sure the error message matches the expected message
      diff -q stderr.txt estderr-$TESTNO.txt >/dev/null 2>&1
      if [ $? -ne 0 ]; then
	  echo "**** Test FAILED - error output doesn't match estderr-$TESTNO.txt"
	  FAIL=1
	  return 1
      fi
  else
      # On successful tests, the program shouldn't print anything to stderr.
      if [ -s stderr.txt ]; then
	  echo "**** Test FAILED - shouldn't write anything to standard error."
	  FAIL=1
	  return 1
      fi
  fi

  # Shouldn't print anything to the terminal.
  if [ -s stdout.txt ]; then
      echo "**** Test failed - shouldn't print anything to standard output"
      FAIL=1
      return 1
  fi

  echo "Test PASS"
  return 0
}

# Test the deflate program
echo
echo "Testing deflate"
if [ -x deflate ]; then
    args=(code-1.txt input-01 compressed.bin)
    testDeflate 01 0

    args=(code-1.txt input-02 compressed.bin)
    testDeflate 02 0

    args=(code-1.txt input-03 compressed.bin)
    testDeflate 03 0

    args=(code-2.txt input-04 compressed.bin)
    testDeflate 04 0

    args=(code-2.txt input-05 compressed.bin)
    testDeflate 05 0

    args=(code-3.txt input-06 compressed.bin)
    testDeflate 06 0

    args=(code-3.txt input-07 compressed.bin)
    testDeflate 07 0

    args=(code-2.txt input-08 compressed.bin)
    testDeflate 08 0
    
    args=(code-2.txt file-that-does-not-exist compressed.bin)
    testDeflate 09 1

    args=(code-4.txt input-10 compressed.bin)
    testDeflate 10 1
    
    args=(code-3.txt input-11 compressed.bin extra arguments)
    testDeflate 11 1
else
  echo "Since your deflate program didn't compile, we couldn't test it"
fi

# Test the inflate program
echo
echo "Testing inflate"
if [ -x inflate ]; then
    args=(code-1.txt expected-01.bin original)
    testInflate 01 0

    args=(code-1.txt expected-02.bin original)
    testInflate 02 0

    args=(code-1.txt expected-03.bin original)
    testInflate 03 0

    args=(code-2.txt expected-04.bin original)
    testInflate 04 0

    args=(code-2.txt expected-05.bin original)
    testInflate 05 0

    args=(code-3.txt expected-06.bin original)
    testInflate 06 0

    args=(code-3.txt expected-07.bin original)
    testInflate 07 0

    args=(code-2.txt expected-08.bin original)
    testInflate 08 0

    args=(code-2.txt input-12 original)
    testInflate 12 1

    args=(code-5.txt input-13 original)
    testInflate 13 1

    args=(code-6.txt input-14 original)
    testInflate 14 1

else
  echo "Since your inflate program didn't compile, we couldn't test it"
fi

if [ $FAIL -ne 0 ]; then
  echo "FAILING TESTS!"
  exit 13
else 
  echo "Tests successful"
  exit 0
fi
