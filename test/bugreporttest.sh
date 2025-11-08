#!/bin/sh
set -eu

./src/cspeedtest --version | grep -F "Bug reports to"
