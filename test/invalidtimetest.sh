#!/bin/sh
set -eu

output=$(./src/cspeedtest --test -t 0 2>&1)
printf '%s\n' "$output" | grep -F "Invalid integration time specified. Ignoring."
