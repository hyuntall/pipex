/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:47:56 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/10/26 15:48:29 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t		size;
	int			i;
	char		*tmp;

	i = -1;
	size = ft_strlen(s1);
	tmp = (char *)malloc(sizeof(char) * (size + 1));
	if (!tmp)
		return (0);
	while (s1[++i])
		tmp[i] = s1[i];
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len1;
	size_t	len2;
	char	*tmp;

	i = 0;
	j = -1;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	tmp = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!tmp)
		return (0);
	while (++j < len1)
		tmp[i++] = s1[j];
	j = -1;
	while (++j < len2)
		tmp[i++] = s2[j];
	tmp[i] = '\0';
	return (tmp);
}

int	in_next_line(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
		return (-1);
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*tmp;
	unsigned int		length;
	size_t				i;

	i = -1;
	if (!s)
		return (0);
	length = ft_strlen(s);
	if (start > length)
		len = 0;
	if (len > length)
		len = length - start;
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (0);
	while (++i < len && s[start + i])
		tmp[i] = s[start + i];
	tmp[i] = '\0';
	return (tmp);
}
