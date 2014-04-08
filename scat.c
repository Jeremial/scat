/**
 * Copyright (c) 2013 by Jeremial (jeremial90@gmail.com)
 * All Rights reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>
#include "deps/commander/commander.h"

#define PACKAGE_NAME "scat"
#define VERSION "1.0.1"
/* Change this to 8 if you want a true bps / character, and not a modem simulation */
#define BITS_PER_CHAR 8
#define BPS 100

struct timespec delay;

int bits_per_char = BITS_PER_CHAR;
int bps = BPS;

void
on_bits_per_char(command_t *self){
    bits_per_char = atoi(self->arg);
}

void
on_bps(command_t *self){
    bps = atoi(self->arg);
}

int
main(int argc, char **argv) {

    command_t program;
    command_init(&program, argv[0], VERSION);
    program.usage = "[options] [file]";
    command_option(&program, "-b", "--bits <bits>", "bits per char, default to 8", on_bits_per_char);
    command_option(&program, "-s", "--bps <bps>", "print speed(bps), default to 100", on_bps);
    command_parse(&program, argc, argv);

    if(bps < 1){
        fprintf(stderr, "bps rate [%d] not a positive integer.\n", bps);
        exit(EXIT_FAILURE);
    }else if (bps > bits_per_char) {
        delay.tv_sec = 0;
        delay.tv_nsec = 1000000000 / bps * bits_per_char;
    } else {
        delay.tv_sec = bits_per_char / bps;
        delay.tv_nsec = (long)(1000000000 * (bits_per_char / (double)bps - delay.tv_sec));
    }

    setbuf(stdout, 0);

    char ch;
    if (program.argc) { /* scat from local files */
        char *file = NULL;
        int i;
        FILE *fd;
        for (i = 0; i < program.argc; ++i) {
            file = program.argv[i];
            if ((fd = fopen(file, "r")) == NULL) {
                fprintf(stderr, "could not open %s for reading.\n", file);
            }
            while ((ch = fgetc(fd)) != EOF) {
                nanosleep(&delay, NULL);
                putchar(ch);
            }
            fclose(fd);
            putchar('\n'); /* start new line */
        }
    } else { /* scat from stdin */
        while ((ch = fgetc(stdin)) != EOF) {
            nanosleep(&delay, NULL);
            putchar(ch);
        }
    }
    return EXIT_SUCCESS;
}