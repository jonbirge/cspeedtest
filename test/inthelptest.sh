#!/bin/sh
set -eu

output=$(./src/cspeedtest-int --help)
printf '%s\n' "$output" | grep -F "Usage: cspeedtest-int [options]"
