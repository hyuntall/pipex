#include <unistd.h>
#include <fcntl.h>
int main(int argc, char **argv)
{
	int	fildes[2];
	int	fd;

	if (argc == 1)
		return (0);
	fd = open(argv[1], O_RDONLY);
	dup2(fd, 1);
	pipe(fildes);
	close(fildes[0]);
	dup2(fildes[1], 1);
	execl("/bin/cat", "/bin/cat", NULL);
	return (1);
}