/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:52:23 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/10 17:21:31 by hyuncpar         ###   ########.fr       */
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

char	*join_cmds(char	**argv)
{
	char	*str;
	char	*tmp;
	int		i;

	i = 0;
	str = ft_strdup("");
	if (!str)
		return (0);
	while (argv[++i])
	{
		tmp = str;
		str = ft_strjoin(str, argv[i]);
		free(tmp);
		tmp = str;
		str = ft_strjoin(str, " ");
		free(tmp);
	}
	return (str);
}

char	**get_cmds(char **argv)
{
	char	**cmds;
	char	*str;
	
	str = join_cmds(argv);
	cmds = ft_split(str, ' ');
	free(str);
	if (!cmds)
		return (0);
	return (cmds);
}

int	main(int argc, char **argv, char **envp)
{
	t_arg	arg;

	if (argc != 5)
		print_error("Not 5 ARG!");
	arg.infile = open(argv[1], O_RDONLY);
	if (arg.infile < 0)
		print_error("infile error");
	arg.path = get_env_path(envp);
	while (*arg.path)
	{
		printf("%s\n", *arg.path++);
	}
	arg.cmd = get_cmds(argv);
	while (*arg.cmd)
	{
		printf("??%s\n", *arg.cmd++);
	}
}
