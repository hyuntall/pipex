/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 21:14:55 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/14 21:03:03 by hyuncpar         ###   ########.fr       */
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

void	p_process(t_arg arg, int pid, int *fd)
{
	int		state;
	char	**cmd;
	char	*tmp;
	int		i;

	dup2(fd[0], 0);
	dup2(arg.outfile, 1);
	close(fd[1]);
	close(fd[0]);
	close(arg.outfile);
	waitpid(pid, &state, WNOWAIT);
	cmd = ft_split(*arg.cmd, ' ');
	i = find_cmd(cmd[0], arg.path);
	if (i >= 0)
	{
		tmp = cmd[0];
		cmd[0] = ft_strjoin(arg.path[i], cmd[0]);
		free(tmp);
		execve(cmd[0], cmd, arg.envp);
	}
	else if (i == -2)
		execve(cmd[0], cmd, arg.envp);
	else
		print_error(cmd[0], 127);
	free_cmd(cmd);
}

void	c_process(t_arg arg, int pid, int *fd)
{
	int		state;
	char	**cmd;
	char	*tmp;
	int		i;

	cmd = ft_split(*arg.cmd, ' ');
	i = find_cmd(cmd[0], arg.path);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	if (i >= 0)
	{
		tmp = cmd[0];
		cmd[0] = ft_strjoin(arg.path[i], cmd[0]);
		free(tmp);
		execve(cmd[0], cmd, arg.envp);
	}
	else if (i == -2)
		execve(cmd[0], cmd, arg.envp);
	else
		print_error(cmd[0], 127);
	free_cmd(cmd);
}

void	pipex(t_arg arg, int infile, int outfile)
{
	int		fd[2];
	int		pipes;
	int		pid;

	if (!*arg.cmd)
		return ;
	pipes = pipe(fd);
	dup2(infile, 0);
	close(infile);
	pid = fork();
	if (pid > 0)
	{
		arg.cmd++;
		p_process(arg, pid, fd);
	}
	else
		c_process(arg, pid, fd);
}
