% CSPEEDTEST(1) cspeedtest User Manual
% Jonathan Birge
% 2023-01-13 17:01:28

# NAME

cspeedtest-int - clientless network speed test running interactively

# SYNOPSIS

cspeedtest-int [*options*] ...

# DESCRIPTION

cspeedtest is a command-line program that runs remotely on a server and measures network speed between a local terminal and that server. This allows one to measure network speed without having to install client software on every machine from which you connect. In addition, it provides a measure of network speed between you and your server, not between your server and some third-party server.

Usage is fairly simple. Just running

    cspeedtest >> log.txt

Runs a short seven second test and logs the value to a file. Output goes to *stdout* by default.

The way cspeedtest measures network speed is by using the ncurses library to send screens full of random characters to the local terminal as fast as the local terminal will allow, and measuring the resulting framerate. This works because terminals have a feedback mechanism to the server that indicates when the terminal is ready to handle more data. Random characters are used to avoid compression effects impacting the estimation of bitrate (ncurses uses compression when sending screens to the local terminal).

Because this relies on ncurses, it will only work on terminals which support ANSI escape sequences. This includes most modern terminals, but not all. It has been tested on xterm and gnome-terminal on Linux, on the Mac OS X Terminal, and on the Windows Command Prompt.

# OPTIONS

-h, \--help
:   Show a brief help message and exit.

-g, \--graph
:   Show a live graph of the measurements.

-b, \--low-bw
:   Low bandwidth mode. This mode is useful for measuring network speed over a slow connection. It uses less data per screen to allow for a reasonable update rate.

-V, \--version
:   Show version information and exit.

-v, \--verbose
:   Show debugging information.

# EXAMPLES

    cspeedtest-int >> log.txt

Measure network speed and log the value to a file.

# DIAGNOSTICS

cspeedtest writes certain diagnostics to *stderr*.

# EXIT STATUS

cspeedtest exits with a status of 0 if it completes successfully. Otherwise, it exits with a status of 1.

# ENVIRONMENT

cspeedtest does not use any environment variables.

# CAVEATS

May not provide accurate measurements over fast connections, as eventually the throughput becomes limited by the terminal speed and not the network. It does, however, provide a fairly good lower bound on the network speed.

# AUTHORS

Jonathan Birge

# BUGS

Please report bugs to bugs@birge.us