/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:42:58 by mialbert          #+#    #+#             */
/*   Updated: 2022/09/17 23:06:09 by mialbert         ###   ########.fr       */
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
# include <unistd.h>

typedef struct philo	t_philo;

typedef struct data
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	int32_t			philo_nbr;
	int32_t			ripoclock;
	int32_t			nomoclock;
	int32_t			zzzoclock;
	int32_t			min_meals;
}	t_data;

typedef struct philo
{
	pthread_t		sopher;
	
	int32_t			index;
	int64_t			meal_time;
	int32_t			meal_count;
	t_data			*data;
}	t_philo;

int32_t	ft_atoi(const char *str);
bool	error_check(int32_t argc);
void	init_data(t_data *data, int32_t argc, char **argv);
void	*routine(void *v_philo);
int64_t	get_time(void);

#endif