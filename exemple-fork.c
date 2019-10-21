#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>

int main (void)
{
	pid_t child_pid;
	do {
	child_pid = fork ();
	} while ((child_pid == -1) && (errno == EAGAIN));
if (child_pid == -1) {
	fprintf(stderr, "unable to fork(), errno=%d\n", errno);
	return 1;
}
if (child_pid == 0) { /* child */
	fprintf(stdout, "Child: PID=%ld\n",
			(long)getpid(), (long)getpid());
	return 0;
} else { /* parent */
	fprintf(stdout, "Parent: PID=%ld; PPID=%ld, child=%ld\n",
			(long)getpid(),(long)getpid(),(long)child_pid);
	return 0;
}
}
