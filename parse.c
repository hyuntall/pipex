/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:57:06 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/16 19:16:17 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_env_path(char **envp)
{
	char	**path;

	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	path = ft_split(*envp + 5, ':');
	return (path);
}

void	free_cmds(char **cmds)
{
	int		i;

	i = -1;
	while (cmds[++i])
		free(cmds[i]);
	free(cmds);
}

char	*insert_slash(char *cmd)
{
	char	*tmp;

	if (cmd[0] != '/')
	{
		tmp = cmd;
		cmd = ft_strjoin("/", cmd);
		free(tmp);
	}
	return (cmd);
}

char	*check_cmd(char *cmd, char **path)
{
	int		i;
	char	*abs_path;

	i = -1;
	if (!access(cmd, X_OK))
		return (cmd);
	cmd = insert_slash(cmd);
	while (path[++i])
	{
		abs_path = ft_strjoin(path[i], cmd);
		if (!access(abs_path, X_OK))
			return (abs_path);
		free(abs_path);
	}
	//print_error(cmd + 1, 127);
	return (cmd);
}

void	parse_cmds(t_arg *arg, int argc, char **argv)
{
	char	**cmd;
	int		i;
	int		check;
	t_cmds	*cmds;

	i = -1;
	while (++i + 2 < argc - 1)
	{
		cmd = ft_split(argv[i + 2], ' ');
		cmd[0] = check_cmd(cmd[0], arg->path);
		cmd_insert(arg, cmd);
	}
}
