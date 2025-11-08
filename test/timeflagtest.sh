#!/bin/sh
set -eu

output=$(./src/cspeedtest --test --time=5 2>&1)
printf '%s\n' "$output" | grep -F "Setting integration time to 5 seconds."
