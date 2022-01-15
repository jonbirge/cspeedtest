# curses-speedtest

## Overview

This program uses curses to write screenfuls of random characters to the terminal, and uses the resulting framerate to estimate the network throughput. This is essentially a "clientless" speedtest for the network between a server and you using your terminal as the speedtest client.

## Usage

Install and compile on your remove server using make. Then run as follows:

```
Usage: cspeedtest [options]

Options:
  -b   low bandwidth (B/W)
  -r   non-random pattern (test compression)
  -h   show this help
  -v   show version
```

## Screenshot

<img width="923" alt="cspeedtest-color" src="https://user-images.githubusercontent.com/660566/147842191-f486bfaa-2f5c-4466-a19b-7e73e34e956f.png">
