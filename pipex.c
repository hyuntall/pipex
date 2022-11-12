/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 21:14:55 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/12 22:20:30 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	find_cmd(char *cmd, char **path)
{
	int		i;
	char	*abs_path;

	i = -1;
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

void	pipex(t_arg arg, int infile, int outfile)
{
	char	**cmd;
	int		i;
	char	*temp;
	int		fd[2];
	int		pipes;
	int		pid;
	int		status;

	if (!*arg.cmd)
		return ;
	pipes = pipe(fd);
	dup2(infile, 0);
	close(infile);
	pid = fork();
	if (pid > 0)
	{
		arg.cmd++;
		dup2(fd[0], 0);
		dup2(outfile, 1);
		close(fd[1]);
		close(fd[0]);
		close(outfile);
		waitpid(pid, &status, 0);
		cmd = ft_split(*arg.cmd, ' ');
		i = find_cmd(cmd[0], arg.path);
		if (i >= 0)
		{
			temp = cmd[0];
			cmd[0] = ft_strjoin(arg.path[i], cmd[0]);
			free(temp);
			execve(cmd[0], cmd, NULL);
		}
		else
			exit(1);
		free_cmd(cmd);
	}
	else
	{
		cmd = ft_split(*arg.cmd, ' ');
		i = find_cmd(cmd[0], arg.path);
		if (i >= 0)
		{
			dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
			temp = cmd[0];
			cmd[0] = ft_strjoin(arg.path[i], cmd[0]);
			free(temp);
			execve(cmd[0], cmd, NULL);
		}
		else
			exit(1);
		free_cmd(cmd);
	}
}
