# curses-speedtest

## Overview

This program uses curses to write screenfuls of random characters to the terminal, and uses the resulting framerate to estimate the network throughput. This is essentially a "clientless" speedtest for the network between a server and you using your terminal as the speedtest client.

## Usage

Install and compile on your remove server using make. Then run as follows:

```
curses-speedtest [options]
Options:
-c   use color
-h   show this help
```
