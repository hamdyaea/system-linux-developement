#include <stdio.h>
#include <unistd.h>

int main(void)
{
	fprintf(stdout, " Real-UID = %u, Effective-UID = %u\n",
			getuid(), geteuid());
        return 0;
}
