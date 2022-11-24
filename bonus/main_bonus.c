/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:52:23 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/24 20:11:32 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_argc(int argc, int here_doc)
{
	if (argc < 5)
	{
		if (here_doc)
			unlink("here_doc");
		write(2, "ARG ERROR!\n", 11);
		exit(1);
	}
}

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

void	free_all(t_arg *arg)
{
	free_path(arg->path);
	free_cmd(arg);
}

int	main(int argc, char **argv, char **envp)
{
	t_arg	arg;
	int		files[2];

	check_argc(argc, 0);
	arg.status_code = 0;
	arg.infile_name = argv[1];
	arg.outfile_name = argv[argc - 1];
	if (!ft_strcmp(arg.infile_name, "here_doc"))
	{
		arg.limit = argv[2];
		argv++;
		argc--;
		arg.here_doc = 1;
		here_doc(arg, argc - 4);
	}
	check_argc(argc, arg.here_doc);
	arg.cmd_head = 0;
	arg.envp = envp;
	arg.path = get_env_path(envp);
	parse_cmds(&arg, argc, argv);
	pipex(&arg);
	if (arg.here_doc)
		unlink("here_doc");
	free_all(&arg);
	return (arg.status_code);
}
