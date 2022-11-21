/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:47:27 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/09/08 22:39:48 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read(int fd, char *buff, char *backup)
{
	char	*temp;
	int		rd;

	while (1)
	{
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd == 0)
			break ;
		if (rd == -1)
			return (0);
		buff[rd] = '\0';
		if (!backup)
			backup = ft_strdup("");
		temp = backup;
		backup = ft_strjoin(backup, buff);
		if (!backup)
			return (0);
		free(temp);
		temp = 0;
		if (in_next_line(buff) > -1)
			break ;
	}
	return (backup);
}

static char	*backup_next_line(char *line)
{
	int		i;
	char	*result;

	if (!line)
		return (0);
	i = in_next_line(line);
	if (i < 0)
		return (0);
	result = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (!result[0])
	{
		free(result);
		return (0);
	}
	line[i + 1] = '\0';
	return (result);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buff;
	static char	*backup[OPEN_MAX];

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	line = ft_read(fd, buff, backup[fd]);
	backup[fd] = backup_next_line(line);
	free(buff);
	buff = 0;
	return (line);
}
