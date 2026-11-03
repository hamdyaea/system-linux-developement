/*
 * Developer: Hamdy Abou El Anein
 * Contact: hamdy.aea@protonmail.com
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Demonstrate POSIX real/effective UID and dropping privileges.
 */
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    const uid_t real_uid = getuid();
    const uid_t effective_uid = geteuid();

    printf("Before: real UID=%lu, effective UID=%lu\n",
           (unsigned long)real_uid, (unsigned long)effective_uid);

    /* Never attempt to regain elevated privileges. The example is safe to
     * run as an ordinary user and must NOT be installed setuid-root. */
    if (setuid(real_uid) == -1) {
        fprintf(stderr, "setuid(%lu) failed: %s\n",
                (unsigned long)real_uid, strerror(errno));
        return 1;
    }

    printf("After: real UID=%lu, effective UID=%lu\n",
           (unsigned long)getuid(), (unsigned long)geteuid());
    return 0;
}