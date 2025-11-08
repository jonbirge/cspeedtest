#!/bin/sh
set -eu

output=$(./src/cspeedtest --help)
printf '%s\n' "$output" | grep -F "Usage: cspeedtest [options]"
printf '%s\n' "$output" | grep -F -- "-i, --interactive"
