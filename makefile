# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/10 00:43:58 by mialbert          #+#    #+#              #
#    Updated: 2022/09/13 00:07:03 by mialbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all: philo
# RED   = \x1b[31m
# GREEN = \x1b[32m
philo:
	gcc -Wall -Wextra -Werror -lpthread -o philo ./srcs/error.c ./srcs/init.c ./srcs/main.c ./srcs/philo_states.c ./srcs/utils.c | echo "${GREEN}It works somehow 🤠😺🙉"
clean:
	@rm -f philo
fclean:
	@rm -f philo
re: fclean all

.PHONY: all clean fclean re

#-fsanitize=thread