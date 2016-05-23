#pragma once

/***
  This file is part of nettools. See COPYING for details.

  nettools is free software; you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation; either version 2.1 of the License, or
  (at your option) any later version.

  nettools is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with nettools; If not, see <http://www.gnu.org/licenses/>.
***/

#include <stdlib.h>

/*
 * Macros
 */

#define _cleanup_(_x) __attribute__((__cleanup__(_x)))
#define _public_ __attribute__((__visibility__("default")))

/*
 * DHCP4 Lease
 */

struct NDhcp4Lease {
        unsigned long n_ref;
};

/*
 * DHCP4 Client
 */

struct NDhcp4Client {
        int unused;
};
