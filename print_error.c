/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:11:01 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/17 18:44:46 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *s, int code)
{
	//system("leaks pipex");
	if (code == 1)
		write(2, "pipex: no such file or directory: ", 34);
	else if (code == 127)
		write(2, "pipex: command not found: ", 26);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	//exit(code);
}
