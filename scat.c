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

#include "scat.h"

const char *short_opt = "b:hs:v";

const struct option long_opt[] = {
    {"bits",    required_argument,  NULL,   'b'},
    {"help",    no_argument,        NULL,   'h'},
    {"speed",   required_argument,  NULL,   's'},
    {"version", no_argument,        NULL,   'v'},
    {NULL,      0,                  NULL,   0}
};

void usage(void) {
    printf("Usage: %s [-hv] [-b bits] [-s bps] [file ...]\n", PACKAGE_NAME);
    printf("options:\n"
           "  -b bits ,  --bits=<bits> : bits per char, default to 8\n"
           "  -h      ,  --help        : print this help\n"
           "  -s bps  ,  --speed=<bps> : print speed(bps), default to 100\n"
           "  -v      ,  --version     : version\n");
}

void version(void){
    printf("%s version %s\n", PACKAGE_NAME, VERSION);
}

void bugs(void){
    printf("Report bugs to <%s>\n", BUGREPORT);
}

int main(int argc, char **argv) {
    char c = 0, ch;
    char *file_name = NULL;
    int bits_per_char = BITS_PER_CHAR;
    int bps = BPS;
    int i;
    struct timespec delay;
    FILE *fd;

    setbuf(stdout, 0);

    while ((c = getopt_long(argc, argv, short_opt, long_opt, NULL)) != -1) {
        switch (c) {
        case 'b':
            bits_per_char = atoi(optarg);
            break;
        case 'h':
        case '?':
            usage();
            bugs();
            exit(EXIT_SUCCESS);
            break;
        case 's':
            bps = atoi(optarg);
            break;
        case 'v':
            version();
            exit(EXIT_SUCCESS);
            break;
        default:
            usage();
            bugs();
            exit(EXIT_FAILURE);
            break;
        }
    }

    if (bps < 1) {
        fprintf(stderr, "%s: bps rate [%d] not a positive integer.\n", PACKAGE_NAME, bps);
        exit(EXIT_FAILURE);
    }else if (bps > bits_per_char) {
        delay.tv_sec = 0;
        delay.tv_nsec = 1000000000 / bps * bits_per_char;
    } else {
        delay.tv_sec = bits_per_char / bps;
        delay.tv_nsec = (long)(1000000000 * (bits_per_char / (double)bps - delay.tv_sec));
    }

    argc -= optind;
    argv += optind;

    if (argc) { /* scat from local files */
        for (i = 0; i < argc; ++i) {
            file_name = argv[i];
            if ((fd = fopen(file_name, "r")) == NULL) {
                fprintf(stderr, "%s: could not open %s for reading.\n", PACKAGE_NAME, file_name);
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