/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:55:06 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/16 20:03:37 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_cmds{
	int				num;
	struct s_cmds	*next;
	char			**cmd;
}	t_cmds;

typedef struct s_arg{
	int		infile;
	int		outfile;
	char	**path;
	char	**cmd;
	char	**envp;
	t_cmds	*cmd_head;
	t_cmds	*cmd_tail;
}	t_arg;

// handle error
void	print_error(char *s, int code);

//parsing
char	**get_env_path(char **envp);
void	parse_cmds(t_arg *arg, int argc, char **argv);

void	cmd_insert(t_arg *arg, char **value);

void	pipex(t_arg arg, int infile, int outfile);
char	*insert_slash(char *cmd);
// utils
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
#endif