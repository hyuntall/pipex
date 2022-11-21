/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:52:23 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/21 19:37:45 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/errno.h>

int	main(int argc, char **argv, char **envp)
{
	t_arg	arg;
	int		files[2];

	arg.status_code = 0;
	if (argc != 5)
	{
		print_error(&arg, "Not 5 ARG!", 1);
		exit(1);
	}
	arg.infile_name = argv[1];
	arg.outfile_name = argv[argc - 1];
	arg.cmd_head = 0;
	arg.envp = envp;
	arg.path = get_env_path(envp);
	parse_cmds(&arg, argc, argv);
	pipex(arg);
	exit(arg.status_code);
}
