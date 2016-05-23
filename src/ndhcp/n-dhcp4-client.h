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

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct NDhcp4Client NDhcp4Client;

int n_dhcp4_client_new(NDhcp4Client **clientp);
NDhcp4Client *n_dhcp4_client_free(NDhcp4Client *client);

/* inline helpers */

static inline void n_dhcp4_client_freep(NDhcp4Client **client) {
        if (*client)
                n_dhcp4_client_free(*client);
}

#ifdef __cplusplus
}
#endif
