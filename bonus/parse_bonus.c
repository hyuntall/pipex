/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:57:06 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/24 19:53:55 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**get_env_path(char **envp)
{
	char	**path;

	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	path = ft_split(*envp + 5, ':');
	return (path);
}

char	*insert_slash(char *cmd)
{
	char	*tmp;

	if (cmd[0] != '/')
	{
		tmp = cmd;
		cmd = ft_strjoin("/", cmd);
	}
	return (cmd);
}

char	*check_cmd(t_arg *arg, char *cmd, char **path)
{
	int		i;
	char	*abs_path;
	char	*tmp;

	i = -1;
	if (!access(cmd, X_OK))
		return (cmd);
	tmp = insert_slash(cmd);
	while (path[++i])
	{
		abs_path = ft_strjoin(path[i], tmp);
		if (!access(abs_path, X_OK))
		{
			arg->status_code = 0;
			free(cmd);
			free(tmp);
			tmp = 0;
			return (abs_path);
		}
		free(abs_path);
	}
	if (cmd[0] != '/')
		free(tmp);
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
		cmd[0] = check_cmd(arg, cmd[0], arg->path);
		cmd_insert(arg, cmd);
	}
}
