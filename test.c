#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int	main()
{
	pid_t	pid;

	pid = fork();
	printf("pid: %d\n", pid);
	usleep(1000);
	pid	= fork();
	printf("pid: %d\n", pid);
	usleep(1);
}
