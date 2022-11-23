/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:55:06 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/11/23 21:20:48 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "./gnl/get_next_line.h"

typedef struct s_cmds{
	int				num;
	struct s_cmds	*next;
	char			**cmd;
}	t_cmds;

typedef struct s_arg{
	char		*infile_name;
	char		*outfile_name;
	int			infile;
	int			outfile;
	char		**path;
	char		**cmd;
	char		**envp;
	int			here_doc;
	char		*limit;
	int			status_code;
	t_cmds		*cmd_head;
	t_cmds		*cmd_tail;
}	t_arg;

// handle error
void	print_error(t_arg *arg, char *s, int code);

//parsing
char	**get_env_path(char **envp);
void	parse_cmds(t_arg *arg, int argc, char **argv);

void	cmd_insert(t_arg *arg, char **value);

void	pipex(t_arg *arg);
char	*insert_slash(char *cmd);

void	here_doc(t_arg arg, int pipe_num);
// utils
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
void	ft_putstr_fd(char *s, int fd);

#endif