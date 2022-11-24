/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:52:23 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/24 20:11:39 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_path(char **path)
{
	char	**tmp;

	tmp = path;
	while (*path)
		free(*path++);
	free(tmp);
}

void	free_cmd(t_arg *arg)
{
	t_cmds	*cmds;
	t_cmds	*temp;
	char	**tmp;

	cmds = arg->cmd_head;
	while (cmds)
	{
		temp = cmds;
		tmp = cmds->cmd;
		while (*cmds->cmd)
			free(*cmds->cmd++);
		free(tmp);
		cmds = cmds->next;
		free(temp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_arg	arg;
	int		files[2];

	arg.status_code = 0;
	if (argc != 5)
	{
		write(2, "Not 5 ARG!\n", 11);
		exit(1);
	}
	arg.infile_name = argv[1];
	arg.outfile_name = argv[argc - 1];
	arg.cmd_head = 0;
	arg.envp = envp;
	arg.path = get_env_path(envp);
	parse_cmds(&arg, argc, argv);
	pipex(&arg);
	free_path(arg.path);
	free_cmd(&arg);
	return (arg.status_code);
}
