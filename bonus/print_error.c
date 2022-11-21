/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:11:01 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/21 22:20:53 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	print_error(t_arg *arg, char *s, int code)
{
	if (code == 1)
		write(2, "pipex: no such file or directory: ", 34);
	else if (code == 127)
		write(2, "pipex: command not found: ", 26);
	else if (code == 2)
	{
		write(2, "pipex: permission denied: ", 26);
		write(2, s, ft_strlen(s));
		write(2, "\n", 1);
		exit(1);
	}
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	arg->status_code = code;
}
