# curses-speedtest

## Overview

This program uses curses to write screenfuls of random characters to the terminal, and uses the resulting framerate to estimate the network throughput. This is essentially a "clientless" speedtest for the network between a server and you using your terminal as the speedtest client. This means that you can get a quick approximate network speed test to your server from anywhere without having to install local software. The cost to this convenience is that the test is only an approximate lower bound, especially for high bandwidth situations where the terminal speed becomes the limiting factor.

## Usage

Install and compile on your remove server using the standard GNU build process (./configure && make). Then run as follows:

```
Usage: cspeedtest [options]

Options:
  -t, --time==T          set integration time to T seconds
  -b, --low-bandwidth    low bandwidth (B/W)
  -h, --help             show this help
  -v, --version          show version
```

Depending on your terminal and/or connection, you may have to try both color and b/w modes to get the highest speed (which is, again, a lower bound).

## Screenshot

<img width="923" alt="cspeedtest-color" src="https://user-images.githubusercontent.com/660566/147842191-f486bfaa-2f5c-4466-a19b-7e73e34e956f.png">

## Distribution

[![Get it from the Snap Store](https://snapcraft.io/static/images/badges/en/snap-store-black.svg)](https://snapcraft.io/cspeedtest)
