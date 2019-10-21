#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main (void)
{
	uid_t uid_reel;
	uid_t uid_eff;
	r_uid = getuid();
	e_uid = geteuid();
	fprintf(stdout, " R-UID = %u, E-UID = %u\n",
			getuid(), geteuid());
	fprintf(stdout, " setuid(%d) = %d\n",
			r_uid, setuid(r_uid));
	fprintf(stdout, "setuid(%d) = %d\n",
			e_uid, setuid(e_uid));
	fprintf(stdout, " R-UID = %u, E-UID = %u\n",
		getuid(), geteuid());
	return 0;
}
