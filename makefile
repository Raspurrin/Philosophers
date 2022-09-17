# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/10 00:43:58 by mialbert          #+#    #+#              #
#    Updated: 2022/09/17 19:20:56 by mialbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all: philo
# RED   = \x1b[31m
# GREEN = \x1b[32m
philo:
	gcc -g -Wall -Wextra -Werror -lpthread -o philo ./srcs/error.c ./srcs/init.c ./srcs/main.c ./srcs/philo_states.c ./srcs/utils.c -fsanitize=thread
clean:
	@rm -f philo
fclean:
	@rm -f philo
re: fclean all

.PHONY: all clean fclean re

#-fsanitize=thread