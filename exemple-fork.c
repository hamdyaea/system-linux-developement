/*
 * Developer: Hamdy Abou El Anein
 * Contact: hamdy.aea@protonmail.com
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Demonstrate fork() and waitpid() without orphaning a child.
 */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    /* Flush stdio before fork to avoid duplicate buffered output. */
    fflush(NULL);
    pid_t child = fork();
    if (child == -1) {
        perror("fork");
        return EXIT_FAILURE;
    }
    if (child == 0) {
        printf("Child: PID=%ld, PPID=%ld\n", (long)getpid(), (long)getppid());
        fflush(stdout);
        _exit(EXIT_SUCCESS);
    }

    printf("Parent: PID=%ld, child=%ld\n", (long)getpid(), (long)child);
    int status = 0;
    pid_t waited;
    do {
        waited = waitpid(child, &status, 0);
    } while (waited == -1 && errno == EINTR);
    if (waited == -1) {
        perror("waitpid");
        return EXIT_FAILURE;
    }
    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
        fprintf(stderr, "Child did not exit successfully\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}