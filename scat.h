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

#ifndef SCAT_H
#define SCAT_H

#define PACKAGE_NAME "scat"

#define VERSION "1.0.0"

/* Change this to 8 if you want a true bps / character, and not a modem simulation */
#define BITS_PER_CHAR 8

#define SPEED_BPS 100

void usage(int mode);

#endif