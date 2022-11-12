#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int	main(int argc, char *argv[], char *envp[])
{
	int	pid;
	int	fd1;
	int	fd[2];
	char	**grep;
	char	**wc;
	int	pipe1;
	int	status;

	argv = 0;
	argc = 0;
	grep = (char **)malloc(sizeof(char *) * 3);
	grep[0] = strdup("/usr/bin/grep");
	grep[1] = strdup("a");
	grep[2] = 0;
	wc = (char **)malloc(sizeof(char *) * 3);
	wc[0] = strdup("/usr/bin/wc");
	wc[1] = strdup("-l");
	wc[2] = 0;
	fd1 = open("./infile", O_RDONLY);
	pipe1 = pipe(fd);
	dup2(fd1, 0);
	close(fd1);
	pid = fork();
	if (pid > 0)
	{
		printf("parent\n");
		//fd1 = open("./outfile", O_WRONLY);
		dup2(fd[0], 0);
		//dup2(fd1, 1);
		//close(fd1);
		close(fd[1]);
		close(fd[0]); 
		waitpid(pid, &status, 0);
		execve("/usr/bin/wc", wc, envp);
	}
	else
	{
		printf("child\n");
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execve("/usr/bin/grep", grep, envp);
	}
}