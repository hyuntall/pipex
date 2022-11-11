/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:52:23 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/11 21:16:27 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execmd(t_arg *arg)
{
	while (*arg->cmd)
	{
		
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_arg	arg;
	int		files[2];

	if (argc != 5)
		print_error("Not 5 ARG!");
	arg.infile = open(argv[1], O_RDONLY);
	arg.cmd = get_cmds(argc, argv);
	if (arg.infile < 0)
		print_error("infile error");
	arg.outfile = open(argv[argc - 1], O_RDWR);
	if (arg.outfile < 0)
		print_error("outfile error");
	arg.path = get_env_path(envp);
	while (*arg.cmd)
		printf("%s\n", *arg.cmd++);
	pipe(files);
	printf("%d %d\n", files[0], files[1]);
	while (*arg.path)
		printf("path: %s\n", *arg.path++);
	return (0);
}
