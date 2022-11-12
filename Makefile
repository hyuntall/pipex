# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/10 16:12:59 by hyuncpar          #+#    #+#              #
#    Updated: 2022/11/12 21:18:48 by hyuncpar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex

CC		=	cc -g -fsanitize=address
CFLAG	=	-Wall -Werror -Wextra
RM		=	rm -f

SRCS	=	main.c parse.c print_error.c ft_split.c pipex.c\
			utils.c utils2.c

OBJS	=	$(SRCS:.c=.o)

.c.o :
	$(CC) $(CFLAGS) -o $@ -c $?

$(NAME)	: $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

all	: $(NAME)

clean :
	$(RM) $(OBJS)

flcean : clean
	$(RM) $(NAME)

re	: clean
	$(MAKE)

PHONY	:	all clean fclean re bonus