/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:58:05 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/23 21:56:55 by hyuncpar         ###   ########.fr       */
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

	i = 0;
	print_pipe(pipe_num);
	write(1, &"heredoc> ", 9);
	line = get_next_line(0);
	fd = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (ft_strlen(line) != ft_strlen(arg.limit) + 1 && \
	ft_strncmp(line, arg.limit, ft_strlen(line) - 1))
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
	line = 0;
	close(fd);
}
