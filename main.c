/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:52:23 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/16 19:42:05 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/errno.h>

int	main(int argc, char **argv, char **envp)
{
	t_arg	arg;
	int		files[2];

	if (argc < 3)
		print_error("Not 5 ARG!", 1);
	arg.infile = open(argv[1], O_RDONLY, 0777);
	if (arg.infile < 0)
		print_error(argv[1], 1);
	arg.outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (arg.outfile < 0)
		print_error(argv[argc - 1], 1);
	arg.cmd_head = 0;
	arg.envp = envp;
	arg.path = get_env_path(envp);
	parse_cmds(&arg, argc, argv);
	pipex(arg, arg.infile, arg.outfile);
	return (0);
}
