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

#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>
#include "n-dhcp-private.h"
#include "ndhcp/n-dhcp4-lease.h"

_public_ NDhcp4Lease *n_dhcp4_lease_ref(NDhcp4Lease *lease) {
        return lease;
}

_public_ NDhcp4Lease *n_dhcp4_lease_unref(NDhcp4Lease *lease) {
        return NULL;
}
