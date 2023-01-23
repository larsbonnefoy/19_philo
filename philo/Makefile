# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 14:55:28 by lbonnefo          #+#    #+#              #
#    Updated: 2023/01/21 15:32:16 by lbonnefo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo 

FILES =	main.c \
		parsing.c \
		parsing_utils.c \
		utils.c \
		init_simu.c \

SRCS= $(addprefix src/, $(FILES))

OBJ = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

$(NAME): $(OBJ)
				cc $(CFLAGS) $(OBJ) -o $(NAME)

.c.o:
		cc $(CFLAGS) -c $< -o $(<:.c=.o)

all: $(NAME) 

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
