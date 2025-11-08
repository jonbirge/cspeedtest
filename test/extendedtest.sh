#!/bin/sh
set -eu

output=$(./src/cspeedtest --test --extended 2>&1)
printf '%s\n' "$output" | grep -F "Using extended characters. Some terminals may have issues."
