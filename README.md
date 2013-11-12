scat
===
Slow cat.  Prints stuff out slowly, as if using an old modem/serial connection.

Scat stands for 'slow cat'.

Basically 'cats' the file or stdin to the screen at a specified number of
bits per second, as if you were using a modem or slow serial connection.

Usage:
---

    % scat -h
    Usage: scat [-hv] [-b bits] [-s bps] [file ...]
    options:
      -b bits ,  --bits=<bits> : bits per char, default to 8
      -h      ,  --help        : print this help
      -s bps  ,  --speed=<bps> : print speed(bps), default to 100
      -v      ,  --version     : version
    Report bugs to <jeremial90@gmail.com>

Install:
---

    make
    sudo make install

Uninstall:
---

    sudo make uninstall