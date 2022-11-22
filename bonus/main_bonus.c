/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:52:23 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/22 18:33:28 by hyuncpar         ###   ########.fr       */
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

	if (argc < 5)
	{
		write(2, "Not 5 ARG!\n", 11);
		exit(1);
	}
	arg.status_code = 0;
	arg.infile_name = argv[1];
	if (!ft_strcmp(arg.infile_name, "here_doc"))
	{
		arg.limit = argv[2];
		argv++;
		argc--;
		arg.here_doc = 1;
		arg.infile = here_doc(arg);
	}
	else
		open_file(&arg, arg.infile_name, 1);
	if (argc < 5)
	{
		write(2, "Not 5 ARG!\n", 11);
		exit(1);
	}
	arg.outfile_name = argv[argc - 1];
	open_file(&arg, arg.outfile_name, 0);
	arg.cmd_head = 0;
	arg.envp = envp;
	arg.path = get_env_path(envp);
	parse_cmds(&arg, argc, argv);
	pipex(arg);
	exit(arg.status_code);
}
