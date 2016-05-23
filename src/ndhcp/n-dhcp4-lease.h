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

/*
 * XXX
 */

#include <inttypes.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

struct in_addr;

typedef struct NDhcp4Lease NDhcp4Lease;

NDhcp4Lease *n_dhcp4_lease_ref(NDhcp4Lease *lease);
NDhcp4Lease *n_dhcp4_lease_unref(NDhcp4Lease *lease);

/* inline helpers */

static inline void n_dhcp4_lease_unrefp(NDhcp4Lease **lease) {
        if (*lease)
                n_dhcp4_lease_unref(*lease);
}

#ifdef __cplusplus
}
#endif
