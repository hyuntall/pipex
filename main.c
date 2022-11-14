/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:52:23 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/14 21:04:48 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_arg	arg;
	int		files[2];

	if (argc != 5)
	{
		print_error("Not 5 ARG!", 0);
		return (0);
	}
	arg.infile = open(argv[1], O_RDONLY, 0777);
	if (arg.infile < 0)
		print_error(argv[1], 1);
	arg.outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (arg.outfile < 0)
		print_error("outfile error", 0);
	arg.envp = envp;
	arg.cmd = get_cmds(argc, argv);
	arg.path = get_env_path(envp);
	pipex(arg, arg.infile, arg.outfile);
	return (0);
}
