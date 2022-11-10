/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:41:01 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/10 17:17:39 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char	*str1;
	const unsigned char	*str2;

	str1 = (const unsigned char *) s1;
	str2 = (const unsigned char *) s2;
	i = 0;
	while (str1[i] && i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	if (!str1[i] && i < n)
		return (str1[i] - str2[i]);
	return (0);
}

char	*ft_strdup(const char *s1)
{
	int		size;
	int		i;
	char	*tmp;

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
	size_t	len;
	char	*tmp;

	i = 0;
	j = -1;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	tmp = (char *)malloc(sizeof(char) * len);
	if (!tmp)
		return (0);
	while (++j < ft_strlen(s1))
	{
		tmp[i] = s1[j];
		i++;
	}
	j = -1;
	while (++j < ft_strlen(s2))
	{
		tmp[i] = s2[j];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
