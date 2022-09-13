/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:42:58 by mialbert          #+#    #+#             */
/*   Updated: 2022/09/13 02:26:14 by mialbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct philo
{
	pthread_t		sopher;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
}	t_philo;

typedef struct data
{
	t_philo		*philo;
	size_t		philo_nbr;
	int32_t		ripoclock;
	int32_t		numoclock;
	int32_t		zzzoclock;
	int32_t		min_meals;
}	t_data;

int32_t	ft_atoi(const char *str);
bool	error_check(int32_t argc, char **argv);
void	init_data(t_data *data, char **argv);
void	*routine(void *data);

#endif