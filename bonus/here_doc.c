/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:58:05 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/24 15:58:56 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	print_pipe(int pipe_num)
{
	int	i;

	i = 0;
	while (i++ < pipe_num)
		write(1, "pipe ", 5);
}

void	here_doc(t_arg arg, int pipe_num)
{
	char	*line;
	int		fd;
	int		i;
	char	*limit;

	i = 0;
	limit = ft_strjoin(arg.limit, "\n");
	print_pipe(pipe_num);
	write(1, &"heredoc> ", 9);
	line = get_next_line(0);
	fd = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (ft_strcmp(line, limit))
	{
		ft_putstr_fd(line, fd);
		free(line);
		line = 0;
		i = 0;
		print_pipe(pipe_num);
		write(1, &"heredoc> ", 9);
		line = get_next_line(0);
	}
	free(line);
	free(limit);
	close(fd);
}
