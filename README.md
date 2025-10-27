[![CodeQL](https://github.com/jonbirge/curses-speedtest/actions/workflows/codeql-analysis.yml/badge.svg)](https://github.com/jonbirge/curses-speedtest/actions/workflows/codeql-analysis.yml)
[![C/C++ CI](https://github.com/jonbirge/curses-speedtest/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/jonbirge/curses-speedtest/actions/workflows/c-cpp.yml)

# cspeedtest

## Overview

This program uses curses to write screenfuls of random characters to the terminal, and uses the resulting framerate to estimate the network throughput. This is essentially a "clientless" speedtest for the network path between your server your terminal, using a standard ANSI terminal as the remote client. This means that you can get a quick approximate network speed test from anywhere without having to install local software. The cost to this convenience is that the test is only an approximate lower bound, especially for high bandwidth situations where the terminal speed becomes the limiting factor.

## Work needed

- This does a pretty good job at establishing a *lower bound* on the the network speed between the terminal and the server on which cspeedtest is installed, but better calibration could be done.
- We should probably just dispense with the "fun" displays, as it seems they are too easy for ncurses to compress and thus provide an anomolous reading.
- The performance graph is also likely impacting the measurement for the same reason, and should be relegated to a simple bar graph in the top line (and not counted as part of the throughput)

## Usage

### Where to install

You just need to install this on the server where you want to measure network speed. Then, you can get an estimate of the network speed from that server to any terminal by logging in via ssh and running `cspeedtest`.

### Command line options

```
Usage: cspeedtest [options]

Options:
  -t T, --int T          set integration time to T seconds
  -i, --interactive      interactive mode
  -b, --low-bandwidth    start in low bandwidth mode
  -h, --help             show this help
  -V, --version          show version
  -v, --verbose          show debugging info
```

Depending on your terminal and/or connection, you may have to try both color and b/w modes to get the highest speed. To test under different conditions (and for fun) there are deterministic patterns that can be displayed by hitting the `r` key.

## Screenshot

<img width="923" alt="cspeedtest-color" src="https://user-images.githubusercontent.com/660566/147842191-f486bfaa-2f5c-4466-a19b-7e73e34e956f.png">

## Installing

### Install from source

Install and compile on your remote server using the standard GNU build process (`autogen && ./configure && make install`).

### Install snap distribution

[![Get it from the Snap Store](https://snapcraft.io/static/images/badges/en/snap-store-black.svg)](https://snapcraft.io/cspeedtest)
