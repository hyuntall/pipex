#include <unistd.h>

int	main(int argc, char **argv)
{
	char *envp[] = {0};
	argc = 0;
	execve("/bin/ls", argv, envp);
	return (0);
}