# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jllarena <jllarena@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/18 10:55:57 by jllarena          #+#    #+#              #
#    Updated: 2024/03/18 11:08:41 by jllarena         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = gcc
FLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRC = mandatory/pipex.c mandatory/error.c mandatory/free.c \
	mandatory/childs.c \
	functions/ft_split.c functions/ft_strjoin.c \
	functions/ft_strncmp.c functions/ft_strlen.c \
	functions/ft_strdup.c

OBJ = $(SRC:.c=.o)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re