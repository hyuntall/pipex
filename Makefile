# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/10 16:12:59 by hyuncpar          #+#    #+#              #
#    Updated: 2022/11/22 17:42:03 by hyuncpar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex
BNAME	=	pipex

CC		=	cc -g -fsanitize=address
CFLAG	=	-Wall -Werror -Wextra
RM		=	rm -f

SRCS	=	main.c parse.c cmds_list.c print_error.c ft_split.c pipex.c\
			utils.c utils2.c

BSRCS	=	./bonus/main_bonus.c ./bonus/parse_bonus.c ./bonus/cmds_list_bonus.c \
			./bonus/print_error.c ./bonus/ft_split.c ./bonus/pipex_bonus.c\
			./bonus/utils.c ./bonus/utils2.c ./bonus/here_doc.c

GNL_SRCS	= ./bonus/gnl/get_next_line.c ./bonus/gnl/get_next_line_utils.c

OBJS	=	$(SRCS:.c=.o)

BOBJS	=	$(BSRCS:.c=.o) $(GNL_SRCS:.c=.o)

.c.o :
	$(CC) $(CFLAGS) -o $@ -c $?

$(NAME)	: $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

$(BNAME) : $(BOBJS)
	$(CC) -o $(BNAME) $(BOBJS)

all	: $(NAME)

bonus : $(BNAME)

clean :
	$(RM) $(OBJS) $(BOBJS)

fclean : clean
	$(RM) $(NAME) $(BNAME)

re	: clean
	$(MAKE)

PHONY	:	all clean fclean re bonus