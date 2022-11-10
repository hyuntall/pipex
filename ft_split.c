/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:58:00 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/10 16:46:38 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_c(char str_c, char c)
{
	if (str_c == c)
		return (1);
	if (str_c == '\0')
		return (1);
	return (0);
}

void	ft_strcpy(char *dest, char const *s, size_t j)
{
	size_t	i;

	i = 0;
	while (i < j)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
}

void	all_free(char **result, size_t word)
{
	size_t	i;

	i = 0;
	while (i < word)
	{
		free(result[i]);
		i++;
	}
	free(result);
}

void	fill_result_array(char **result, char const *s, char c)
{
	size_t	j;
	size_t	word;
	size_t	i;

	i = 0;
	word = -1;
	while (s[i])
	{
		if (check_c(s[i], c))
			i++;
		else
		{
			j = 0;
			while (!check_c(s[i + j], c))
				j++;
			result[++word] = (char *)malloc(sizeof(char) * (j + 1));
			if (!result[word])
			{
				all_free(result, word);
				return ;
			}
			ft_strcpy(result[word], s + i, j);
			i += j;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	word;
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	word = 0;
	while (s[i])
	{
		if (check_c(s[i + 1], c) && !check_c(s[i], c))
			word++;
		i++;
	}
	result = (char **)malloc(sizeof(char *) * (word + 1));
	if (!result)
		return (0);
	result[word] = 0;
	if (word == 0)
		return (result);
	fill_result_array(result, s, c);
	return (result);
}
