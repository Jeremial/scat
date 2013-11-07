scat
===
Slow cat.  Prints stuff out slowly, as if using an old modem/serial connection.

Scat stands for 'slow cat'.

Basically 'cats' the file or stdin to the screen at a specified number of
bits per second, as if you were using a modem or slow serial connection.

Usage:
---

    % scat -h
    Usage: scat [--bits=<bits>] [--help] [--speed=<speed>]
                [--version] [<file1> <file2> ...]
    options:
      -b, --bits=<bit>: bits per char, default to 8
      -h, --help: print this help
      -s, --speed=<speed>: print speed(bps), default to 100
      -v, --version: version

Install:
---

    make
    sudo make install

Uninstall:
---

    sudo make uninstall