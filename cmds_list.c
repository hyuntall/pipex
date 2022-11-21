/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:51:14 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/21 18:38:20 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmds	*ft_cmd_new(char **value)
{
	t_cmds	*cmd;

	cmd = (t_cmds *)malloc(sizeof(t_cmds));
	if (!cmd)
		return (0);
	cmd->cmd = value;
	cmd->next = 0;
	return (cmd);
}

void	cmd_insert(t_arg *arg, char **value)
{
	t_cmds	*new_cmd;

	new_cmd = ft_cmd_new(value);
	if (!arg->cmd_head)
	{
		arg->cmd_head = new_cmd;
		arg->cmd_tail = new_cmd;
		arg->cmd_tail->num = 0;
	}
	else
	{	
		arg->cmd_tail->next = new_cmd;
		arg->cmd_tail->next->num = arg->cmd_tail->num + 1;
		arg->cmd_tail = arg->cmd_tail->next;
		arg->cmd_tail->next = 0;
	}
}
