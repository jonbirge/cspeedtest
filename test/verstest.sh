#!/bin/bash
# Will be run from parent directory
echo "Testing version..."
src/cspeedtest --version > test/vers.out
grep cspeedtest test/vers.out
