/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 21:14:55 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/16 20:25:33 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	find_cmd(char *cmd, char **path)
{
	int		i;
	char	*abs_path;

	i = -1;
	if (!access(cmd, X_OK))
		return (-2);
	cmd = insert_slash(cmd);
	while (path[++i])
	{
		abs_path = ft_strjoin(path[i], cmd);
		if (!access(abs_path, X_OK))
		{
			free(abs_path);
			return (i);
		}
		free(abs_path);
	}
	return (-1);
}

void	free_cmd(char **cmd)
{
	while (*cmd)
		free(*cmd++);
}

void	p_process(t_arg arg, int pid, int *fd, char **cmd)
{
	int		state;
	char	*tmp;
	int		i;

	dup2(fd[0], 0);
	dup2(arg.outfile, 1);
	close(fd[1]);
	close(fd[0]);
	close(arg.outfile);
	waitpid(pid, &state, WNOWAIT);
	if (access(cmd[0], X_OK) < 0)
		print_error(cmd[0] + 1, 127);
	execve(cmd[0], cmd, arg.envp);
}

void	c_process(t_arg arg, int pid, int *fd, char **cmd)
{
	int		state;
	char	*tmp;
	int		i;

	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	if (access(cmd[0], X_OK) < 0)
		print_error(cmd[0] + 1, 127);
	execve(cmd[0], cmd, arg.envp);
}

void	recurs_pipe(t_arg arg, int state, t_cmds cmds, int *fd)
{
	printf("%d %d %s\n",  cmds.num, state, cmds.cmd[0]);
	if (cmds.num == 0)
	{
		printf("first!\n");
		dup2(arg.infile, 0);
		close(arg.infile);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
	}
	else if (!cmds.next)
	{
		printf("last!\n");
		dup2(fd[0], 0);
		dup2(arg.outfile, 1);
		close(fd[1]);
		close(fd[0]);
		close(arg.outfile);
	}
	else
	{
		printf("middle\n");
		dup2(fd[0], 0);
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
	}
	//close(fd[1 - state]);
	if (access(cmds.cmd[0], X_OK) < 0)
		print_error(cmds.cmd[0] + 1, 127);
	execve(cmds.cmd[0], cmds.cmd, arg.envp);
}

void	pipex(t_arg arg, int infile, int outfile)
{
	int		fd[2];
	int		pipes;
	int		pid;
	t_cmds	*cmds;
	int		i;
	int		state;

	i = 1;
	cmds = arg.cmd_head;
	pipes = pipe(fd);
	//dup2(infile, 0);
	//close(infile);
	while (cmds)
	{
		pid = fork();
		if (!pid)
		{
			recurs_pipe(arg, i % 2, *cmds, fd);
		}
		waitpid(pid, &state, WNOWAIT);
		cmds = cmds->next;
		i++;
	}
	/*
	pid = fork();
	if (pid > 0)
	{
		cmds = cmds->next;
		p_process(arg, pid, fd, cmds->cmd);
	}
	else
		c_process(arg, pid, fd, cmds->cmd);
		*/
}
