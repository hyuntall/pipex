/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:52:23 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/23 22:43:03 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	arg.outfile_name = argv[argc - 1];
	if (!ft_strcmp(arg.infile_name, "here_doc"))
	{
		arg.limit = argv[2];
		argv++;
		argc--;
		arg.here_doc = 1;
		here_doc(arg, argc - 4);
	}
	if (argc < 5)
	{
		write(2, "Not 5 ARG!\n", 11);
		exit(1);
	}
	arg.cmd_head = 0;
	arg.envp = envp;
	arg.path = get_env_path(envp);
	parse_cmds(&arg, argc, argv);
	pipex(&arg);
	if (arg.here_doc)
		unlink("here_doc");
	return (arg.status_code);
}
