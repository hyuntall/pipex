/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:52:23 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/23 23:01:22 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	return (arg.status_code);
}
