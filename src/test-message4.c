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
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "n-dhcp-private.h"

static void test_outgoing(void) {
        NDhcp4Outgoing *outgoing;
        int r;

        /* verify basic NEW/FREE */

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
        uint8_t *v;
        size_t l;
        int r;

        /* verify that messages must be at least the size of the header */

        r = n_dhcp4_incoming_new(&incoming, NULL, 0);
        assert(r < 0);

        r = n_dhcp4_incoming_new(&incoming, NULL, sizeof(m.header) + 64 + 128 + 3);
        assert(r < 0);

        /* verify that magic must be set */

        memset(&m, 0, sizeof(m));
        r = n_dhcp4_incoming_new(&incoming, &m, sizeof(m));
        assert(r < 0);

        /* verify basic NEW/FREE */

        memset(&m, 0, sizeof(m));
        m.magic = htobe32(N_DHCP4_MESSAGE_MAGIC);
        incoming = NULL;
        r = n_dhcp4_incoming_new(&incoming, &m, sizeof(m.header) + 64 + 128 + 4);
        assert(r >= 0);
        assert(incoming);

        incoming = n_dhcp4_incoming_free(incoming);
        assert(!incoming);

        /* verify that PAD is properly handled */

        r = n_dhcp4_incoming_new(&incoming, &m, sizeof(m));
        assert(r >= 0);
        incoming = n_dhcp4_incoming_free(incoming);

        /* verify that SNAME/FILE are only looked at if OVERLOAD is set */

        m.sname[0] = 1;
        m.sname[1] = 0;
        m.file[0] = 2;
        m.file[1] = 0;

        r = n_dhcp4_incoming_new(&incoming, &m, sizeof(m));
        assert(r >= 0);
        r = n_dhcp4_incoming_query(incoming, 1, NULL, NULL);
        assert(r == -ENODATA);
        r = n_dhcp4_incoming_query(incoming, 2, NULL, NULL);
        assert(r == -ENODATA);
        incoming = n_dhcp4_incoming_free(incoming);

        m.options[0] = N_DHCP4_OPTION_OVERLOAD;
        m.options[1] = 1;
        m.options[2] = 0;

        r = n_dhcp4_incoming_new(&incoming, &m, sizeof(m));
        assert(r >= 0);
        r = n_dhcp4_incoming_query(incoming, 1, NULL, NULL);
        assert(r == -ENODATA);
        r = n_dhcp4_incoming_query(incoming, 2, NULL, NULL);
        assert(r == -ENODATA);
        incoming = n_dhcp4_incoming_free(incoming);

        m.options[0] = N_DHCP4_OPTION_OVERLOAD;
        m.options[1] = 1;
        m.options[2] = N_DHCP4_OVERLOAD_SNAME;

        r = n_dhcp4_incoming_new(&incoming, &m, sizeof(m));
        assert(r >= 0);
        r = n_dhcp4_incoming_query(incoming, 1, NULL, NULL);
        assert(r == 0);
        r = n_dhcp4_incoming_query(incoming, 2, NULL, NULL);
        assert(r == -ENODATA);
        incoming = n_dhcp4_incoming_free(incoming);

        m.options[0] = N_DHCP4_OPTION_OVERLOAD;
        m.options[1] = 1;
        m.options[2] = N_DHCP4_OVERLOAD_FILE;

        r = n_dhcp4_incoming_new(&incoming, &m, sizeof(m));
        assert(r >= 0);
        r = n_dhcp4_incoming_query(incoming, 1, NULL, NULL);
        assert(r == -ENODATA);
        r = n_dhcp4_incoming_query(incoming, 2, NULL, NULL);
        assert(r == 0);
        incoming = n_dhcp4_incoming_free(incoming);

        m.options[0] = N_DHCP4_OPTION_OVERLOAD;
        m.options[1] = 1;
        m.options[2] = N_DHCP4_OVERLOAD_FILE | N_DHCP4_OVERLOAD_SNAME;

        r = n_dhcp4_incoming_new(&incoming, &m, sizeof(m));
        assert(r >= 0);
        r = n_dhcp4_incoming_query(incoming, 1, NULL, NULL);
        assert(r == 0);
        r = n_dhcp4_incoming_query(incoming, 2, NULL, NULL);
        assert(r == 0);
        incoming = n_dhcp4_incoming_free(incoming);

        /* verify basic concatenation */

        m.options[3] = 1;
        m.options[4] = 1;
        m.options[5] = 0xef;
        m.sname[1] = 1;
        m.sname[2] = 0xcf;

        r = n_dhcp4_incoming_new(&incoming, &m, sizeof(m));
        assert(r >= 0);
        r = n_dhcp4_incoming_query(incoming, 1, (const void **)&v, &l);
        assert(r == 0);
        assert(l == 2);
        assert(v[0] == 0xef && v[1] == 0xcf);
        incoming = n_dhcp4_incoming_free(incoming);
}

int main(int argc, char **argv) {
        test_outgoing();
        test_incoming();
        return 0;
}
