/***
  This file is part of systemd.

  Copyright 2013 Lennart Poettering

  systemd is free software; you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation; either version 2.1 of the License, or
  (at your option) any later version.

  systemd is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with systemd; If not, see <http://www.gnu.org/licenses/>.
***/

#include <string.h>

#include "errno-list.h"
#include "macro.h"

static const struct errno_name* lookup_errno(register const char *str,
                                             register GPERF_LEN_TYPE len);

#include "errno-from-name.h"
#include "errno-to-name.h"

const char *errno_to_name(int id) {

        if (id < 0)
                id = -id;

        if (id >= (int) ELEMENTSOF(errno_names))
                return NULL;

        return errno_names[id];
}

int errno_from_name(const char *name) {
        const struct errno_name *sc;

        assert(name);

        sc = lookup_errno(name, strlen(name));
        if (!sc)
                return -EINVAL;

        assert(sc->id > 0);
        return sc->id;
}

#if 0 /// UNNEEDED by elogind
int errno_max(void) {
        return ELEMENTSOF(errno_names);
}
#endif // 0
