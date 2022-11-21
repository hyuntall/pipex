/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:52:23 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/21 22:36:09 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	open_file(t_arg *arg, char *filename, int o)
{
	if (o)
	{
		arg->infile = open(filename, O_RDONLY, 0777);
		if (arg->infile < 0)
			print_error(arg, filename, 1);
	}
	else
	{
		arg->outfile = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (arg->outfile < 0)
			print_error(arg, filename, 2);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_arg	arg;
	int		files[2];

	arg.status_code = 0;
	arg.infile_name = argv[1];
	if (!ft_strncmp(arg.infile_name, "here_doc", 8))
	{
		arg.limit = argv[2];
		argv++;
		argc--;
		arg.here_doc = 1;
	}
	else
		open_file(&arg, arg.infile_name, 1);
	arg.outfile_name = argv[argc - 1];
	open_file(&arg, arg.outfile_name, 0);
	arg.cmd_head = 0;
	arg.envp = envp;
	arg.path = get_env_path(envp);
	parse_cmds(&arg, argc, argv);
	pipex(arg);
	exit(arg.status_code);
}
