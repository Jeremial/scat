scat
===
Slow cat.  Prints stuff out slowly, as if using an old modem/serial connection.

Scat stands for 'slow cat'.

Basically 'cats' the file or stdin to the screen at a specified number of
bits per second, as if you were using a modem or slow serial connection.

Usage:
---

    scat --help

    Usage: ./scat [options] [file]

    Options:

      -V, --version                 output program version
      -h, --help                    output help information
      -b, --bits <bits>             bits per char, default to 8
      -s, --bps <bps>               print speed(bps), default to 100

Install:
---

    make

then excute `./scat` with your options
