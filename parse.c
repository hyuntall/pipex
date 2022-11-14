/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:57:06 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/14 20:02:35 by hyuncpar         ###   ########.fr       */
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

char	**get_cmds(int argc, char **argv)
{
	char	**cmds;
	int		i;
	int		j;

	i = -1;
	cmds = (char **)malloc(sizeof(char *) * (argc - 1));
	if (!cmds)
		return (0);
	while (++i + 2 < argc - 1)
	{
		j = 0;
		cmds[i] = (char *)malloc(sizeof(char) * (ft_strlen(argv[i + 2]) + 1));
		if (!cmds[i])
			return (0);
		while (*argv[i + 2])
			cmds[i][j++] = *argv[i + 2]++;
		cmds[i][j] = 0;
		cmds[i] = insert_slash(cmds[i]);
	}
	cmds[i] = 0;
	return (cmds);
}
