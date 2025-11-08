#!/bin/sh
set -eu

output=$(./src/cspeedtest -i --help)
printf '%s\n' "$output" | grep -F "Usage: cspeedtest-int [options]"
