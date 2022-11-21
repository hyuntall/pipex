/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 21:14:55 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/21 19:58:16 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_file(t_arg *arg, char *filename, int o)
{
	if (o)
	{
		arg->infile = open(filename, O_RDONLY, 0777);
		if (arg->infile < 0)
			print_error(arg, filename, 1);
	}
	else
	{
		arg->outfile = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (arg->outfile < 0)
			print_error(arg, filename, 2);
	}
}

void	free_cmd(char **cmd)
{
	while (*cmd)
		free(*cmd++);
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
		if (arg.infile >= 0 && !cmds.num)
			dup2(arg.infile, 0);
		else if (arg.infile < 0 && !cmds.num)
			exit(1);
		if (!cmds.next && arg.outfile > 0)
			dup2(arg.outfile, 1);
		else
			dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		arg.status_code = 0;
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
	open_file(&arg, arg.infile_name, 1);
	open_file(&arg, arg.outfile_name, 0);
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
	//printf("status code: %d\n", arg.status_code);
}
