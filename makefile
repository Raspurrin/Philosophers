# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/10 00:43:58 by mialbert          #+#    #+#              #
#    Updated: 2022/09/20 00:06:50 by mialbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all: philo
# RED   = \x1b[31m
# GREEN = \x1b[32m
philo:
	gcc -g -Wall -Wextra -Werror -lpthread -o philo ./srcs/error.c ./srcs/time.c ./srcs/init.c ./srcs/main.c ./srcs/philo_states.c ./srcs/utils.c -fsanitize=thread
clean:
	@rm -f philo
fclean:
	@rm -f philo
re: fclean all

.PHONY: all clean fclean re

#-fsanitize=thread