# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 14:55:28 by lbonnefo          #+#    #+#              #
#    Updated: 2023/01/29 12:53:08 by lbonnefo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo 

FILES =	main.c \
		parsing.c \
		parsing_utils.c \
		utils.c \
		eat_sleep_think.c \
		init_run_simu.c \
		thread_management.c 

SRCS= $(addprefix src/, $(FILES))

OBJ = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g

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
