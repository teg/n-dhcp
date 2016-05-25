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
 * Tests for DHCP4 Message Handling
 */

#undef NDEBUG
#include <assert.h>
#include <endian.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "n-dhcp-private.h"

static void test_outgoing(void) {
        NDhcp4Outgoing *outgoing;
        int r;

        outgoing = NULL;
        r = n_dhcp4_outgoing_new(&outgoing, 0, 0);
        assert(r >= 0);
        assert(outgoing);

        outgoing = n_dhcp4_outgoing_free(outgoing);
        assert(!outgoing);
}

static void test_incoming(void) {
        NDhcp4Incoming *incoming;
        struct {
                NDhcp4Header header;
                uint8_t sname[64];
                uint8_t file[128];
                uint32_t magic;
                uint8_t options[1024];
        } m;
        int r;

        r = n_dhcp4_incoming_new(&incoming, NULL, 0);
        assert(r < 0);

        memset(&m, 0, sizeof(m));
        r = n_dhcp4_incoming_new(&incoming, &m, sizeof(m));
        assert(r < 0);

        memset(&m, 0, sizeof(m));
        m.magic = htobe32(N_DHCP4_MESSAGE_MAGIC);
        incoming = NULL;
        r = n_dhcp4_incoming_new(&incoming, &m, sizeof(m));
        assert(r >= 0);
        assert(incoming);

        incoming = n_dhcp4_incoming_free(incoming);
        assert(!incoming);
}

int main(int argc, char **argv) {
        test_outgoing();
        test_incoming();
        return 0;
}
