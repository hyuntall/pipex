/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 21:14:55 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/24 15:54:56 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	open_file(t_arg *arg, char *filename, int isinfile)
{
	if ((isinfile && !access(filename, F_OK) && access(filename, R_OK)) || \
	(!isinfile && !access(filename, F_OK) && access(filename, W_OK)))
	{
		arg->status_code = 1;
		return (2);
	}
	if (isinfile)
	{
		arg->infile = open(filename, O_RDONLY, 0777);
		if (arg->infile < 0)
		{
			arg->status_code = 1;
			return (1);
		}
	}
	else
	{
		arg->outfile = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (arg->outfile < 0)
		{
			arg->status_code = 1;
			return (1);
		}
	}
	return (0);
}

void	process_child(t_arg *arg, t_cmds cmds, int *fd, int open_error)
{
	if (!cmds.num)
	{
		if (open_error)
			print_error(arg, arg->infile_name, open_error);
		dup2(arg->infile, 0);
	}
	if (!cmds.next)
	{
		if (open_error)
			print_error(arg, arg->outfile_name, open_error);
		dup2(arg->outfile, 1);
	}
	else
		dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	execve(cmds.cmd[0], cmds.cmd, arg->envp);
	print_error(arg, cmds.cmd[0], 127);
}

void	repipex(t_arg *arg, t_cmds cmds, int in)
{
	pid_t	pid;
	int		fd[2];
	int		is_opened;
	int		status;

	if (!cmds.num)
		is_opened = open_file(arg, arg->infile_name, 1);
	if (access(cmds.cmd[0], X_OK))
		arg->status_code = 127;
	else
		arg->status_code = 0;
	if (!cmds.next)
		is_opened = open_file(arg, arg->outfile_name, 0);
	pipe(fd);
	pid = fork();
	if (pid)
	{
		dup2(fd[0], 0);
		close(fd[1]);
		close(fd[0]);
		waitpid(pid, &status, WNOHANG);
	}
	else
		process_child(arg, cmds, fd, is_opened);
}

void	pipex(t_arg *arg)
{
	int		fd[2];
	int		pipes;
	pid_t	pid;
	t_cmds	*cmds;
	int		i;

	i = 1;
	cmds = arg->cmd_head;
	pid = fork();
	while (wait(NULL) != -1)
	{
		while (cmds)
		{
			repipex(arg, *cmds, 1);
			cmds = cmds->next;
		}
	}
	if (!pid)
		exit(0);
	close(arg->infile);
	close(arg->outfile);
}
