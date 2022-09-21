# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/10 00:43:58 by mialbert          #+#    #+#              #
#    Updated: 2022/09/22 01:28:57 by mialbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS	= -Wall -Wextra -Werror -pthread -g -O3
CC		= clang
NAME	= philo
DEBUG	= -fsanitize=thread
SRCS	=	./srcs/error.c \
			./srcs/init.c \
			./srcs/time.c \
			./srcs/main.c \
			./srcs/philo_states.c \
			./srcs/utils.c \
			./srcs/rand.c
OBJS	= $(SRCS:.c=.o)

NC		:= \033[0m
B_RED	:= \033[1;31m
RED 	:= \033[0;31m
PURPLE	:= \033[0;35m
B_BLUE 	:= \033[1;34m
BLUE 	:= \033[0;34m

all: philo

%.o : %.c
	@echo "$(B_BLUE)Compiling: $(BLUE)$(notdir $<) 🔨$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

banner:
	@echo "\n${PURPLE}======== Philosophers ========${NC}"
#	@say die die die die die die die
	@say Think eat sleep dont die think eat sleep dont die think eat sleep die die die die die die die

$(NAME): banner $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(DEBUG)
clean:
	@rm -f $(OBJS)
	@echo "${B_RED}🧹 Cleaning: ${RED} philo object files $(NC)"

fclean: clean
	@rm -f philo
	@echo "${B_RED}🧹 Cleaning: ${RED} $(NAME)$(NC)"

re: fclean all

.PHONY: all clean fclean re banner $(NAME)
