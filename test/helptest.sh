#!/bin/bash
# Will be run from parent directory
echo "Testing help..."
src/cspeedtest --help > test/help.out
grep Usage test/help.out
