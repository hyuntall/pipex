/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 21:14:55 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/21 23:06:56 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_cmd(char **cmd)
{
	while (*cmd)
		free(*cmd++);
}

void	here_doc(t_arg arg, int *fd)
{
	char* line;
	int i;

	dup2(fd[1], 1);
    line = get_next_line(0);			// 1
    while (line && ft_strncmp(line, arg.limit, ft_strlen(arg.limit)))
    {
    	printf("Gnl %d line : %s", i++, line);	
        free(line);
    	line = get_next_line(0);
    }
    printf("\n");
    free(line);
	printf("sadda\n");
	close(fd[1]);
	close(fd[0]);
}

void	repipex(t_arg arg, t_cmds cmds, int in)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (pid)
	{
		dup2(fd[0], 0);
		close(fd[1]);
		close(fd[0]);
		waitpid(pid, NULL, WNOHANG);
	}
	else
	{
		if (access(cmds.cmd[0], X_OK))
			exit(127);
		if (arg.here_doc == 1 && !cmds.num)
		{
			here_doc(arg, fd);
			printf("asdsa\n");
		}
		else if (arg.infile >= 0 && !cmds.num)
			dup2(arg.infile, 0);
		else if (arg.infile < 0 && !cmds.num)
			exit(1);
		if (!cmds.next && arg.outfile > 0)
			dup2(arg.outfile, 1);
		else
			dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execve(cmds.cmd[0], cmds.cmd, arg.envp);
	}
}

void	pipex(t_arg arg)
{
	int		fd[2];
	int		pipes;
	pid_t	pid;
	t_cmds	*cmds;
	int		i;

	i = 1;
	cmds = arg.cmd_head;
	pid = fork();
	while (wait(&pid) != -1)
	{
		while (!pid && cmds)
		{
			repipex(arg, *cmds, 1);
			cmds = cmds->next;
		}
	}
	close(arg.infile);
	close(arg.outfile);
}
