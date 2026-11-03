/*
 * Developer: Hamdy Abou El Anein
 * Contact: hamdy.aea@protonmail.com
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Display real and effective user IDs without modifying privileges.
 */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    printf("Real UID=%lu, Effective UID=%lu\n",
           (unsigned long)getuid(), (unsigned long)geteuid());
    return 0;
}