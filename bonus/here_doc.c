/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:58:05 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/22 17:40:01 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	here_doc(t_arg arg)
{
	char	*line;
	int		fd;

	write(1, &"heredoc> ", 9);
	line = get_next_line(0);
	fd = open("temp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (line && ft_strncmp(line, arg.limit, ft_strlen(arg.limit)))
	{
		ft_putstr_fd(line, fd);
		free(line);
		line = 0;
		write(1, &"heredoc> ", 9);
		line = get_next_line(0);
	}
	free(line);
	line = 0;
	close(fd);
	fd = open("temp", O_RDONLY);
	return (fd);
}
