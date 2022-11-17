/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 21:14:55 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/17 20:03:02 by hyuncpar         ###   ########.fr       */
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

void	repipex(t_arg arg, char **cmd, int in)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (pid)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		waitpid(pid, NULL, WNOHANG);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], 1);
		if (!in)
			exit(1);
		else
			execve(cmd[0], cmd, arg.envp);
		exit(127);
	}
}

void	pipex(t_arg arg)
{
	int		fd[2];
	int		pipes;
	int		pid;
	t_cmds	*cmds;
	int		i;

	i = 1;
	cmds = arg.cmd_head;
	dup2(arg.infile, 0);
	dup2(arg.outfile, 1);
	repipex(arg, cmds->cmd, arg.infile);
	cmds = cmds->next;
	while (cmds->next)
	{
		repipex(arg, cmds->cmd, 1);
		cmds = cmds->next;
	}
	execve(cmds->cmd[0], cmds->cmd, arg.envp);
}
