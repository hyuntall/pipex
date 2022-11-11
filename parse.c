/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:57:06 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/11 21:19:54 by hyuncpar         ###   ########.fr       */
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
		j = 1;
		cmds[i] = (char *)malloc(sizeof(char) * (ft_strlen(argv[i + 2]) + 2));
		if (!cmds[i])
			return (0);
		cmds[i][0] = '/';
		while (*argv[i + 2])
			cmds[i][j++] = *argv[i + 2]++;
		cmds[i][j] = 0;
	}
	cmds[i] = 0;
	return (cmds);
}
